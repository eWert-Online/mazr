module General = Reducers_General;
module Decorations = Reducers_Decorations;
module Objects = Reducers_Objects;
module Path = Reducers_Path;
module Ui = Reducers_Ui;
module Mob = Reducers_Mob;

type t = {
  general: General.t,
  objects: Objects.t,
  path: Path.t,
  decorations: Decorations.t,
  ui: Ui.t,
  mobs: Mob.t,
};

module Actions = {
  type t = {
    handleGridClick: ((int, int)) => unit,
    selectElement: Types.Ui.selectables => unit,
    spawnMob: (((int, int)) => Mazr.Types.Mob.t) => unit,
  };

  let handleGridClick = ((state, dispatch: ActionTypes.t => unit), coordinates: (int, int)) => {
    let selectedElement = state.ui.selectedElement;
    let startNode = state.path.startNode;
    let beacon = state.path.beacon;
    let endNode = state.path.endNode;

    switch (startNode, beacon, endNode) {
    | (None, _, _) => dispatch(ActionTypes.SET_START_NODE(coordinates))
    | (Some(_), None, _) => dispatch(ActionTypes.SET_BEACON(coordinates))
    | (Some(_), Some(_), None) => dispatch(ActionTypes.SET_END_NODE(coordinates))
    | (Some(_), Some(_), Some(_)) =>
      switch (selectedElement) {
      | Object(building) => dispatch(ActionTypes.PLACE_BUILDING(coordinates, building))
      | Sell => dispatch(ActionTypes.SELL_BUILDING(coordinates))
      }
    };
  };

  let spawnMob = ((state, dispatch: ActionTypes.t => unit), init) => {
    switch (state.path.startNode) {
    | Some(coords) =>
      let mob = init(coords);
      dispatch(ActionTypes.SPAWN_MOB(mob));
    | None => ()
    };
  };

  let selectElement = ((_state, dispatch: ActionTypes.t => unit), element) => {
    dispatch(ActionTypes.SET_SELECTED_ELEMENT(element));
  };
};

let make = () => {
  let (state_deco, dispatch_deco) = React.useReducer(Decorations.make, Decorations.initialState);
  let (state_general, dispatch_general) = React.useReducer(General.make, General.initialState);
  let (state_path, dispatch_path) = React.useReducer(Path.make, Path.initialState);
  let (state_objects, dispatch_objects) = React.useReducer(Objects.make, Objects.initialState);
  let (state_ui, dispatch_ui) = React.useReducer(Ui.make, Ui.initialState);
  let (state_mobs, dispatch_mobs) = React.useReducer(Mob.make, Mob.initialState);

  let actionQueue = React.useRef([]);

  let rec flushQueue = actions => {
    switch (actions) {
    | Some(actions) =>
      let maybeAction = Belt.List.head(actions);
      switch (maybeAction) {
      | Some(action) =>
        dispatch_deco(action);
        dispatch_general(action);
        dispatch_path(action);
        dispatch_objects(action);
        dispatch_ui(action);
        dispatch_mobs(action);

        flushQueue(Belt.List.tail(actions));
      | None => ()
      };
    | None => ()
    };
  };

  let dispatch = (action: ActionTypes.t) => {
    React.Ref.setCurrent(actionQueue, Belt.List.concat(React.Ref.current(actionQueue), [action]));
  };

  Hooks.useInterval(
    () => {
      let actions = React.Ref.current(actionQueue);
      React.Ref.setCurrent(actionQueue, []);

      let moveActions = [||];
      let actions =
        actions->Belt.List.keep(action => {
          switch (action) {
          | ActionTypes.MOVE_MOB(id, coordinates) =>
            ignore(Js.Array.push((id, coordinates), moveActions));
            false;
          | _ => true
          }
        });
      let bulkMove = ActionTypes.MOVE_MOB_BULK(moveActions);
      flushQueue(Some([bulkMove, ...actions]));
    },
    32,
  );

  let state =
    React.useRef({
      general: state_general,
      objects: state_objects,
      path: state_path,
      decorations: state_deco,
      ui: state_ui,
      mobs: state_mobs,
    });

  React.Ref.setCurrent(
    state,
    {
      general: state_general,
      objects: state_objects,
      path: state_path,
      decorations: state_deco,
      ui: state_ui,
      mobs: state_mobs,
    },
  );

  let actions: Actions.t = {
    handleGridClick: coords => Actions.handleGridClick((React.Ref.current(state), dispatch), coords),
    spawnMob: mob => Actions.spawnMob((React.Ref.current(state), dispatch), mob),
    selectElement: element => Actions.selectElement((React.Ref.current(state), dispatch), element),
  };

  (React.Ref.current(state), dispatch, actions);
};
module Styles = {
  open Css;

  let mob =
    style([
      position(absolute),
      top(0->px),
      left(0->px),
      unsafe("width", "calc(100% / " ++ string_of_int(Settings.map_width) ++ ")"),
      display(block),
      margin(auto),
      overflow(hidden),
      transitionProperty("all"),
      transitionTimingFunction(linear),
      selector("&::before", [contentRule(`text("")), display(block), paddingTop(100.0->pct)]),
    ]);
};

[@react.component]
let make = (~mob: Types.Mob.t) => {
  let (state, dispatch) = React.useContext(GameContext.context);

  let prevCoordinates = React.useRef(mob.coordinates);
  let currentTile = React.useRef(state.grid.tiles[mob.coordinates.x][mob.coordinates.y]);
  let hasBeacon = React.useRef(false);

  React.useEffect2(
    () => {
      React.Ref.setCurrent(prevCoordinates, React.Ref.current(currentTile).coordinates);
      React.Ref.setCurrent(currentTile, state.grid.tiles[mob.coordinates.x][mob.coordinates.y]);
      if (React.Ref.current(hasBeacon) === false) {
        React.Ref.setCurrent(
          hasBeacon,
          switch (state.grid.tiles[mob.coordinates.x][mob.coordinates.y].entity) {
          | Waypoint(Beacon) => true
          | _ => false
          },
        );
      };
      None;
    },
    (mob.coordinates.x, mob.coordinates.y),
  );

  Hooks.useInterval(
    () => {
      let currentTile = React.Ref.current(currentTile);
      let hasBeacon = React.Ref.current(hasBeacon);

      let newCoordinates =
        switch (currentTile.path.nextPath.toBeacon, currentTile.path.nextPath.toEnd, hasBeacon) {
        | (_, Some(pathToEnd), true) => pathToEnd
        | (Some(pathToBeacon), _, false) => pathToBeacon
        | _ => currentTile.coordinates
        };
      dispatch(ActionTypes.MOVE_MOB(mob.id, newCoordinates));

      switch (currentTile.entity, hasBeacon) {
      | (Waypoint(EndNode), true) =>
        ignore(Js.Global.setTimeout(() => dispatch(ActionTypes.DESPAWN_MOB(mob.id)), mob.speed))
      | _ => ()
      };
    },
    mob.speed,
  );

  <div
    className={Css.merge([
      Styles.mob,
      Css.(
        style([
          transforms([
            translate(
              (float_of_int(React.Ref.current(currentTile).coordinates.x) *. 100.0)->pct,
              (float_of_int(React.Ref.current(currentTile).coordinates.y) *. 100.0)->pct,
            ),
            translateY((-30.0)->pct),
          ]),
          transitionDuration(mob.speed),
        ])
      ),
    ])}>
    {switch (mob.typ) {
     | Skeleton =>
       <Mob_Skeleton
         animation={
           switch (React.Ref.current(currentTile).coordinates, React.Ref.current(prevCoordinates)) {
           | (current, prev) when current.x < prev.x => Mob_Skeleton.Animations.walkLeft // LEFT
           | (current, prev) when current.x > prev.x => Mob_Skeleton.Animations.walkRight // RIGHT
           | (current, prev) when current.y > prev.y => Mob_Skeleton.Animations.walkDown // DOWN
           | (current, prev) when current.y < prev.y => Mob_Skeleton.Animations.walkUp // UP
           | _ => ""
           }
         }
       />
     }}
  </div>;
};
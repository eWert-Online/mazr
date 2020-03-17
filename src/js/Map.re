module Styles = {
  open Css;

  let map =
    style([
      position(relative),
      display(`flex),
      flexWrap(nowrap),
      alignItems(center),
      justifyContent(center),
      border(5->px, solid, hex("fcfcfc")),
    ]);
  let gridColumn = style([flexGrow(1.0)]);
  let gridCell =
    style([
      position(relative),
      display(block),
      width(100.0->pct),
      selector("&::before", [contentRule(`text("")), display(block), paddingTop(100.0->pct)]),
    ]);
};

[@react.component]
let make = () => {
  let (state, dispatch) = React.useContext(GameContext.context);

  let handleTileClick =
    React.useCallback2(
      (tile: Types.Grid.tile) => {
        switch (state.grid.waypoints.startNode, state.grid.waypoints.beacon, state.grid.waypoints.endNode) {
        | (None, _, _) => dispatch(ActionTypes.SET_START_NODE(tile.coordinates))
        | (Some(_), None, _) => dispatch(ActionTypes.SET_BEACON(tile.coordinates))
        | (Some(_), Some(_), None) => dispatch(ActionTypes.SET_END_NODE(tile.coordinates))
        | (Some(_), Some(_), Some(_)) =>
          switch (state.ui.selectedElement) {
          | Building(building) => dispatch(ActionTypes.PLACE_BUILDING(tile.coordinates, building))
          | Sell => dispatch(ActionTypes.SELL_BUILDING(tile.coordinates))
          }
        }
      },
      (state.grid.waypoints, state.ui.selectedElement),
    );

  React.useMemo2(
    () => {
      <div className=Styles.map>
        {Belt.Array.mapWithIndex(state.grid.tiles, (x, row) => {
           <div className=Styles.gridColumn key={string_of_int(x)}>
             {row
              ->Belt.Array.mapWithIndex((y, _column) => {
                  let tile = state.grid.tiles[x][y];
                  let neighbours = Pathfinder.getNeighbours(~tiles=state.grid.tiles, ~tile);
                  <div className=Styles.gridCell key={"tile_" ++ string_of_int(x) ++ "-" ++ string_of_int(y)}>
                    <MapTile tile neighbours onClick=handleTileClick />
                  </div>;
                })
              ->React.array}
           </div>
         })
         ->React.array}
      </div>
    },
    (state.grid.tiles, handleTileClick),
  );
};
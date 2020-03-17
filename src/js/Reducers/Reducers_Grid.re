module ObjectReducer = Reducers_Grid_Object;
module Path = Reducers_Grid_Path;
module Waypoints = Reducers_Grid_Waypoints;

open Types.Grid;

type t = Types.Grid.t;

let initialState = {
  waypoints: Waypoints.initialState,
  tiles:
    Array.init(Settings.map_width, x =>
      Array.init(Settings.map_height, y =>
        {
          coordinates: {
            x,
            y,
          },
          path: Path.initialState,
          entity: ObjectReducer.initialState(),
        }
      )
    ),
};

let make = (~state=initialState, ~action: ActionTypes.t) => {
  switch (action) {
  | SELL_BUILDING(coordinates)
  | PLACE_BUILDING(coordinates, _)
  | SET_START_NODE(coordinates)
  | SET_END_NODE(coordinates)
  | SET_BEACON(coordinates) =>
    let waypoints = Waypoints.make(~state=state.waypoints, ~action);
    let tiles = Belt.Array.map(state.tiles, row => {Belt.Array.map(row, tile => {...tile, path: Path.initialState})});

    let tileToUpdate = tiles[coordinates.x][coordinates.y];
    tiles[coordinates.x][coordinates.y] = {
      ...tileToUpdate,
      entity: ObjectReducer.make(~state=tileToUpdate.entity, ~action),
    };

    let pathToBeacon =
      switch (waypoints.startNode, waypoints.beacon) {
      | (Some(startNode), Some(beacon)) =>
        Pathfinder.find(~tiles, ~startTile=tiles[startNode.x][startNode.y], ~endTile=tiles[beacon.x][beacon.y])
      | _ => None
      };
    let pathToEnd =
      switch (waypoints.beacon, waypoints.endNode) {
      | (Some(beacon), Some(endNode)) =>
        Pathfinder.find(~tiles, ~startTile=tiles[beacon.x][beacon.y], ~endTile=tiles[endNode.x][endNode.y])
      | _ => None
      };

    switch (pathToBeacon) {
    | Some(path) =>
      Belt.List.forEachWithIndex(
        path,
        (index, pathTile) => {
          let nextPath =
            switch (Belt.List.get(path, index + 1)) {
            | Some(tile) => Some(tile.coordinates)
            | None => None
            };
          let tile = tiles[pathTile.coordinates.x][pathTile.coordinates.y];
          tiles[tile.coordinates.x][tile.coordinates.y] = {
            ...tile,
            path: {
              inPath: true,
              nextPath: {
                toBeacon: nextPath,
                toEnd: tile.path.nextPath.toEnd,
              },
            },
          };
        },
      )
    | None => ()
    };
    switch (pathToEnd) {
    | Some(path) =>
      Belt.List.forEachWithIndex(
        path,
        (index, pathTile) => {
          let nextPath =
            switch (Belt.List.get(path, index + 1)) {
            | Some(tile) => Some(tile.coordinates)
            | None => None
            };
          let tile = tiles[pathTile.coordinates.x][pathTile.coordinates.y];
          tiles[tile.coordinates.x][tile.coordinates.y] = {
            ...tile,
            path: {
              inPath: true,
              nextPath: {
                toBeacon: tile.path.nextPath.toBeacon,
                toEnd: nextPath,
              },
            },
          };
        },
      )
    | None => ()
    };

    {waypoints, tiles};
  | _ => state
  };
};
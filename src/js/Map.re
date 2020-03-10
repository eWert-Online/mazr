module Styles = {
  open Css;

  let map = style([display(`flex), flexWrap(nowrap), alignItems(center), justifyContent(center)]);
  let gridCell =
    style([
      position(relative),
      display(block),
      width(Grid.tileSize->pxFloat),
      selector("&::before", [contentRule(`text("")), display(block), paddingTop(100.0->pct)]),
    ]);
};

[@react.component]
let make = () => {
  let context = React.useContext(GameContext.context);

  let (hasPath, setHasPath) = React.useState(() => false);
  let (needToRecalculatePath, setNeedToRecalculatePath) = React.useState(() => true);

  let (tiles, setTiles) =
    React.useState(() => {
      Array.init(Grid.width, x =>
        Array.init(
          Grid.height,
          y => {
            let tile: Types.mapTile = {
              coordinates: {
                x,
                y,
              },
              state: Empty,
              nextPath: [||],
              objects:
                switch (Random.int(5)) {
                | 0 =>
                  switch (Random.int(10)) {
                  | 0 => Tree(Trunk)
                  | _ => Tree(DarkGreen)
                  }
                | 1 => Plant(HighGrass)
                | _ => None
                },
            };
            tile;
          },
        )
      )
    });

  let (mobs, setMobs) =
    React.useState(() => {
      let mobsArray: array(Types.mob) = [||];
      mobsArray;
    });

  React.useEffect5(
    () => {
      needToRecalculatePath
        ? {
          setTiles(tiles => {
            Belt.Array.map(tiles, row => {Belt.Array.map(row, tile => {{...tile, state: Empty, nextPath: [||]}})})
          });

          let pathToBeacon =
            switch (context.startNode, context.beacon) {
            | (Some(startNode), Some(beacon)) =>
              let path =
                Pathfinder.find(
                  ~tiles,
                  ~startTile=tiles[startNode.coordinates.x][startNode.coordinates.y],
                  ~endTile=tiles[beacon.coordinates.x][beacon.coordinates.y],
                );
              switch (path) {
              | Some(path) => path
              | None => []
              };
            | _ => []
            };

          let pathToEnd =
            switch (context.beacon, context.endNode) {
            | (Some(beacon), Some(endNode)) =>
              let path =
                Pathfinder.find(
                  ~tiles,
                  ~startTile=tiles[beacon.coordinates.x][beacon.coordinates.y],
                  ~endTile=tiles[endNode.coordinates.x][endNode.coordinates.y],
                );
              switch (path) {
              | Some(path) => path
              | None => []
              };
            | _ => []
            };

          let completePath = List.append(pathToBeacon, pathToEnd);

          setTiles(tiles => {
            let newTiles = Belt.Array.copy(tiles);
            Belt.List.forEachWithIndex(
              completePath,
              (index, pathTile) => {
                let nextPath: array(Grid.t) =
                  switch (Belt.List.get(completePath, index + 1)) {
                  | Some(tile) => [|{x: tile.coordinates.x, y: tile.coordinates.y}|]
                  | None => [||]
                  };
                let tile = newTiles[pathTile.coordinates.x][pathTile.coordinates.y];
                let tile = {...tile, state: Path, nextPath: Array.concat([tile.nextPath, nextPath])};
                Js.log(tile);
                newTiles[tile.coordinates.x][tile.coordinates.y] = tile;
              },
            );

            newTiles;
          });

          setHasPath(_ => List.length(pathToEnd) > 0 && List.length(pathToBeacon) > 0);
          setNeedToRecalculatePath(_ => false);
        }
        : ();
      None;
    },
    (context.startNode, context.beacon, context.endNode, tiles, needToRecalculatePath),
  );

  React.useEffect1(
    () => {
      let timer =
        switch (hasPath, context.startNode, context.beacon, context.endNode) {
        | (true, Some(start), Some(_beacon), Some(_destination)) =>
          Some(
            Js.Global.setInterval(
              () => {
                setMobs(mobs => {
                  let newMob = Mobs_Skeleton.init(~coordinates=start.coordinates);
                  Belt.Array.concat(mobs, [|newMob|]);
                })
              },
              8000,
            ),
          )
        | _ => None
        };

      switch (timer) {
      | Some(timerId) => Some(() => Js.Global.clearInterval(timerId))
      | None => None
      };
    },
    [|hasPath|],
  );

  let setTileState = (~tile: Types.mapTile, ~objects) => {
    setTiles(tiles => {
      let tiles = Array.copy(tiles);
      tiles[tile.coordinates.x][tile.coordinates.y] = {...tile, objects};
      tiles;
    });
    setNeedToRecalculatePath(_ => true);
    switch (objects) {
    | Waypoint(StartNode) => context.setStartNode(_ => Some(tile))
    | Waypoint(Beacon) => context.setBeacon(_ => Some(tile))
    | Waypoint(EndNode) => context.setEndNode(_ => Some(tile))
    | _ => ()
    };
  };

  <div className=Styles.map>
    {Belt.Array.mapWithIndex(Grid.grid, (x, row) => {
       <div key={string_of_int(x)}>
         {row
          ->Belt.Array.mapWithIndex((y, _column) => {
              let tile = tiles[x][y];
              <div className=Styles.gridCell key={"tile_" ++ string_of_int(x) ++ "-" ++ string_of_int(y)}>
                <MapTile tile tiles setObjects={objects => {setTileState(~tile, ~objects)}} />
              </div>;
            })
          ->React.array}
       </div>
     })
     ->React.array}
    {Belt.Array.mapWithIndex(mobs, (index, mob) => {<Mob key={string_of_int(index)} mob tiles />})->React.array}
  </div>;
};
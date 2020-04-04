type tile = {
  coordinates: (int, int),
  obstructed: bool,
};

type t = {
  startNode: option((int, int)),
  endNode: option((int, int)),
  beacon: option((int, int)),
  calculatedPath: array((int, int)),
  grid: array(array(tile)),
};

module Pathfinder = {
  let getDistance = ((x1, y1), (x2, y2)) => {
    abs(x1 - x2) + abs(y1 - y2);
  };

  let getNeighbours = (~grid: array(array(tile)), ~coordinates: (int, int)) => {
    let (x, y) = coordinates;
    let north =
      if (y > 0) {
        Some(grid[x][y - 1]);
      } else {
        None;
      };
    let east =
      if (x < Settings.map_width - 1) {
        Some(grid[x + 1][y]);
      } else {
        None;
      };
    let west =
      if (x > 0) {
        Some(grid[x - 1][y]);
      } else {
        None;
      };
    let south =
      if (y < Settings.map_height - 1) {
        Some(grid[x][y + 1]);
      } else {
        None;
      };

    [|north, east, south, west|];
  };

  let find = (~grid: array(array(tile)), ~startTile: (int, int), ~endTile: (int, int)) => {
    let (startX, startY) = startTile;
    let (endX, endY) = endTile;
    // parent holds a link to the previous node in the path.
    // Used at the end for reconstructing the route
    let parent = Array.make_matrix(Settings.map_width, Settings.map_height, None);

    // distanceCost holds the distance to any node taking the best known path so far.
    // Better paths replace worse ones as we find them.
    // We start with all distanceCosts at max_int
    let distanceCost = Array.make_matrix(Settings.map_width, Settings.map_height, max_int);

    // remainingCost holds the distance from any node to the end Node.
    // We start with all remainingCosts at 0
    let remainingCost = Array.make_matrix(Settings.map_width, Settings.map_height, 0);

    // openSet holds all the values, which are currently evaluated
    let openSet = ref([||]);

    // closedSet holds true / false on whether a node has been seen already.
    // Used to stop us returning to nodes multiple times
    let closedSet = Array.make_matrix(Settings.map_width, Settings.map_height, false);

    // To begin, we set the distance to the start to zero (we're there) and add it into the unvisited queue
    distanceCost[startX][startY] = 0;
    let _newIndex = Js.Array.push(startTile, openSet^);

    let finalPath = [||];

    // Begin!
    // continue while there are unvisited nodes in the queue
    while (Array.length(openSet^) > 0) {
      // Find current shortest path point to explore
      let current =
        Belt.Array.reduce(
          openSet^,
          openSet^[0],
          (initial, item) => {
            let (currentX, currentY) = item;
            let (initialX, initialY) = initial;
            if (distanceCost[currentX][currentY] < distanceCost[initialX][initialY]
                || distanceCost[currentX][currentY] === distanceCost[initialX][initialY]
                && remainingCost[currentX][currentY] < remainingCost[initialX][initialY]) {
              item;
            } else {
              initial;
            };
          },
        );

      let (currentX, currentY) = current;

      openSet := Belt.Array.keep(openSet^, item => {item != current});
      // Mark the current node as visited
      closedSet[currentX][currentY] = true;

      // If the current item is the the endTile we are done!
      if (currentX === endX && currentY === endY) {
        // We want to reconstruct the path.
        // We start at end, and then go prev[end] and follow all the prev[] links until we're back at the start
        let rec getPath = (pathSegment: (int, int)) => {
          let (x, y) = pathSegment;
          let nextParent = parent[x][y];
          switch (nextParent) {
          | Some(parent) => getPath(parent)
          | _ => ()
          };
          switch (pathSegment) {
          | (x, y) when x === startX && y === startY => ()
          | (x, y) when x === endX && y === endY => ()
          | _ => ignore(Js.Array.push(pathSegment, finalPath))
          };
        };
        getPath(current);
      } else {
        // Get every neighbor of the current tile
        let neighbours = getNeighbours(~grid, ~coordinates=current);
        Belt.Array.forEach(neighbours, neighbour
          // Check, if we havent already visited the current neighbour
          =>
            switch (neighbour) {
            | Some(neighbour) =>
              let (neighbourX, neighbourY) = neighbour.coordinates;
              if (closedSet[neighbourX][neighbourY] === false && !neighbour.obstructed) {
                // newDistanceToNeigbour is the distance of the path from the start, through the current node, to the neighbour.
                let newDistanceToNeigbour =
                  distanceCost[currentX][currentY] + getDistance((currentX, currentY), (neighbourX, neighbourY));

                // A* includes a remaining cost, the f cost. In this case we use manhattan distance to calculate the distance from
                // the neighbour to the end. We use manhattan again because A* works well when the g cost and f cost are balanced.
                // https://en.wikipedia.org/wiki/Taxicab_geometry
                let remaining = getDistance((neighbourX, neighbourY), (endX, endY));

                // Check if the neighbor is in the openList
                let isOpen =
                  Belt.Array.some(
                    openSet^,
                    item => {
                      let (x, y) = item;
                      x === neighbourX && y === neighbourY;
                    },
                  );

                // If this new distance is the new shortest path to the current neighbour
                if (newDistanceToNeigbour < distanceCost[neighbourX][neighbourY] || !isOpen) {
                  distanceCost[neighbourX][neighbourY] = newDistanceToNeigbour;
                  remainingCost[neighbourX][neighbourY] = remaining;
                  parent[neighbourX][neighbourY] = Some(current);

                  if (!isOpen) {
                    let _newIndex = Js.Array.push(neighbour.coordinates, openSet^);
                    ();
                  };
                };
              };
            | None => ()
            }
          );
      };
    };

    Array.length(finalPath) > 0 ? Some(finalPath) : None;
  };
};

let initialState = {
  startNode: None,
  beacon: None,
  endNode: None,
  calculatedPath: [||],
  grid: {
    let objects = Reducers_Objects.initialState;
    Array.init(Settings.map_width, x =>
      Array.init(
        Settings.map_height,
        y => {
          let coordinates = (x, y);
          {coordinates, obstructed: Belt.Array.some(objects, item => {item.coordinates == coordinates})};
        },
      )
    );
  },
};

let make = (state: t, action: ActionTypes.t) => {
  let newState =
    switch (action) {
    | SET_START_NODE((x, y)) =>
      let grid = Belt.Array.copy(state.grid);
      let tileToUpdate = grid[x][y];
      grid[x][y] = {...tileToUpdate, obstructed: false};
      {...state, grid, startNode: Some((x, y))};
    | SET_BEACON((x, y)) =>
      let grid = Belt.Array.copy(state.grid);
      let tileToUpdate = grid[x][y];
      grid[x][y] = {...tileToUpdate, obstructed: false};
      {...state, grid, beacon: Some((x, y))};
    | SET_END_NODE((x, y)) =>
      let grid = Belt.Array.copy(state.grid);
      let tileToUpdate = grid[x][y];
      grid[x][y] = {...tileToUpdate, obstructed: false};
      {...state, grid, endNode: Some((x, y))};
    | PLACE_BUILDING((x, y), _)
    | SELL_BUILDING((x, y)) =>
      let grid = Belt.Array.copy(state.grid);
      let tileToUpdate = grid[x][y];
      grid[x][y] = {
        ...tileToUpdate,
        obstructed:
          switch (action) {
          | PLACE_BUILDING(_, _) => true
          | SELL_BUILDING(_) => false
          | _ => tileToUpdate.obstructed
          },
      };
      {...state, grid};
    | _ => state
    };

  {
    ...newState,
    calculatedPath:
      Array.concat([
        switch (newState.startNode, newState.beacon) {
        | (Some(startNode), Some(beacon)) =>
          switch (Pathfinder.find(~grid=newState.grid, ~startTile=startNode, ~endTile=beacon)) {
          | Some(path) => Array.concat([[|startNode|], path, [|beacon|]])
          | None => [||]
          }
        | _ => [||]
        },
        switch (newState.beacon, newState.endNode) {
        | (Some(beacon), Some(endNode)) =>
          switch (Pathfinder.find(~grid=newState.grid, ~startTile=beacon, ~endTile=endNode)) {
          | Some(path) => Array.concat([path, [|endNode|]])
          | None => [||]
          }
        | _ => [||]
        },
      ]),
  };
};
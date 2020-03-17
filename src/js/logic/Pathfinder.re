let getDistance = (nodeA: Types.Grid.tile, nodeB: Types.Grid.tile) => {
  abs(nodeA.coordinates.x - nodeB.coordinates.x) + abs(nodeA.coordinates.y - nodeB.coordinates.y);
};

let isObstacle = (~tile: Types.Grid.tile) => {
  switch (tile.entity) {
  | Tree(_) => true
  | _ => false
  };
};

let getNeighbours = (~tiles: array(array(Types.Grid.tile)), ~tile: Types.Grid.tile) => {
  let north =
    if (tile.coordinates.y > 0) {
      Some(tiles[tile.coordinates.x][tile.coordinates.y - 1]);
    } else {
      None;
    };
  let east =
    if (tile.coordinates.x < Settings.map_width - 1) {
      Some(tiles[tile.coordinates.x + 1][tile.coordinates.y]);
    } else {
      None;
    };
  let west =
    if (tile.coordinates.x > 0) {
      Some(tiles[tile.coordinates.x - 1][tile.coordinates.y]);
    } else {
      None;
    };
  let south =
    if (tile.coordinates.y < Settings.map_height - 1) {
      Some(tiles[tile.coordinates.x][tile.coordinates.y + 1]);
    } else {
      None;
    };

  [|north, east, south, west|];
};

let find = (~tiles: array(array(Types.Grid.tile)), ~startTile: Types.Grid.tile, ~endTile: Types.Grid.tile) => {
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
  distanceCost[startTile.coordinates.x][startTile.coordinates.y] = 0;
  let _newIndex = Js.Array.push(startTile, openSet^);

  let finalPath = ref([]);

  // Begin!
  // continue while there are unvisited nodes in the queue
  while (Array.length(openSet^) > 0) {
    // Find current shortest path point to explore
    let current =
      Belt.Array.reduce(openSet^, openSet^[0], (initial, item) =>
        if (distanceCost[item.coordinates.x][item.coordinates.y]
            < distanceCost[initial.coordinates.x][initial.coordinates.y]
            || distanceCost[item.coordinates.x][item.coordinates.y]
            === distanceCost[initial.coordinates.x][initial.coordinates.y]
            && remainingCost[item.coordinates.x][item.coordinates.y]
            < remainingCost[initial.coordinates.x][initial.coordinates.y]) {
          item;
        } else {
          initial;
        }
      );

    openSet := Belt.Array.keep(openSet^, item => {item !== current});
    // Mark the current node as visited
    closedSet[current.coordinates.x][current.coordinates.y] = true;

    // If the current item is the the endTile we are done!
    if (current.coordinates.x === endTile.coordinates.x && current.coordinates.y === endTile.coordinates.y) {
      // We want to reconstruct the path.
      // We start at end, and then go prev[end] and follow all the prev[] links until we're back at the start
      let rec getPath = (pathSegment: Types.Grid.tile) => {
        let nextParent = parent[pathSegment.coordinates.x][pathSegment.coordinates.y];
        [
          pathSegment,
          ...switch (nextParent) {
             | Some(parent) => getPath(parent)
             | _ => []
             },
        ];
      };
      finalPath := getPath(current);
    } else {
      // Get every neighbor of the current tile
      let neighbours = getNeighbours(~tiles, ~tile=current);
      Belt.Array.forEach(neighbours, neighbour
        // Check, if we havent already visited the current neighbour
        =>
          switch (neighbour) {
          | Some(neighbour) =>
            if (closedSet[neighbour.coordinates.x][neighbour.coordinates.y] === false && !isObstacle(~tile=neighbour)) {
              // newDistanceToNeigbour is the distance of the path from the start, through the current node, to the neighbour.
              let newDistanceToNeigbour =
                distanceCost[current.coordinates.x][current.coordinates.y] + getDistance(current, neighbour);

              // A* includes a remaining cost, the f cost. In this case we use manhattan distance to calculate the distance from
              // the neighbour to the end. We use manhattan again because A* works well when the g cost and f cost are balanced.
              // https://en.wikipedia.org/wiki/Taxicab_geometry
              let remaining = getDistance(neighbour, endTile);

              // Check if the neighbor is in the openList
              let isOpen =
                Belt.Array.some(openSet^, item => {
                  item.coordinates.x === neighbour.coordinates.x && item.coordinates.y === neighbour.coordinates.y
                });

              // If this new distance is the new shortest path to the current neighbour
              if (newDistanceToNeigbour < distanceCost[neighbour.coordinates.x][neighbour.coordinates.y] || !isOpen) {
                distanceCost[neighbour.coordinates.x][neighbour.coordinates.y] = newDistanceToNeigbour;
                remainingCost[neighbour.coordinates.x][neighbour.coordinates.y] = remaining;
                parent[neighbour.coordinates.x][neighbour.coordinates.y] = Some(current);

                if (!isOpen) {
                  let _newIndex = Js.Array.push(neighbour, openSet^);
                  ();
                };
              };
            }
          | None => ()
          }
        );
    };
  };

  List.length(finalPath^) > 0 ? Some(List.rev(finalPath^)) : None;
};
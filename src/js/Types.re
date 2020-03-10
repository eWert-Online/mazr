type gameObject =
  | None
  | Tree(Tree.t)
  | Plant(Plant.t)
  | Waypoint(Waypoint.t);

type selectables =
  | Sell
  | Building(gameObject);

type tileState =
  | Empty
  | Path;

type pathObject = {
  toBeacon: option(Grid.t),
  toEnd: option(Grid.t),
};

type mapTile = {
  coordinates: Grid.t,
  state: tileState,
  nextPath: pathObject,
  objects: gameObject,
};

type mobType =
  | Skeleton;

type mob = {
  id: float,
  coordinates: Grid.t,
  health: int,
  speed: int,
  typ: mobType,
};
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

type mapTile = {
  coordinates: Grid.t,
  state: tileState,
  nextPath: array(Grid.t),
  objects: gameObject,
};

type mobType =
  | Skeleton;

type mob = {
  coordinates: Grid.t,
  health: int,
  speed: int,
  typ: mobType,
};
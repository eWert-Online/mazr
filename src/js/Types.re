type gameObject =
  | NoBuilding
  | Tree(Object.Tree.t)
  | Plant(Object.Plant.t)
  | Waypoint(Object.Waypoint.t);

type selectables =
  | Sell
  | Building(gameObject);

type coordinates = {
  x: int,
  y: int,
};

module Mob = {
  type mobType =
    | Skeleton;

  type t = {
    id: float,
    coordinates,
    health: int,
    speed: int,
    typ: mobType,
  };
};

module Ui = {
  type t = {selectedElement: selectables};
};

module Path = {
  type pathObject = {
    toBeacon: option(coordinates),
    toEnd: option(coordinates),
  };

  type t = {
    inPath: bool,
    nextPath: pathObject,
  };
};

module Waypoints = {
  type t = {
    startNode: option(coordinates),
    endNode: option(coordinates),
    beacon: option(coordinates),
  };
};

module Grid = {
  type tile = {
    coordinates,
    path: Path.t,
    entity: gameObject,
  };

  type t = {
    waypoints: Waypoints.t,
    tiles: array(array(tile)),
  };
};
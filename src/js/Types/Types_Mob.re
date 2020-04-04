type mobType =
  | Skeleton
  | Bunny;

type t = {
  id: float,
  coordinates: (int, int),
  health: int,
  speed: int,
  typ: mobType,
};
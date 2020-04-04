type tile = {
  coordinates: (int, int),
  path: Types_Path.t,
  entity: Types_Objects.t,
};

type t = array(array(tile));
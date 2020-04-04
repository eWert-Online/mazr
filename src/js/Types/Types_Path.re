type pathObject = {
  toBeacon: option((int, int)),
  toEnd: option((int, int)),
};

type t = {
  inPath: bool,
  nextPath: pathObject,
};
type t = Types.mob;

let make = (~coordinates) => {
  let mob: t = {coordinates, health: 100, speed: 500, typ: Types.Skeleton};
  mob;
};
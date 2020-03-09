[@bs.val] [@bs.scope "window"] external innerWidth: int = "innerWidth";

type t = {
  x: int,
  y: int,
};

let width = 50;
let height = 25;

let tileSize = float_of_int(innerWidth) /. float_of_int(width);

let grid = Array.init(width, x => Array.init(height, y => {{x, y}}));
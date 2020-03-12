type t = {
  x: int,
  y: int,
};

let width = 50;
let height = 25;

let grid = Array.init(width, x => Array.init(height, y => {{x, y}}));
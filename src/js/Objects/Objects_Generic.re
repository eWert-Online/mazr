module Styles = {
  open Css;

  let gameObject =
    style([
      position(absolute),
      top(zero),
      bottom(zero),
      left(zero),
      right(zero),
      display(block),
      backgroundSize(contain),
      backgroundPosition(center),
      backgroundRepeat(noRepeat),
    ]);
};
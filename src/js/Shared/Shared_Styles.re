let filled =
  Css.(
    style([
      position(absolute),
      top((-1)->px),
      bottom((-1)->px),
      left((-1)->px),
      right((-1)->px),
      display(block),
      backgroundSize(contain),
      backgroundPosition(center),
      backgroundRepeat(noRepeat),
      pointerEvents(none),
    ])
  );

let gridEntity =
  Css.(
    style([
      position(absolute),
      top(0->px),
      left(0->px),
      unsafe("width", "calc(100% / " ++ string_of_int(Settings.map_width) ++ ")"),
      display(block),
      margin(auto),
      // overflow(hidden),
      pointerEvents(none),
      selector(
        "&::before",
        [contentRule(`text("")), pointerEvents(none), display(block), paddingTop(100.0->pct)],
      ),
    ])
  );

let gridEntityCoords = (coordinates: (int, int)) => {
  let (x, y) = coordinates;
  Css.(
    merge([
      gridEntity,
      style([transforms([translate((float_of_int(x) *. 100.0)->pct, (float_of_int(y) *. 100.0)->pct)])]),
    ])
  );
};
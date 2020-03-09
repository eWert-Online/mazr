module Styles = {
  open Css;

  let mob =
    style([
      position(absolute),
      top(0->px),
      left(0->px),
      width(Grid.tileSize->pxFloat),
      display(block),
      margin(auto),
      transitionProperty("all"),
      transitionTimingFunction(linear),
      backgroundPosition4(~x=`left, ~y=`top, ~offsetX=0->px, ~offsetY=0->px),
      backgroundRepeat(noRepeat),
      selector("&::before", [contentRule(`text("")), display(block), paddingTop(100.0->pct)]),
    ]);
};

[@react.component]
let make = (~mob: Types.mob, ~tiles: array(array(Mazr.Types.mapTile))) => {
  let mobType = Css.(style([backgroundImage(url("/images/characters/skeleton.png"))]));

  let (coordinate, setCoordinate) =
    React.useState(() => {
      let coord: Grid.t = {x: mob.coordinates.x, y: mob.coordinates.y};
      coord;
    });

  let (hasBeacon, setHasBeacon) = React.useState(() => false);

  React.useEffect3(
    () => {
      let currentTile = tiles[coordinate.x][coordinate.y];
      let id =
        Js.Global.setTimeout(
          () => {
            switch (Array.length(currentTile.nextPath)) {
            | 1 => setCoordinate(_ => {currentTile.nextPath[0]})
            | 2 =>
              if (hasBeacon) {
                setCoordinate(_ => {currentTile.nextPath[1]});
              } else {
                setCoordinate(_ => {currentTile.nextPath[0]});
              }
            | _ => ()
            }
          },
          mob.speed,
        );

      switch (currentTile.objects) {
      | Waypoint(Beacon) =>
        setHasBeacon(hadBeacon =>
          if (!hadBeacon) {
            true;
          } else {
            hadBeacon;
          }
        )
      | _ => ()
      };
      Some(() => {Js.Global.clearTimeout(id)});
    },
    (coordinate.x, coordinate.y, hasBeacon),
  );

  let calculatedStyle =
    Css.(
      style([
        transforms([
          translate(
            (float_of_int(coordinate.x) *. Grid.tileSize)->pxFloat,
            (float_of_int(coordinate.y) *. Grid.tileSize)->pxFloat,
          ),
          translateY((-33.0)->pct),
        ]),
        transitionDuration(mob.speed),
      ])
    );

  <div className={Css.merge([Styles.mob, mobType, calculatedStyle])} />;
};
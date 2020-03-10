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
      overflow(hidden),
      transitionProperty("all"),
      transitionTimingFunction(linear),
      selector("&::before", [contentRule(`text("")), display(block), paddingTop(100.0->pct)]),
    ]);
};

type positions = {
  prev: Grid.t,
  current: Grid.t,
};

[@react.component]
let make = (~mob: Types.mob, ~tiles: array(array(Mazr.Types.mapTile))) => {
  let (positions, setPositions) =
    React.useState(() => {
      let coord: positions = {
        prev: {
          x: mob.coordinates.x,
          y: mob.coordinates.y,
        },
        current: {
          x: mob.coordinates.x,
          y: mob.coordinates.y,
        },
      };
      coord;
    });

  let (hasBeacon, setHasBeacon) = React.useState(() => false);

  React.useEffect3(
    () => {
      let currentTile = tiles[positions.current.x][positions.current.y];
      let id =
        Js.Global.setTimeout(
          () => {
            let nextPathLength = Array.length(currentTile.nextPath);
            if (nextPathLength > 0) {
              if (hasBeacon && nextPathLength === 2) {
                setPositions(positions => {prev: positions.current, current: currentTile.nextPath[1]});
              } else {
                setPositions(positions => {prev: positions.current, current: currentTile.nextPath[0]});
              };
            };
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
    (positions.current.x, positions.current.y, hasBeacon),
  );

  let calculatedStyle =
    Css.(
      style([
        transforms([
          translate(
            (float_of_int(positions.current.x) *. Grid.tileSize)->pxFloat,
            (float_of_int(positions.current.y) *. Grid.tileSize)->pxFloat,
          ),
          translateY((-30.0)->pct),
        ]),
        transitionDuration(mob.speed),
      ])
    );

  <div className={Css.merge([Styles.mob, calculatedStyle])}>
    {switch (mob.typ) {
     | Skeleton =>
       <Mobs_Skeleton
         animation={
           switch (positions.current.x, positions.current.y, positions.prev.x, positions.prev.y) {
           | (currentX, _currentY, prevX, _prevY) when currentX < prevX => Mobs_Skeleton.Animations.walkLeft // LEFT
           | (currentX, _currentY, prevX, _prevY) when currentX > prevX => Mobs_Skeleton.Animations.walkRight // RIGHT
           | (_currentX, currentY, _prevX, prevY) when currentY > prevY => Mobs_Skeleton.Animations.walkDown // DOWN
           | (_currentX, currentY, _prevX, prevY) when currentY < prevY => Mobs_Skeleton.Animations.walkUp // UP
           | _ => ""
           }
         }
       />
     }}
  </div>;
};
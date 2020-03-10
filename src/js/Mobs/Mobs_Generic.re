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
  prev: option(Grid.t),
  current: Grid.t,
  next: option(Grid.t),
};

[@react.component]
let make = (~mob: Types.mob, ~tiles: array(array(Mazr.Types.mapTile)), ~despawn) => {
  let (positions, setPositions) =
    React.useState(() => {
      let coord: positions = {
        prev: None,
        current: {
          x: mob.coordinates.x,
          y: mob.coordinates.y,
        },
        next: {
          let nextTile = tiles[mob.coordinates.x][mob.coordinates.y];
          nextTile.nextPath.toBeacon;
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
            let newPrev = positions.current;

            let newCurrent =
              switch (currentTile.nextPath.toBeacon, currentTile.nextPath.toEnd, hasBeacon) {
              | (Some(pathToBeacon), None, _) => pathToBeacon
              | (None, Some(pathToEnd), _) => pathToEnd
              | (None, None, _) => currentTile.coordinates
              | (Some(_pathToBeacon), Some(pathToEnd), true) => pathToEnd
              | (Some(pathToBeacon), Some(_pathToEnd), false) => pathToBeacon
              };

            let newCurrentTile = tiles[newCurrent.x][newCurrent.y];
            let currentIsBeacon =
              switch (newCurrentTile.objects) {
              | Waypoint(Beacon) => true
              | _ => false
              };
            let newNext =
              switch (newCurrentTile.nextPath.toBeacon, newCurrentTile.nextPath.toEnd, hasBeacon || currentIsBeacon) {
              | (Some(pathToBeacon), None, _) => Some(pathToBeacon)
              | (None, Some(pathToEnd), _) => Some(pathToEnd)
              | (Some(_pathToBeacon), Some(pathToEnd), true) => Some(pathToEnd)
              | (Some(pathToBeacon), Some(_pathToEnd), false) => Some(pathToBeacon)
              | (None, None, _) => None
              };

            if (currentIsBeacon) {
              setHasBeacon(_ => true);
            };

            setPositions(_positions => {prev: Some(newPrev), current: newCurrent, next: newNext});
          },
          mob.speed,
        );
      Some(() => {Js.Global.clearTimeout(id)});
    },
    (positions.current.x, positions.current.y, hasBeacon),
  );

  React.useEffect1(
    () => {
      let id =
        Js.Global.setTimeout(
          () => {
            switch (positions.next) {
            | Some(_) => ()
            | None => despawn(~id=mob.id)
            }
          },
          mob.speed,
        );
      Some(() => {Js.Global.clearTimeout(id)});
    },
    [|positions.next|],
  );

  let calculatedStyle =
    Css.(
      style([
        transforms([
          translate(
            (float_of_int(positions.current.x) *. 100.0)->pct,
            (float_of_int(positions.current.y) *. 100.0)->pct,
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
           switch (positions.current, positions.prev, positions.next) {
           | (current, Some(prev), _next) when current.x < prev.x => Mobs_Skeleton.Animations.walkLeft // LEFT
           | (current, Some(prev), _next) when current.x > prev.x => Mobs_Skeleton.Animations.walkRight // RIGHT
           | (current, Some(prev), _next) when current.y > prev.y => Mobs_Skeleton.Animations.walkDown // DOWN
           | (current, Some(prev), _next) when current.y < prev.y => Mobs_Skeleton.Animations.walkUp // UP
           | _ => ""
           }
         }
       />
     }}
  </div>;
};
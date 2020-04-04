module Skeleton = Mob_Skeleton;
module Bunny = Mob_Bunny;

module Styles = {
  open Css;

  let mob =
    merge([Shared.Styles.gridEntity, style([transitionProperty("all"), transitionTimingFunction(linear)])]);
};

[@react.component]
let make = (~mob: Types.Mob.t, ~path: array((int, int)), ~dispatch) => {
  let prevCoordinates = React.useRef(mob.coordinates);
  let upcomingPath = React.useRef(path);
  // let alreadyWalkedPath = React.useRef([]);

  React.useEffect1(
    () => {
      let path = React.Ref.current(upcomingPath);
      let coordinates = Js.Array.shift(path);

      switch (coordinates) {
      | Some(coordinates) => React.Ref.setCurrent(prevCoordinates, coordinates)
      | None => ()
      };
      React.Ref.setCurrent(upcomingPath, path);
      None;
    },
    [|mob.coordinates|],
  );

  React.useEffect1(
    () => {
      // Find a new path in here...
      None
    },
    [|path|],
  );

  Hooks.useInterval(
    () => {
      // find next path and move to new coordinates
      let upcomingPath = React.Ref.current(upcomingPath);
      let currentCoordinates = Belt.Array.get(upcomingPath, 0);
      switch (currentCoordinates) {
      | Some(newCoordinates) => dispatch(ActionTypes.MOVE_MOB(mob.id, newCoordinates))
      | None => dispatch(ActionTypes.DESPAWN_MOB(mob.id))
      };
    },
    mob.speed,
  );

  React.useMemo4(
    () => {
      <div
        className={Css.merge([
          Styles.mob,
          Css.(
            style([
              transforms([Shared.Functions.translateTo(mob.coordinates), translateY((-30.0)->pct)]),
              transitionDuration(mob.speed),
            ])
          ),
        ])}>
        {switch (mob.typ) {
         | Skeleton =>
           <Skeleton
             animation={
               switch (mob.coordinates, React.Ref.current(prevCoordinates)) {
               | ((currentX, _), (prevX, _)) when currentX < prevX => Skeleton.Animations.walkLeft
               | ((currentX, _), (prevX, _)) when currentX > prevX => Skeleton.Animations.walkRight
               | ((_, currentY), (_, prevY)) when currentY > prevY => Skeleton.Animations.walkDown
               | ((_, currentY), (_, prevY)) when currentY < prevY => Skeleton.Animations.walkUp
               | _ => ""
               }
             }
           />
         | Bunny =>
           <Bunny
             animation={
               switch (mob.coordinates, React.Ref.current(prevCoordinates)) {
               | ((currentX, _), (prevX, _)) when currentX < prevX => Bunny.Animations.walkLeft
               | ((currentX, _), (prevX, _)) when currentX > prevX => Bunny.Animations.walkRight
               | ((_, currentY), (_, prevY)) when currentY > prevY => Bunny.Animations.walkDown
               | ((_, currentY), (_, prevY)) when currentY < prevY => Bunny.Animations.walkUp
               | _ => ""
               }
             }
           />
         }}
      </div>
    },
    (mob.speed, mob.typ, mob.coordinates, prevCoordinates),
  );
};
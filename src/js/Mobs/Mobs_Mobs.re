module Styles = {
  open Css;

  let map = style([display(`flex), flexWrap(nowrap), alignItems(center), justifyContent(center)]);
  let gridCell =
    style([
      position(relative),
      display(block),
      width(Grid.tileSize->pxFloat),
      selector("&::before", [contentRule(`text("")), display(block), paddingTop(100.0->pct)]),
    ]);
};

[@react.component]
let make = (~spawn: Types.mapTile, ~tiles) => {
  let (mobs, setMobs) =
    React.useState(() => {
      let mobsArray: array(Types.mob) = [||];
      mobsArray;
    });

  React.useEffect(() => {
    let timer =
      Js.Global.setInterval(
        () => {
          setMobs(mobs => {
            let newMob = Mobs_Skeleton.init(~coordinates=spawn.coordinates);
            Belt.Array.concat(mobs, [|newMob|]);
          })
        },
        4000,
      );

    Some(() => Js.Global.clearInterval(timer));
  });

  let despawn = (~id) => {
    setMobs(mobs => {Belt.Array.keep(mobs, mob => {mob.id !== id})});
  };

  Belt.Array.map(mobs, mob => {<Mobs_Generic key={Js.Float.toString(mob.id)} mob tiles despawn />})->React.array;
};
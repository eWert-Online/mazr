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
        8000,
      );

    Some(() => Js.Global.clearInterval(timer));
  });

  let despawn = (~id) => {
    setMobs(mobs => {Belt.Array.keep(mobs, mob => {mob.id !== id})});
  };

  Belt.Array.mapWithIndex(mobs, (index, mob) => {<Mobs_Generic key={string_of_int(index)} mob tiles despawn />})
  ->React.array;
};
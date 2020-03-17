module Styles = {
  open Css;

  let gameWrapper =
    style([
      display(`flex),
      alignItems(flexStart),
      justifyContent(center),
      backgroundImage(linearGradient(180.0->deg, [(zero, hex("06060c")), (100.0->pct, hex("080811"))])),
      width(100.0->vw),
      height(100.0->vh),
    ]);

  let game =
    style([
      position(relative),
      display(`flex),
      flexDirection(column),
      width(100.0->pct),
      unsafe(
        "maxWidth",
        "calc((100vh - 80px - 10px) * ("
        ++ string_of_int(Settings.map_width)
        ++ " / "
        ++ string_of_int(Settings.map_height)
        ++ "))",
      ),
    ]);
};

[@react.component]
let make = () => {
  <GameContext>
    <div className=Styles.gameWrapper> <div className=Styles.game> <Map /> <Mobs /> <Ui /> </div> </div>
  </GameContext>;
};
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
        "calc((100vh - 80px - 10px) * (" ++ string_of_int(Grid.width) ++ " / " ++ string_of_int(Grid.height) ++ "))",
      ),
    ]);
};

[@react.component]
let make = () => {
  let (selectedElement, setSelectedElement) = React.useState(_ => Types.Building(Tree(DarkGreen)));
  let (startNode, setStartNode) = React.useState(_ => None);
  let (endNode, setEndNode) = React.useState(_ => None);
  let (beacon, setBeacon) = React.useState(_ => None);

  let value: GameContext.t = {
    startNode,
    setStartNode,

    endNode,
    setEndNode,

    beacon,
    setBeacon,

    selectedElement,
    setSelectedElement,

    playing:
      switch (startNode, beacon, endNode) {
      | (Some(_), Some(_), Some(_)) => true
      | _ => false
      },
  };

  <GameContext value>
    <div className=Styles.gameWrapper> <div className=Styles.game> <Map /> <Ui /> </div> </div>
  </GameContext>;
};
module Styles = {
  open Css;

  let gameWrapper =
    style([
      display(`flex),
      flexDirection(column),
      backgroundImage(url("/images/abyss.png")),
      height(100.0->pct),
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

  <GameContext value> <div className=Styles.gameWrapper> <Map /> <Ui /> </div> </GameContext>;
};
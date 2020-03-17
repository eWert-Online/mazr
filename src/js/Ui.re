module Button = Ui_Button;

module Styles = {
  open Css;

  let toolbar =
    style([
      height(80->px),
      flexGrow(1.0),
      alignSelf(center),
      display(`flex),
      alignItems(center),
      justifyContent(center),
      padding2(~v=15->px, ~h=30->px),
    ]);
};

[@react.component]
let make = () => {
  let (state, dispatch) = React.useContext(GameContext.context);

  let selectElement = element => {
    dispatch(ActionTypes.SET_SELECTED_ELEMENT(element));
  };

  let spawnMob = mob => {
    dispatch(ActionTypes.SPAWN_MOB(mob));
  };

  <div className=Styles.toolbar>
    {switch (state.grid.waypoints.startNode, state.grid.waypoints.beacon, state.grid.waypoints.endNode) {
     | (None, _, _) =>
       <Button
         active={
           switch (state.grid.waypoints.startNode) {
           | Some(_) => false
           | _ => true
           }
         }
         icon="/images/objects/hole.png"
         onClick={_ => ()}>
         "Startpunkt"->React.string
       </Button>
     | (_, None, _) =>
       <Button
         active={
           switch (state.grid.waypoints.beacon) {
           | Some(_) => false
           | _ => true
           }
         }
         icon="/images/objects/key.png"
         onClick={_ => ()}>
         "Wegpunkt"->React.string
       </Button>
     | (_, _, None) =>
       <Button
         active={
           switch (state.grid.waypoints.endNode) {
           | Some(_) => false
           | _ => true
           }
         }
         icon="/images/objects/chest.png"
         onClick={_ => ()}>
         "Zielpunkt"->React.string
       </Button>
     | (Some(startNode), Some(_beacon), Some(_endNode)) =>
       <React.Fragment>
         <Button
           active={
             switch (state.ui.selectedElement) {
             | Types.Building(Tree(DarkGreen)) => true
             | _ => false
             }
           }
           icon="/images/objects/tree_darkgreen.png"
           onClick={_ => selectElement(Types.Building(Tree(DarkGreen)))}>
           "Baum"->React.string
         </Button>
         <Button
           active={
             switch (state.ui.selectedElement) {
             | Sell => true
             | _ => false
             }
           }
           icon="/images/objects/gold.png"
           onClick={_ => selectElement(Types.Sell)}>
           "Verkaufen"->React.string
         </Button>
         <Button
           active=false
           icon="/images/objects/skeleton.png"
           onClick={_ => spawnMob(Mob_Skeleton.init(~coordinates=startNode))}>
           "Skelett"->React.string
         </Button>
       </React.Fragment>
     }}
  </div>;
};
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
  let context = React.useContext(GameContext.context);

  let selectElement = element => {
    context.setSelectedElement(_ => element);
  };

  <div className=Styles.toolbar>
    {switch (context.startNode, context.beacon, context.endNode) {
     | (None, None, None) =>
       <UiButton
         active={
           switch (context.startNode) {
           | Some(_) => false
           | _ => true
           }
         }
         icon="/images/objects/hole.png"
         onClick={_ => ()}>
         "Startpunkt"->React.string
       </UiButton>
     | (Some(_), None, None) =>
       <UiButton
         active={
           switch (context.beacon) {
           | Some(_) => false
           | _ => true
           }
         }
         icon="/images/objects/key.png"
         onClick={_ => ()}>
         "Wegpunkt"->React.string
       </UiButton>
     | (Some(_), Some(_), None) =>
       <UiButton
         active={
           switch (context.endNode) {
           | Some(_) => false
           | _ => true
           }
         }
         icon="/images/objects/chest.png"
         onClick={_ => ()}>
         "Zielpunkt"->React.string
       </UiButton>
     | _ =>
       <React.Fragment>
         <UiButton
           active={
             switch (context.selectedElement) {
             | Types.Building(Tree(DarkGreen)) => true
             | _ => false
             }
           }
           icon="/images/objects/tree_darkgreen.png"
           onClick={_ => selectElement(Types.Building(Tree(DarkGreen)))}>
           "Baum"->React.string
         </UiButton>
         <UiButton
           active={
             switch (context.selectedElement) {
             | Sell => true
             | _ => false
             }
           }
           icon="/images/objects/gold.png"
           onClick={_ => selectElement(Types.Sell)}>
           "Verkaufen"->React.string
         </UiButton>
       </React.Fragment>
     }}
  </div>;
};
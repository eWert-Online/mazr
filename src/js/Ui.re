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
let make = (~state: Reducers.Ui.t, ~actions: Reducers.Actions.t) => {
  <div className=Styles.toolbar>
    <Button
      active={
        switch (state.selectedElement) {
        | Object(Tree(DarkGreen)) => true
        | _ => false
        }
      }
      icon="/images/objects/tree_darkgreen.png"
      onClick={_ => actions.selectElement(Object(Tree(DarkGreen)))}>
      "Baum"->React.string
    </Button>
    <Button
      active={
        switch (state.selectedElement) {
        | Sell => true
        | _ => false
        }
      }
      icon="/images/objects/gold.png"
      onClick={_ => actions.selectElement(Sell)}>
      "Verkaufen"->React.string
    </Button>
    <Button
      active={
        switch (state.selectedElement) {
        | Object(Tower(Fire)) => true
        | _ => false
        }
      }
      icon="/images/towers/fire.png"
      onClick={_ => actions.selectElement(Object(Tower(Fire)))}>
      "Tower"->React.string
    </Button>
    <Button active=false icon="/images/objects/skeleton.png" onClick={_ => actions.spawnMob(Mob.Skeleton.init)}>
      "Skelett"->React.string
    </Button>
    <Button active=false icon="/images/objects/bunny.png" onClick={_ => actions.spawnMob(Mob.Bunny.init)}>
      "Bunny"->React.string
    </Button>
  </div>;
};
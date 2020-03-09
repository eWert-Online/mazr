module Styles = {
  open Css;

  let toolbar = style([display(`flex), alignItems(center), padding(15->px), flexGrow(1.0)]);
  let button =
    style([
      height(40->px),
      width(40->px),
      display(`flex),
      alignItems(center),
      justifyContent(center),
      backgroundColor(transparent),
      borderStyle(none),
      marginRight(15->px),
      cursor(`pointer),
      backgroundImage(url("/images/ui/sign.png")),
      backgroundRepeat(noRepeat),
      backgroundSize(cover),
    ]);
};

[@react.component]
let make = () => {
  let context = React.useContext(GameContext.context);

  let selectElement = element => {
    context.setSelectedElement(_ => element);
  };

  <div className=Styles.toolbar>
    <button
      className={Css.merge([
        Styles.button,
        Css.(
          style([
            switch (context.selectedElement) {
            | Building(Tree(DarkGreen)) => backgroundImage(url("/images/ui/sign_tree_active.png"))
            | _ => backgroundImage(url("/images/ui/sign_tree.png"))
            },
          ])
        ),
      ])}
      onClick={_ => selectElement(Types.Building(Tree(DarkGreen)))}
    />
    <button
      className={Css.merge([
        Styles.button,
        Css.(
          style([
            switch (context.selectedElement) {
            | Sell => backgroundImage(url("/images/ui/sign_sell_active.png"))
            | _ => backgroundImage(url("/images/ui/sign_sell.png"))
            },
          ])
        ),
      ])}
      onClick={_ => selectElement(Types.Sell)}
    />
  </div>;
};
module Styles = {
  open Css;

  let button =
    style([
      color(hex("ffffff")),
      fontSize(14->px),
      backgroundColor(hex("654f3c")),
      position(relative),
      display(`flex),
      alignItems(center),
      justifyContent(center),
      border(1->px, solid, hex("75604e")),
      borderRadius(3->px),
      cursor(`pointer),
      marginTop(30->px),
      marginLeft(15->px),
      marginRight(15->px),
      padding2(~v=2->px, ~h=10->px),
      selector(
        "&::before",
        [
          contentRule(`text("")),
          display(block),
          height(40->px),
          width(40->px),
          backgroundRepeat(noRepeat),
          backgroundSize(contain),
          backgroundPosition(`bottom),
          position(absolute),
          top(zero),
          left(zero),
          right(zero),
          margin(auto),
          transform(translateY((-80.0)->pct)),
        ],
      ),
    ]);
};

[@react.component]
let make = (~icon, ~active, ~onClick: unit => unit, ~children) => {
  let icon = Css.(style([selector("&::before", [backgroundImage(url(icon))])]));
  let active =
    active
      ? Css.(
          style([
            selector(
              "&::after",
              [
                contentRule(`text("")),
                display(block),
                border(2->px, solid, hex("ffffff")),
                borderRadius(50.0->pct),
                width(10->px),
                position(absolute),
                bottom(zero),
                left(zero),
                right(zero),
                margin(auto),
                transform(translateY(10->px)),
              ],
            ),
          ])
        )
      : "";

  <button className={Css.merge([Styles.button, icon, active])} onClick={_ => onClick()}> children </button>;
};
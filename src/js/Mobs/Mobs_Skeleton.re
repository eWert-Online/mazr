module Animations = {
  open Css;

  let walkUp =
    style([
      transform(translateY(0.0->pct)),
      animationName(keyframes([(100, [transforms([translateY(0.0->pct), translateX((-100.0)->pct)])])])),
    ]);
  let walkLeft =
    style([
      transform(translateY((-25.0)->pct)),
      animationName(keyframes([(100, [transforms([translateY((-25.0)->pct), translateX((-100.0)->pct)])])])),
    ]);
  let walkRight =
    style([
      transform(translateY((-75.0)->pct)),
      animationName(keyframes([(100, [transforms([translateY((-75.0)->pct), translateX((-100.0)->pct)])])])),
    ]);
  let walkDown =
    style([
      transform(translateY((-50.0)->pct)),
      animationName(keyframes([(100, [transforms([translateY((-50.0)->pct), translateX((-100.0)->pct)])])])),
    ]);
};

module Styles = {
  open Css;

  let mob = style([position(absolute), top(zero), bottom(zero), left(zero), right(zero), overflow(hidden)]);

  let texture =
    style([
      display(block),
      width(900.0->pct),
      height(400.0->pct),
      animationDuration(800),
      animationIterationCount(infinite),
      animationTimingFunction(steps(9, `end_)),
    ]);
};

type t = Types.mob;

let init = (~coordinates) => {
  let mob: t = {id: Js.Date.now(), coordinates, health: 100, speed: 500, typ: Types.Skeleton};
  mob;
};

[@react.component]
let make = (~animation) => {
  <div className={Css.merge([Styles.mob])}>
    <img className={Css.merge([Styles.texture, animation])} src="/images/characters/skeleton.png" />
  </div>;
};
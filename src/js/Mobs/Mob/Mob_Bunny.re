type t = Types.Mob.t;
let health = 60;
let speed = 400;

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
      width(800.0->pct),
      height(400.0->pct),
      animationDuration(speed),
      animationIterationCount(infinite),
      animationTimingFunction(steps(8, `end_)),
    ]);
};

let init = coordinates => {
  let mob: t = {id: Js.Date.now(), coordinates, health, speed, typ: Types.Mob.Bunny};
  mob;
};

[@react.component]
let make = (~animation) => {
  <div className={Css.merge([Styles.mob])}>
    <img className={Css.merge([Styles.texture, animation])} src="/images/characters/bunny.png" />
  </div>;
};
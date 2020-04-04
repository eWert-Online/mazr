type turnType =
  | Bottom_Left
  | Left_Top
  | Top_Right
  | Right_Bottom;

type endType =
  | Top
  | Right
  | Bottom
  | Left;

type t =
  | Dot
  | Vertical
  | Horizontal
  | Turn(turnType)
  | End(endType);

[@react.component]
let make = (~pathType: t) => {
  let pathType =
    switch (pathType) {
    | Dot => Css.(style([]))
    | Horizontal => Css.(style([backgroundImage(url("/images/path/dirt/horizontal.png"))]))
    | Vertical => Css.(style([backgroundImage(url("/images/path/dirt/vertical.png"))]))

    | Turn(Bottom_Left) => Css.(style([backgroundImage(url("/images/path/dirt/turn_bottom_left.png"))]))
    | Turn(Left_Top) => Css.(style([backgroundImage(url("/images/path/dirt/turn_left_top.png"))]))
    | Turn(Top_Right) => Css.(style([backgroundImage(url("/images/path/dirt/turn_top_right.png"))]))
    | Turn(Right_Bottom) => Css.(style([backgroundImage(url("/images/path/dirt/turn_right_bottom.png"))]))

    | End(Top) => Css.(style([backgroundImage(url("/images/path/dirt/vertical.png"))]))
    | End(Right) => Css.(style([backgroundImage(url("/images/path/dirt/horizontal.png"))]))
    | End(Bottom) => Css.(style([backgroundImage(url("/images/path/dirt/vertical.png"))]))
    | End(Left) => Css.(style([backgroundImage(url("/images/path/dirt/horizontal.png"))]))
    };

  <div className={Css.merge([Shared.Styles.filled, pathType])} />;
};
type t =
  | StartNode
  | Beacon
  | EndNode;

[@react.component]
let make = (~waypointType: t) => {
  let waypointType =
    switch (waypointType) {
    | StartNode => Css.(style([zIndex(10), backgroundImage(url("/images/objects/hole.png"))]))
    | Beacon => Css.(style([zIndex(10), backgroundImage(url("/images/objects/key.png"))]))
    | EndNode => Css.(style([zIndex(10), backgroundImage(url("/images/objects/chest.png"))]))
    };

  <div className={Css.merge([Shared.Styles.filled, waypointType])} />;
};
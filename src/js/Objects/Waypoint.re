type t =
  | StartNode
  | Beacon
  | EndNode;

[@react.component]
let make = (~waypointType: t) => {
  let waypointType =
    switch (waypointType) {
    | StartNode => Css.(style([backgroundImage(url("/images/objects/hole.png"))]))
    | Beacon => Css.(style([backgroundImage(url("/images/objects/key.png"))]))
    | EndNode => Css.(style([backgroundImage(url("/images/objects/chest.png"))]))
    };

  <div className={Css.merge([Objects_Generic.Styles.gameObject, waypointType])} />;
};
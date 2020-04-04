type t =
  | LightGreen
  | DarkGreen
  | Trunk;

[@react.component]
let make = (~treeType: t) => {
  let treeType =
    switch (treeType) {
    | DarkGreen => Css.(style([backgroundImage(url("/images/objects/tree_darkgreen.png"))]))
    | LightGreen => Css.(style([backgroundImage(url("/images/objects/tree_green.png"))]))
    | Trunk => Css.(style([backgroundImage(url("/images/objects/tree_trunk.png"))]))
    };

  <div className={Css.merge([Shared.Styles.filled, treeType])} />;
};
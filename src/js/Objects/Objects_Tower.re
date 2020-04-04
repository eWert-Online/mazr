type t =
  | Fire;

[@react.component]
let make = (~towerType: t) => {
  let towerType =
    switch (towerType) {
    | Fire => Css.(style([backgroundImage(url("/images/towers/fire.png"))]))
    };

  <div className={Css.merge([Shared.Styles.filled, towerType])} />;
};
type t =
  | HighGrass;

[@react.component]
let make = (~plantType: t) => {
  let plantType =
    switch (plantType) {
    | HighGrass => Css.(style([backgroundImage(url("/images/objects/high_grass.png"))]))
    };

  <div className={Css.merge([Objects_Generic.Styles.gameObject, plantType])} />;
};
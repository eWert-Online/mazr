module Styles = {
  open Css;

  let gameWrapper =
    style([
      display(`flex),
      alignItems(flexStart),
      justifyContent(center),
      backgroundImage(linearGradient(180.0->deg, [(zero, hex("06060c")), (100.0->pct, hex("080811"))])),
      width(100.0->vw),
      height(100.0->vh),
    ]);

  let game =
    style([
      position(relative),
      display(`flex),
      flexDirection(column),
      width(100.0->pct),
      unsafe(
        "maxWidth",
        "calc((100vh - 80px - 10px) * ("
        ++ string_of_int(Settings.map_width)
        ++ " / "
        ++ string_of_int(Settings.map_height)
        ++ "))",
      ),
    ]);
};

[@react.component]
let make = () => {
  let (state, dispatch, actions) = Reducers.make();

  <div className=Styles.gameWrapper>
    <div className=Styles.game>
      {React.useMemo1(() => {<Layers.Base state={state.general} actions />}, [|state.general|])}
      {React.useMemo1(() => {<Layers.Decorations state={state.decorations} />}, [|state.decorations|])}
      {React.useMemo4(
         () => {<Layers.Path state={state.path} />},
         (state.path.startNode, state.path.beacon, state.path.endNode, state.path.calculatedPath),
       )}
      {React.useMemo1(() => {<Layers.Objects state={state.objects} />}, [|state.objects|])}
      {React.useMemo2(
         () => {<Layers.Mobs state={state.mobs} calculatedPath={state.path.calculatedPath} dispatch />},
         (state.mobs, state.path.calculatedPath),
       )}
      {React.useMemo1(() => {<Ui state={state.ui} actions />}, [|state.ui|])}
    </div>
  </div>;
};
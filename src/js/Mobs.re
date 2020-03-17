[@react.component]
let make = () => {
  let (state, _dispatch) = React.useContext(GameContext.context);

  React.useMemo1(
    () => {Belt.Array.map(state.mobs, mob => {<Mob key={Js.Float.toString(mob.id)} mob />})->React.array},
    [|state.mobs|],
  );
};
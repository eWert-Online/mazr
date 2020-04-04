[@react.component]
let make = (~state: Reducers.Mob.t, ~calculatedPath, ~dispatch: ActionTypes.t => unit) => {
  Belt.Array.map(state, mob => {<Mob key={Js.Float.toString(mob.id)} mob path=calculatedPath dispatch />})
  ->React.array;
};
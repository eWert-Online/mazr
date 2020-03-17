type t = Reducers.Mob.t;

let context: React.Context.t(t) = React.createContext(Reducers.Mob.initialState);

let init = () => {
  React.useReducer((state, action) => {Reducers.Mob.make(~state, ~action)}, Reducers.Mob.initialState);
};

[@react.component]
let make = (~children, ~value) => {
  React.createElement(React.Context.provider(context), {"value": value, "children": children});
};
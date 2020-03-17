type t = (Reducers.t, ActionTypes.t => unit);

let context: React.Context.t(t) = React.createContext((Reducers.initialState, _ => ()));

[@react.component]
let make = (~children) => {
  let value = React.useReducer((state, action) => {Reducers.make(~state, ~action)}, Reducers.initialState);

  React.createElement(React.Context.provider(context), {"value": value, "children": children});
};
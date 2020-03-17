type t = Reducers.Grid.t;

let context: React.Context.t(t) = React.createContext(Reducers.Grid.initialState);

let init = () => {
  React.useReducer((state, action) => {Reducers.Grid.make(~state, ~action)}, Reducers.Grid.initialState);
};

[@react.component]
let make = (~children, ~value) => {
  React.createElement(React.Context.provider(context), {"value": value, "children": children});
};
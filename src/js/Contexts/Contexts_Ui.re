type t = Reducers.Ui.t;

let context: React.Context.t(t) = React.createContext(Reducers.Ui.initialState);

let init = () => {
  React.useReducer((state, action) => {Reducers.Ui.make(~state, ~action)}, Reducers.Ui.initialState);
};

[@react.component]
let make = (~children, ~value) => {
  React.createElement(React.Context.provider(context), {"value": value, "children": children});
};
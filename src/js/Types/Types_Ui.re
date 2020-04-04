type selectables =
  | Sell
  | Object(Types_Objects.t);

type t = {
  selectedElement: selectables,
  gold: int,
  wood: int,
};
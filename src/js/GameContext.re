type t = {
  startNode: option(Types.mapTile),
  setStartNode: (option(Types.mapTile) => option(Types.mapTile)) => unit,
  endNode: option(Types.mapTile),
  setEndNode: (option(Types.mapTile) => option(Types.mapTile)) => unit,
  beacon: option(Types.mapTile),
  setBeacon: (option(Types.mapTile) => option(Types.mapTile)) => unit,
  selectedElement: Types.selectables,
  setSelectedElement: (Types.selectables => Types.selectables) => unit,
  playing: bool,
};

let context: React.Context.t(t) =
  React.createContext({
    startNode: None,
    setStartNode: _ => (),

    endNode: None,
    setEndNode: _ => (),

    beacon: None,
    setBeacon: _ => (),

    selectedElement: Building(Tree(DarkGreen)),
    setSelectedElement: _ => (),

    playing: false,
  });

[@react.component]
let make = (~value, ~children) =>
  React.createElement(React.Context.provider(context), {"value": value, "children": children});
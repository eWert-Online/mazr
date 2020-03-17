open Types.Ui;

type t = Types.Ui.t;

let initialState: t = {selectedElement: Building(Tree(DarkGreen))};

let make = (~state=initialState, ~action: ActionTypes.t) => {
  switch (action) {
  | SET_SELECTED_ELEMENT(element) => {selectedElement: element}
  | _ => state
  };
};
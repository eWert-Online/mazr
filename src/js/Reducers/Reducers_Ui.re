open Types.Ui;

type t = Types.Ui.t;

let initialState: t = {selectedElement: Object(Tree(DarkGreen)), gold: 100, wood: 80};

let make = (state: t, action: ActionTypes.t) => {
  switch (action) {
  | SET_SELECTED_ELEMENT(element) => {...state, selectedElement: element}
  | _ => state
  };
};
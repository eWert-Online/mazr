open Types.Waypoints;

let initialState = {startNode: None, endNode: None, beacon: None};

let make = (~state=initialState, ~action: ActionTypes.t) => {
  switch (action) {
  | SET_START_NODE(coordinates) => {...state, startNode: Some(coordinates)}
  | SET_END_NODE(coordinates) => {...state, endNode: Some(coordinates)}
  | SET_BEACON(coordinates) => {...state, beacon: Some(coordinates)}
  | _ => state
  };
};
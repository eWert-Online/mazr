let initialState = () =>
  switch (Random.int(5)) {
  | 0 =>
    switch (Random.int(10)) {
    | 0 => Types.Tree(Trunk)
    | _ => Types.Tree(DarkGreen)
    }
  | 1 => Types.Plant(HighGrass)
  | _ => Types.NoBuilding
  };

let make = (~state=initialState(), ~action: ActionTypes.t) => {
  switch (action) {
  | PLACE_BUILDING(_, building) =>
    switch (state) {
    | NoBuilding => building
    | Plant(_) => building
    | c => c
    }
  | SELL_BUILDING(_) =>
    switch (state) {
    | Tree(_) => Types.NoBuilding
    | c => c
    }
  | SET_START_NODE(_) => Waypoint(StartNode)
  | SET_END_NODE(_) => Waypoint(EndNode)
  | SET_BEACON(_) => Waypoint(Beacon)
  | _ => state
  };
};
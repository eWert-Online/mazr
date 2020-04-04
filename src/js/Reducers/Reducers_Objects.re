type tile = {
  coordinates: (int, int),
  entity: option(Types.Objects.t),
};

type t = array(tile);

let initialState: t = {
  Array.init(
    Settings.map_width * Settings.map_height,
    i => {
      let x = i mod Settings.map_width;
      let y = i / Settings.map_width;

      {
        coordinates: (x, y),
        entity:
          switch (Random.int(6)) {
          | 0 =>
            switch (Random.int(10)) {
            | 0 => Some(Tree(Trunk))
            | _ => Some(Tree(DarkGreen))
            }
          | _ => None
          },
      };
    },
  )
  |> Js.Array.filter(item => {
       switch (item.entity) {
       | Some(_) => true
       | None => false
       }
     });
};

let make = (state: t, action: ActionTypes.t) => {
  switch (action) {
  | PLACE_BUILDING(coordinates, building) =>
    let isObstructed = Belt.Array.some(state, item => item.coordinates == coordinates);
    if (!isObstructed) {
      Belt.Array.concat(state, [|{coordinates, entity: Some(building)}|]);
    } else {
      state;
    };
  | SELL_BUILDING(coordinates) => Belt.Array.keep(state, item => {item.coordinates != coordinates})
  | SET_START_NODE(coordinates)
  | SET_END_NODE(coordinates)
  | SET_BEACON(coordinates) => Belt.Array.keep(state, item => {item.coordinates != coordinates})
  | _ => state
  };
};
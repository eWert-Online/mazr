type decorationType =
  | Plant(Decorations.Plant.t);

type tile = {
  coordinates: (int, int),
  entity: option(decorationType),
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
          switch (Random.int(5)) {
          | 0 => Some(Plant(HighGrass))
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
  | _ => state
  };
};
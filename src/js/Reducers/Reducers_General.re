type theme =
  | Grassland
  | Desert;

type tile = (int, int);

type t = {
  theme,
  grid: array(array(tile)),
};

let initialState = {
  theme: Desert,
  grid:
    Array.init(Settings.map_width, x =>
      Array.init(
        Settings.map_height,
        y => {
          let coordinates = (x, y);
          coordinates;
        },
      )
    ),
};

let make = (state: t, action: ActionTypes.t) => {
  switch (action) {
  | _ => state
  };
};
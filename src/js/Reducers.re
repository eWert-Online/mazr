module Grid = Reducers_Grid;
module Ui = Reducers_Ui;
module Mob = Reducers_Mob;

type t = {
  ui: Ui.t,
  grid: Grid.t,
  mobs: Mob.t,
};

let initialState = {ui: Ui.initialState, grid: Grid.initialState, mobs: Mob.initialState};

let make = (~state=initialState, ~action: ActionTypes.t) => {
  {
    grid: Grid.make(~state=state.grid, ~action),
    ui: Ui.make(~state=state.ui, ~action),
    mobs: Mob.make(~state=state.mobs, ~action),
  };
};
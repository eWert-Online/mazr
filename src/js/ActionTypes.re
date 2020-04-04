type t =
  | MOVE_MOB(float, (int, int))
  | MOVE_MOB_BULK(array((float, (int, int))))
  | DESPAWN_MOB(float)
  | SPAWN_MOB(Types.Mob.t)
  | SELL_BUILDING((int, int))
  | PLACE_BUILDING((int, int), Types.Objects.t)
  | SET_START_NODE((int, int))
  | SET_END_NODE((int, int))
  | SET_BEACON((int, int))
  | SET_SELECTED_ELEMENT(Types.Ui.selectables);
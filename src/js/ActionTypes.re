type t =
  | MOVE_MOB(float, Types.coordinates)
  | DESPAWN_MOB(float)
  | SPAWN_MOB(Types.Mob.t)
  | SELL_BUILDING(Types.coordinates)
  | PLACE_BUILDING(Types.coordinates, Types.gameObject)
  | SET_START_NODE(Types.coordinates)
  | SET_END_NODE(Types.coordinates)
  | SET_BEACON(Types.coordinates)
  | SET_SELECTED_ELEMENT(Types.selectables);
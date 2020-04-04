open Types.Mob;

type t = array(Types.Mob.t);

let initialState: t = [||];

let make = (state: t, action: ActionTypes.t) => {
  switch (action) {
  | SPAWN_MOB(mob) => Belt.Array.concat(state, [|mob|])
  | DESPAWN_MOB(id) => Belt.Array.keep(state, mob => {mob.id !== id})
  | MOVE_MOB(id, coordinates) =>
    Belt.Array.map(state, mob =>
      if (mob.id === id) {
        {...mob, coordinates};
      } else {
        mob;
      }
    )
  | MOVE_MOB_BULK(mobs) =>
    Belt.Array.map(
      state,
      mob => {
        let maybeMob = Js.Array.find(((id, _)) => id === mob.id, mobs);
        switch (maybeMob) {
        | Some((_, coordinates)) => {...mob, coordinates}
        | None => mob
        };
      },
    )
  | _ => state
  };
};
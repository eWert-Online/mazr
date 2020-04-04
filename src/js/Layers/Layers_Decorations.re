[@react.component]
let make = (~state: Reducers.Decorations.t) => {
  Belt.Array.mapWithIndex(state, (index, decoration) => {
    <div key={string_of_int(index)} className={Shared.Styles.gridEntityCoords(decoration.coordinates)}>
      {switch (decoration.entity) {
       | Some(Plant(plantType)) => <Decorations.Plant plantType />
       | _ => React.null
       }}
    </div>
  })
  ->React.array;
};
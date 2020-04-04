[@react.component]
let make = (~state: Reducers.Objects.t) => {
  Belt.Array.mapWithIndex(state, (index, item) => {
    <div key={string_of_int(index)} className={Shared.Styles.gridEntityCoords(item.coordinates)}>
      {switch (item.entity) {
       | Some(Tree(treeType)) => <Objects.Tree treeType />
       | Some(Tower(towerType)) => <Objects.Tower towerType />
       | _ => React.null
       }}
    </div>
  })
  ->React.array;
};
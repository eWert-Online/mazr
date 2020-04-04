[@react.component]
let make = (~state: Reducers.Path.t) => {
  let getPathType = (~prev, ~current, ~next) => {
    let pathType: Objects.Path.t =
      switch (prev, current, next) {
      | (Some((x1, _)), (x2, _), Some((x3, _))) when x1 === x2 && x2 === x3 => Vertical
      | (Some((_, y1)), (_, y2), Some((_, y3))) when y1 === y2 && y2 === y3 => Horizontal
      | (None, _, None) => Dot
      | (None, (x2, y2), Some((x3, y3))) =>
        switch ((x2, y2), (x3, y3)) {
        | ((x2, y2), (x3, y3)) when x2 === x3 && y2 < y3 => End(Top)
        | ((x2, y2), (x3, y3)) when x2 === x3 && y2 > y3 => End(Bottom)
        | ((x2, y2), (x3, y3)) when y2 === y3 && x2 < x3 => End(Left)
        | ((x2, y2), (x3, y3)) when y2 === y3 && x2 > x3 => End(Right)
        | _ => End(Top)
        }
      | (Some((x1, y1)), (x2, y2), None) =>
        switch ((x1, y1), (x2, y2)) {
        | ((x1, y1), (x2, y2)) when x1 === x2 && y1 > y2 => End(Top)
        | ((x1, y1), (x2, y2)) when x1 === x2 && y1 < y2 => End(Bottom)
        | ((x1, y1), (x2, y2)) when y1 === y2 && x1 > x2 => End(Left)
        | ((x1, y1), (x2, y2)) when y1 === y2 && x1 < x2 => End(Right)
        | _ => End(Bottom)
        }
      | (Some((x1, y1)), (x2, y2), Some((x3, y3))) when x1 !== x3 || y1 !== y3 =>
        switch ((x1, y1), (x2, y2), (x3, y3)) {
        | ((x1, y1), (x2, y2), (x3, y3)) when x1 > x3 && y1 > y3 && y1 === y2 && x2 === x3 => Turn(Bottom_Left)
        | ((x1, y1), (x2, y2), (x3, y3)) when x1 < x3 && y1 < y3 && x1 === x2 && y2 === y3 => Turn(Bottom_Left)
        | ((x1, y1), (x2, y2), (x3, y3)) when x1 > x3 && y1 > y3 && x1 === x2 && y2 === y3 => Turn(Top_Right)
        | ((x1, y1), (x2, y2), (x3, y3)) when x1 < x3 && y1 < y3 && y1 === y2 && x2 === x3 => Turn(Top_Right)
        | ((x1, y1), (x2, y2), (x3, y3)) when x1 < x3 && y1 > y3 && y1 === y2 && x2 === x3 => Turn(Right_Bottom)
        | ((x1, y1), (x2, y2), (x3, y3)) when x1 > x3 && y1 < y3 && x1 === x2 && y2 === y3 => Turn(Right_Bottom)
        | ((x1, y1), (x2, y2), (x3, y3)) when x1 < x3 && y1 > y3 && x1 === x2 && y2 === y3 => Turn(Left_Top)
        | ((x1, y1), (x2, y2), (x3, y3)) when x1 > x3 && y1 < y3 && y1 === y2 && x2 === x3 => Turn(Left_Top)
        | _ => Turn(Left_Top)
        }
      | _ => Horizontal
      };
    pathType;
  };

  <React.Fragment>
    {React.useMemo1(
       () => {
         Belt.Array.mapWithIndex(
           state.calculatedPath,
           (index, (x, y)) => {
             let prevCoordinates = Belt.Array.get(state.calculatedPath, index - 1);
             let nextCoordinates = Belt.Array.get(state.calculatedPath, index + 1);
             let pathType = getPathType(~prev=prevCoordinates, ~current=(x, y), ~next=nextCoordinates);

             <div
               key={string_of_int(index) ++ "-" ++ string_of_int(x) ++ "-" ++ string_of_int(y)}
               className={Shared.Styles.gridEntityCoords((x, y))}>
               <Objects.Path pathType />
             </div>;
           },
         )
         ->React.array
       },
       [|state.calculatedPath|],
     )}
    {React.useMemo3(
       () => {
         <React.Fragment>
           {switch (state.startNode) {
            | Some(coordinates) =>
              <div className={Shared.Styles.gridEntityCoords(coordinates)}>
                <Objects.Waypoint waypointType=StartNode />
              </div>
            | _ => React.null
            }}
           {switch (state.beacon) {
            | Some(coordinates) =>
              <div className={Shared.Styles.gridEntityCoords(coordinates)}>
                <Objects.Waypoint waypointType=Beacon />
              </div>
            | _ => React.null
            }}
           {switch (state.endNode) {
            | Some(coordinates) =>
              <div className={Shared.Styles.gridEntityCoords(coordinates)}>
                <Objects.Waypoint waypointType=EndNode />
              </div>
            | _ => React.null
            }}
         </React.Fragment>
       },
       (state.startNode, state.beacon, state.endNode),
     )}
  </React.Fragment>;
};
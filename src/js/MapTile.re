// module Styles = {
 //   open Css;
 //   let mapTile =
 //     style([
 //       position(absolute),
 //       top(zero),
 //       bottom(zero),
 //       left(zero),
 //       right(zero),
 //       display(block),
 //       width(100.0->pct),
 //       padding(0->px),
 //       borderStyle(none),
 //       backgroundImage(url("/images/grass.png")),
 //       backgroundSize(cover),
 //       selector(
 //         "&:hover::after",
 //         [contentRule(`text("")), display(block), height(100.0->pct), backgroundColor(rgba(255, 255, 255, 0.3))],
 //       ),
 //     ]);
 // };
 // [@react.component]
 // let make = (~tile: Types.Grid.tile, ~neighbours: array(option(Types.Grid.tile)), ~onClick) => {
 //   let handleClick = _event => {
 //     onClick(tile);
 //   };
 //   let stateStyle =
 //     tile.path.inPath
 //       ? switch (neighbours[0], neighbours[1], neighbours[2], neighbours[3]) {
 //         | (Some(north), Some(east), Some(south), Some(west)) =>
 //           switch (north.path.inPath, east.path.inPath, south.path.inPath, west.path.inPath) {
 //           // Endings
 //           | (true, false, false, false) => Css.(style([backgroundImage(url("/images/path/dirt/end_bottom.png"))]))
 //           | (false, true, false, false) => Css.(style([backgroundImage(url("/images/path/dirt/end_left.png"))]))
 //           | (false, false, true, false) => Css.(style([backgroundImage(url("/images/path/dirt/end_top.png"))]))
 //           | (false, false, false, true) => Css.(style([backgroundImage(url("/images/path/dirt/end_right.png"))]))
 //           // Straights
 //           | (false, true, false, true) => Css.(style([backgroundImage(url("/images/path/dirt/horizontal.png"))]))
 //           | (true, false, true, false) => Css.(style([backgroundImage(url("/images/path/dirt/vertical.png"))]))
 //           // Turns
 //           | (true, true, false, false) =>
 //             Css.(style([backgroundImage(url("/images/path/dirt/turn_bottom_left.png"))]))
 //           | (false, false, true, true) =>
 //             Css.(style([backgroundImage(url("/images/path/dirt/turn_top_right.png"))]))
 //           | (true, false, false, true) =>
 //             Css.(style([backgroundImage(url("/images/path/dirt/turn_right_bottom.png"))]))
 //           | (false, true, true, false) =>
 //             Css.(style([backgroundImage(url("/images/path/dirt/turn_left_top.png"))]))
 //           // Junctions
 //           | (false, true, true, true) => Css.(style([backgroundImage(url("/images/path/dirt/junction_top.png"))]))
 //           | (true, false, true, true) =>
 //             Css.(style([backgroundImage(url("/images/path/dirt/junction_right.png"))]))
 //           | (true, true, false, true) =>
 //             Css.(style([backgroundImage(url("/images/path/dirt/junction_bottom.png"))]))
 //           | (true, true, true, false) => Css.(style([backgroundImage(url("/images/path/dirt/junction_left.png"))]))
 //           // Surrounded by paths
 //           | (true, true, true, true) => Css.(style([backgroundImage(url("/images/path/dirt/filled.png"))]))
 //           // TODO: Surrounded by empty Fields
 //           | (false, false, false, false) => ""
 //           }
 //         | (None, Some(east), Some(south), Some(west)) =>
 //           switch (east.path.inPath, south.path.inPath, west.path.inPath) {
 //           // Endings
 //           | (true, false, false) => Css.(style([backgroundImage(url("/images/path/dirt/end_left.png"))]))
 //           | (false, true, false) => Css.(style([backgroundImage(url("/images/path/dirt/end_top.png"))]))
 //           | (false, false, true) => Css.(style([backgroundImage(url("/images/path/dirt/end_right.png"))]))
 //           // Straight trues
 //           | (true, false, true) => Css.(style([backgroundImage(url("/images/path/dirt/horizontal.png"))]))
 //           // Turns
 //           | (false, true, true) => Css.(style([backgroundImage(url("/images/path/dirt/turn_top_right.png"))]))
 //           | (true, true, false) => Css.(style([backgroundImage(url("/images/path/dirt/turn_left_top.png"))]))
 //           // Junctions
 //           | (true, true, true) => Css.(style([backgroundImage(url("/images/path/dirt/junction_top.png"))]))
 //           // TODO: Surrounded by empty Fields
 //           | (false, false, false) => ""
 //           }
 //         | (Some(north), None, Some(south), Some(west)) =>
 //           switch (north.path.inPath, south.path.inPath, west.path.inPath) {
 //           // Endings
 //           | (true, false, false) => Css.(style([backgroundImage(url("/images/path/dirt/end_bottom.png"))]))
 //           | (false, true, false) => Css.(style([backgroundImage(url("/images/path/dirt/end_top.png"))]))
 //           | (false, false, true) => Css.(style([backgroundImage(url("/images/path/dirt/end_right.png"))]))
 //           // Straight trues
 //           | (true, true, false) => Css.(style([backgroundImage(url("/images/path/dirt/vertical.png"))]))
 //           // Turns
 //           | (false, true, true) => Css.(style([backgroundImage(url("/images/path/dirt/turn_top_right.png"))]))
 //           | (true, false, true) => Css.(style([backgroundImage(url("/images/path/dirt/turn_right_bottom.png"))]))
 //           // Junctions
 //           | (true, true, true) => Css.(style([backgroundImage(url("/images/path/dirt/junction_right.png"))]))
 //           // TODO: Surrounded by empty Fields
 //           | (false, false, false) => ""
 //           }
 //         | (Some(north), Some(east), None, Some(west)) =>
 //           switch (north.path.inPath, east.path.inPath, west.path.inPath) {
 //           // Endings
 //           | (true, false, false) => Css.(style([backgroundImage(url("/images/path/dirt/end_bottom.png"))]))
 //           | (false, true, false) => Css.(style([backgroundImage(url("/images/path/dirt/end_left.png"))]))
 //           | (false, false, true) => Css.(style([backgroundImage(url("/images/path/dirt/end_right.png"))]))
 //           // Straight trues
 //           | (false, true, true) => Css.(style([backgroundImage(url("/images/path/dirt/horizontal.png"))]))
 //           // Turns
 //           | (true, true, false) => Css.(style([backgroundImage(url("/images/path/dirt/turn_bottom_left.png"))]))
 //           | (true, false, true) => Css.(style([backgroundImage(url("/images/path/dirt/turn_right_bottom.png"))]))
 //           // Junctions
 //           | (true, true, true) => Css.(style([backgroundImage(url("/images/path/dirt/junction_bottom.png"))]))
 //           // TODO: Surrounded by empty Fields
 //           | (false, false, false) => ""
 //           }
 //         | (Some(north), Some(east), Some(south), None) =>
 //           switch (north.path.inPath, east.path.inPath, south.path.inPath) {
 //           // Endings
 //           | (true, false, false) => Css.(style([backgroundImage(url("/images/path/dirt/end_bottom.png"))]))
 //           | (false, true, false) => Css.(style([backgroundImage(url("/images/path/dirt/end_left.png"))]))
 //           | (false, false, true) => Css.(style([backgroundImage(url("/images/path/dirt/end_top.png"))]))
 //           // Straight trues
 //           | (true, false, true) => Css.(style([backgroundImage(url("/images/path/dirt/vertical.png"))]))
 //           // Turns
 //           | (true, true, false) => Css.(style([backgroundImage(url("/images/path/dirt/turn_bottom_left.png"))]))
 //           | (false, true, true) => Css.(style([backgroundImage(url("/images/path/dirt/turn_left_top.png"))]))
 //           // Junctions
 //           | (true, true, true) => Css.(style([backgroundImage(url("/images/path/dirt/junction_left.png"))]))
 //           // TODO: Surrounded by empty Fields
 //           | (false, false, false) => ""
 //           }
 //         | (Some(north), None, None, Some(west)) =>
 //           switch (north.path.inPath, west.path.inPath) {
 //           // Endings
 //           | (true, false) => Css.(style([backgroundImage(url("/images/path/dirt/end_bottom.png"))]))
 //           | (false, true) => Css.(style([backgroundImage(url("/images/path/dirt/end_right.png"))]))
 //           // Turns
 //           | (true, true) => Css.(style([backgroundImage(url("/images/path/dirt/turn_right_bottom.png"))]))
 //           // TODO: Surrounded by empty Fields
 //           | (false, false) => ""
 //           }
 //         | (Some(north), Some(east), None, None) =>
 //           switch (north.path.inPath, east.path.inPath) {
 //           // Endings
 //           | (true, false) => Css.(style([backgroundImage(url("/images/path/dirt/end_bottom.png"))]))
 //           | (false, true) => Css.(style([backgroundImage(url("/images/path/dirt/end_left.png"))]))
 //           // Turns
 //           | (true, true) => Css.(style([backgroundImage(url("/images/path/dirt/turn_bottom_left.png"))]))
 //           // TODO: Surrounded by empty Fields
 //           | (false, false) => ""
 //           }
 //         | (None, Some(east), Some(south), None) =>
 //           switch (east.path.inPath, south.path.inPath) {
 //           // Endings
 //           | (true, false) => Css.(style([backgroundImage(url("/images/path/dirt/end_left.png"))]))
 //           | (false, true) => Css.(style([backgroundImage(url("/images/path/dirt/end_top.png"))]))
 //           // Turns
 //           | (true, true) => Css.(style([backgroundImage(url("/images/path/dirt/turn_left_top.png"))]))
 //           // TODO: Surrounded by empty Fields
 //           | (false, false) => ""
 //           }
 //         | (None, None, Some(south), Some(west)) =>
 //           switch (south.path.inPath, west.path.inPath) {
 //           // Endings
 //           | (true, false) => Css.(style([backgroundImage(url("/images/path/dirt/end_top.png"))]))
 //           | (false, true) => Css.(style([backgroundImage(url("/images/path/dirt/end_right.png"))]))
 //           // Turns
 //           | (true, true) => Css.(style([backgroundImage(url("/images/path/dirt/turn_top_right.png"))]))
 //           // TODO: Surrounded by empty Fields
 //           | (false, false) => ""
 //           }
 //         | _ => Css.(style([backgroundImage(url("/images/path/dirt/filled.png"))]))
 //         }
 //       : "";
 //   <button className={Css.merge([Styles.mapTile, stateStyle])} onClick=handleClick>
 //     {switch (tile.entity) {
 //      | Tree(treeType) => <Objects.Tree treeType />
 //      | Tower(towerType) => <Objects.Tower towerType />
 //      | Nothing => React.null
 //      }}
 //   </button>;
 /* }*/
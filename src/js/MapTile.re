module Styles = {
  open Css;

  let mapTile =
    style([
      position(absolute),
      top(zero),
      bottom(zero),
      left(zero),
      right(zero),
      display(block),
      width(100.0->pct),
      padding(0->px),
      borderStyle(none),
      backgroundImage(url("/images/grass.png")),
      backgroundSize(cover),
      selector(
        "&:hover::after",
        [contentRule(`text("")), display(block), height(100.0->pct), backgroundColor(rgba(255, 255, 255, 0.3))],
      ),
    ]);
};

[@react.component]
let make = (~tiles, ~tile: Types.mapTile, ~setObjects: Types.gameObject => unit) => {
  let context = React.useContext(GameContext.context);

  let handleStateChange = _event => {
    let newState =
      switch (context.selectedElement) {
      | Sell =>
        switch (tile.objects) {
        | Waypoint(waypoint) => Types.Waypoint(waypoint)
        | _ => Types.None
        }
      | Building(building) =>
        switch (context.startNode, context.beacon, context.endNode) {
        | (None, _, _) => Waypoint(StartNode)
        | (Some(_), None, _) => Waypoint(Beacon)
        | (Some(_), Some(_), None) => Waypoint(EndNode)
        | (Some(_), Some(_), Some(_)) =>
          switch (tile.objects) {
          | None => building
          | Plant(_) => building
          | c => c
          }
        }
      };

    setObjects(newState);
  };

  let stateStyle =
    switch (tile.state) {
    | Path =>
      let neighbours = Pathfinder.getNeighbours(~tiles, ~tile);
      switch (neighbours[0], neighbours[1], neighbours[2], neighbours[3]) {
      | (Some(north), Some(east), Some(south), Some(west)) =>
        switch (north.state, east.state, south.state, west.state) {
        // Endings
        | (Path, Empty, Empty, Empty) => Css.(style([backgroundImage(url("/images/path/dirt/end_bottom.png"))]))
        | (Empty, Path, Empty, Empty) => Css.(style([backgroundImage(url("/images/path/dirt/end_left.png"))]))
        | (Empty, Empty, Path, Empty) => Css.(style([backgroundImage(url("/images/path/dirt/end_top.png"))]))
        | (Empty, Empty, Empty, Path) => Css.(style([backgroundImage(url("/images/path/dirt/end_right.png"))]))

        // Straight Paths
        | (Empty, Path, Empty, Path) => Css.(style([backgroundImage(url("/images/path/dirt/horizontal.png"))]))
        | (Path, Empty, Path, Empty) => Css.(style([backgroundImage(url("/images/path/dirt/vertical.png"))]))

        // Turns
        | (Path, Path, Empty, Empty) =>
          Css.(style([backgroundImage(url("/images/path/dirt/turn_bottom_left.png"))]))
        | (Empty, Empty, Path, Path) => Css.(style([backgroundImage(url("/images/path/dirt/turn_top_right.png"))]))
        | (Path, Empty, Empty, Path) =>
          Css.(style([backgroundImage(url("/images/path/dirt/turn_right_bottom.png"))]))
        | (Empty, Path, Path, Empty) => Css.(style([backgroundImage(url("/images/path/dirt/turn_left_top.png"))]))

        // Junctions
        | (Empty, Path, Path, Path) => Css.(style([backgroundImage(url("/images/path/dirt/junction_top.png"))]))
        | (Path, Empty, Path, Path) => Css.(style([backgroundImage(url("/images/path/dirt/junction_right.png"))]))
        | (Path, Path, Empty, Path) => Css.(style([backgroundImage(url("/images/path/dirt/junction_bottom.png"))]))
        | (Path, Path, Path, Empty) => Css.(style([backgroundImage(url("/images/path/dirt/junction_left.png"))]))

        // Surrounded by Path Fields
        | (Path, Path, Path, Path) => Css.(style([backgroundImage(url("/images/path/dirt/filled.png"))]))
        // TODO: Surrounded by Empty Fields
        | (Empty, Empty, Empty, Empty) => ""
        }
      | (None, Some(east), Some(south), Some(west)) =>
        switch (east.state, south.state, west.state) {
        // Endings
        | (Path, Empty, Empty) => Css.(style([backgroundImage(url("/images/path/dirt/end_left.png"))]))
        | (Empty, Path, Empty) => Css.(style([backgroundImage(url("/images/path/dirt/end_top.png"))]))
        | (Empty, Empty, Path) => Css.(style([backgroundImage(url("/images/path/dirt/end_right.png"))]))

        // Straight Paths
        | (Path, Empty, Path) => Css.(style([backgroundImage(url("/images/path/dirt/horizontal.png"))]))

        // Turns
        | (Empty, Path, Path) => Css.(style([backgroundImage(url("/images/path/dirt/turn_top_right.png"))]))
        | (Path, Path, Empty) => Css.(style([backgroundImage(url("/images/path/dirt/turn_left_top.png"))]))

        // Junctions
        | (Path, Path, Path) => Css.(style([backgroundImage(url("/images/path/dirt/junction_top.png"))]))
        // TODO: Surrounded by Empty Fields
        | (Empty, Empty, Empty) => ""
        }
      | (Some(north), None, Some(south), Some(west)) =>
        switch (north.state, south.state, west.state) {
        // Endings
        | (Path, Empty, Empty) => Css.(style([backgroundImage(url("/images/path/dirt/end_bottom.png"))]))
        | (Empty, Path, Empty) => Css.(style([backgroundImage(url("/images/path/dirt/end_top.png"))]))
        | (Empty, Empty, Path) => Css.(style([backgroundImage(url("/images/path/dirt/end_right.png"))]))

        // Straight Paths
        | (Path, Path, Empty) => Css.(style([backgroundImage(url("/images/path/dirt/vertical.png"))]))

        // Turns
        | (Empty, Path, Path) => Css.(style([backgroundImage(url("/images/path/dirt/turn_top_right.png"))]))
        | (Path, Empty, Path) => Css.(style([backgroundImage(url("/images/path/dirt/turn_right_bottom.png"))]))

        // Junctions
        | (Path, Path, Path) => Css.(style([backgroundImage(url("/images/path/dirt/junction_right.png"))]))

        // TODO: Surrounded by Empty Fields
        | (Empty, Empty, Empty) => ""
        }
      | (Some(north), Some(east), None, Some(west)) =>
        switch (north.state, east.state, west.state) {
        // Endings
        | (Path, Empty, Empty) => Css.(style([backgroundImage(url("/images/path/dirt/end_bottom.png"))]))
        | (Empty, Path, Empty) => Css.(style([backgroundImage(url("/images/path/dirt/end_left.png"))]))
        | (Empty, Empty, Path) => Css.(style([backgroundImage(url("/images/path/dirt/end_right.png"))]))

        // Straight Paths
        | (Empty, Path, Path) => Css.(style([backgroundImage(url("/images/path/dirt/horizontal.png"))]))

        // Turns
        | (Path, Path, Empty) => Css.(style([backgroundImage(url("/images/path/dirt/turn_bottom_left.png"))]))
        | (Path, Empty, Path) => Css.(style([backgroundImage(url("/images/path/dirt/turn_right_bottom.png"))]))

        // Junctions
        | (Path, Path, Path) => Css.(style([backgroundImage(url("/images/path/dirt/junction_bottom.png"))]))

        // TODO: Surrounded by Empty Fields
        | (Empty, Empty, Empty) => ""
        }
      | (Some(north), Some(east), Some(south), None) =>
        switch (north.state, east.state, south.state) {
        // Endings
        | (Path, Empty, Empty) => Css.(style([backgroundImage(url("/images/path/dirt/end_bottom.png"))]))
        | (Empty, Path, Empty) => Css.(style([backgroundImage(url("/images/path/dirt/end_left.png"))]))
        | (Empty, Empty, Path) => Css.(style([backgroundImage(url("/images/path/dirt/end_top.png"))]))

        // Straight Paths
        | (Path, Empty, Path) => Css.(style([backgroundImage(url("/images/path/dirt/vertical.png"))]))

        // Turns
        | (Path, Path, Empty) => Css.(style([backgroundImage(url("/images/path/dirt/turn_bottom_left.png"))]))
        | (Empty, Path, Path) => Css.(style([backgroundImage(url("/images/path/dirt/turn_left_top.png"))]))

        // Junctions
        | (Path, Path, Path) => Css.(style([backgroundImage(url("/images/path/dirt/junction_left.png"))]))

        // TODO: Surrounded by Empty Fields
        | (Empty, Empty, Empty) => ""
        }
      | (Some(north), None, None, Some(west)) =>
        switch (north.state, west.state) {
        // Endings
        | (Path, Empty) => Css.(style([backgroundImage(url("/images/path/dirt/end_bottom.png"))]))
        | (Empty, Path) => Css.(style([backgroundImage(url("/images/path/dirt/end_right.png"))]))

        // Turns
        | (Path, Path) => Css.(style([backgroundImage(url("/images/path/dirt/turn_right_bottom.png"))]))

        // TODO: Surrounded by Empty Fields
        | (Empty, Empty) => ""
        }
      | (Some(north), Some(east), None, None) =>
        switch (north.state, east.state) {
        // Endings
        | (Path, Empty) => Css.(style([backgroundImage(url("/images/path/dirt/end_bottom.png"))]))
        | (Empty, Path) => Css.(style([backgroundImage(url("/images/path/dirt/end_left.png"))]))
        // Turns
        | (Path, Path) => Css.(style([backgroundImage(url("/images/path/dirt/turn_bottom_left.png"))]))

        // TODO: Surrounded by Empty Fields
        | (Empty, Empty) => ""
        }
      | (None, Some(east), Some(south), None) =>
        switch (east.state, south.state) {
        // Endings
        | (Path, Empty) => Css.(style([backgroundImage(url("/images/path/dirt/end_left.png"))]))
        | (Empty, Path) => Css.(style([backgroundImage(url("/images/path/dirt/end_top.png"))]))

        // Turns
        | (Path, Path) => Css.(style([backgroundImage(url("/images/path/dirt/turn_left_top.png"))]))

        // TODO: Surrounded by Empty Fields
        | (Empty, Empty) => ""
        }
      | (None, None, Some(south), Some(west)) =>
        switch (south.state, west.state) {
        // Endings
        | (Path, Empty) => Css.(style([backgroundImage(url("/images/path/dirt/end_top.png"))]))
        | (Empty, Path) => Css.(style([backgroundImage(url("/images/path/dirt/end_right.png"))]))

        // Turns
        | (Path, Path) => Css.(style([backgroundImage(url("/images/path/dirt/turn_top_right.png"))]))

        // TODO: Surrounded by Empty Fields
        | (Empty, Empty) => ""
        }
      | _ => Css.(style([backgroundImage(url("/images/path/dirt/filled.png"))]))
      };
    | Empty => ""
    };

  <button className={Css.merge([Styles.mapTile, stateStyle])} onClick=handleStateChange>
    {switch (tile.objects) {
     | Tree(treeType) => <Tree treeType />
     | Waypoint(waypointType) => <Waypoint waypointType />
     | Plant(plantType) => <Plant plantType />
     | None => React.null
     }}
  </button>;
};
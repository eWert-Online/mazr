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

        | (Empty, Path, Path, Path) => Css.(style([backgroundImage(url("/images/path/dirt/junction_top.png"))]))
        | (Path, Empty, Path, Path) => Css.(style([backgroundImage(url("/images/path/dirt/junction_right.png"))]))
        | (Path, Path, Empty, Path) => Css.(style([backgroundImage(url("/images/path/dirt/junction_bottom.png"))]))
        | (Path, Path, Path, Empty) => Css.(style([backgroundImage(url("/images/path/dirt/junction_left.png"))]))

        // Surrounded by Path Fields
        | (Path, Path, Path, Path) => Css.(style([backgroundImage(url("/images/path/dirt/filled.png"))]))
        // TODO: Surrounded by Empty Fields
        | (Empty, Empty, Empty, Empty) => ""
        }
      | _ => Css.(style([backgroundImage(url("/images/path/dirt/filled.png"))]))
      };
    | Empty =>
      let neighbours = Pathfinder.getNeighbours(~tiles, ~tile);
      switch (neighbours[2]) {
      | None => Css.(style([backgroundImage(url("/images/edge.png"))]))
      | _ => ""
      };
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
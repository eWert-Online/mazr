module Styles = {
  open Css;

  let grid =
    style([
      position(relative),
      display(`flex),
      flexWrap(nowrap),
      alignItems(center),
      justifyContent(center),
      border(5->px, solid, hex("fcfcfc")),
    ]);
  let gridColumn = style([flexGrow(1.0)]);
  let gridCell =
    style([
      position(relative),
      display(block),
      width(100.0->pct),
      padding(0->px),
      borderStyle(none),
      backgroundSize(cover),
      selector("&::before", [contentRule(`text("")), display(block), paddingTop(100.0->pct)]),
      selector("&:hover::before", [backgroundColor(rgba(255, 255, 255, 0.3))]),
    ]);
};

[@react.component]
let make = (~state: Reducers.General.t, ~actions: Reducers.Actions.t) => {
  let theme =
    switch (state.theme) {
    | Grassland => Css.(style([backgroundImage(url("/images/grass.png"))]))
    | Desert => Css.(style([backgroundImage(url("/images/grass.png"))])) // TODO: Add Desert Tiles
    };

  <div className=Styles.grid>
    {Belt.Array.mapWithIndex(state.grid, (x, row) => {
       <div className=Styles.gridColumn key={string_of_int(x)}>
         {row
          ->Belt.Array.mapWithIndex((y, column) => {
              <button
                className={Css.merge([Styles.gridCell, theme])}
                key={string_of_int(x) ++ "-" ++ string_of_int(y)}
                onClick={_event => {actions.handleGridClick(column)}}
              />
            })
          ->React.array}
       </div>
     })
     ->React.array}
  </div>;
};
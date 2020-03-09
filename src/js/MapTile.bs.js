'use strict';

var Css = require("bs-css-emotion/src/Css.js");
var Block = require("bs-platform/lib/js/block.js");
var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");
var Tree$Mazr = require("./Objects/Tree.bs.js");
var Caml_array = require("bs-platform/lib/js/caml_array.js");
var Plant$Mazr = require("./Objects/Plant.bs.js");
var Waypoint$Mazr = require("./Objects/Waypoint.bs.js");
var Pathfinder$Mazr = require("./Pathfinder.bs.js");
var GameContext$Mazr = require("./GameContext.bs.js");

var mapTile = Curry._1(Css.style, /* :: */[
      Css.position(Css.absolute),
      /* :: */[
        Css.top(Css.zero),
        /* :: */[
          Css.bottom(Css.zero),
          /* :: */[
            Css.left(Css.zero),
            /* :: */[
              Css.right(Css.zero),
              /* :: */[
                Css.display(Css.block),
                /* :: */[
                  Css.width(Css.pct(100.0)),
                  /* :: */[
                    Css.padding(Css.px(0)),
                    /* :: */[
                      Css.borderStyle(Css.none),
                      /* :: */[
                        Css.backgroundImage(Css.url("/images/grass.png")),
                        /* :: */[
                          Css.backgroundSize(Css.cover),
                          /* :: */[
                            Css.selector("&:hover::after", /* :: */[
                                  Css.contentRule(/* `text */[
                                        -856044371,
                                        ""
                                      ]),
                                  /* :: */[
                                    Css.display(Css.block),
                                    /* :: */[
                                      Css.height(Css.pct(100.0)),
                                      /* :: */[
                                        Css.backgroundColor(Css.rgba(255, 255, 255, 0.3)),
                                        /* [] */0
                                      ]
                                    ]
                                  ]
                                ]),
                            /* [] */0
                          ]
                        ]
                      ]
                    ]
                  ]
                ]
              ]
            ]
          ]
        ]
      ]
    ]);

var Styles = {
  mapTile: mapTile
};

function MapTile(Props) {
  var tiles = Props.tiles;
  var tile = Props.tile;
  var setObjects = Props.setObjects;
  var context = React.useContext(GameContext$Mazr.context);
  var handleStateChange = function (_event) {
    var match = context.selectedElement;
    var tmp;
    if (match) {
      var building = match[0];
      var match$1 = context.startNode;
      var match$2 = context.beacon;
      var match$3 = context.endNode;
      if (match$1 !== undefined) {
        if (match$2 !== undefined) {
          if (match$3 !== undefined) {
            var c = tile.objects;
            if (typeof c === "number") {
              tmp = building;
            } else {
              switch (c.tag | 0) {
                case /* Plant */1 :
                    tmp = building;
                    break;
                case /* Tree */0 :
                case /* Waypoint */2 :
                    tmp = c;
                    break;
                
              }
            }
          } else {
            tmp = /* Waypoint */Block.__(2, [/* EndNode */2]);
          }
        } else {
          tmp = /* Waypoint */Block.__(2, [/* Beacon */1]);
        }
      } else {
        tmp = /* Waypoint */Block.__(2, [/* StartNode */0]);
      }
    } else {
      var match$4 = tile.objects;
      tmp = typeof match$4 === "number" || match$4.tag !== /* Waypoint */2 ? /* None */0 : /* Waypoint */Block.__(2, [match$4[0]]);
    }
    return Curry._1(setObjects, tmp);
  };
  var match = tile.state;
  var stateStyle;
  if (match) {
    var neighbours = Pathfinder$Mazr.getNeighbours(tiles, tile);
    var match$1 = Caml_array.caml_array_get(neighbours, 0);
    var match$2 = Caml_array.caml_array_get(neighbours, 1);
    var match$3 = Caml_array.caml_array_get(neighbours, 2);
    var match$4 = Caml_array.caml_array_get(neighbours, 3);
    var exit = 0;
    if (match$1 !== undefined && match$2 !== undefined && match$3 !== undefined && match$4 !== undefined) {
      var match$5 = match$1.state;
      var match$6 = match$2.state;
      var match$7 = match$3.state;
      var match$8 = match$4.state;
      stateStyle = match$5 ? (
          match$6 ? (
              match$7 ? (
                  match$8 ? Curry._1(Css.style, /* :: */[
                          Css.backgroundImage(Css.url("/images/path/dirt/filled.png")),
                          /* [] */0
                        ]) : Curry._1(Css.style, /* :: */[
                          Css.backgroundImage(Css.url("/images/path/dirt/junction_left.png")),
                          /* [] */0
                        ])
                ) : (
                  match$8 ? Curry._1(Css.style, /* :: */[
                          Css.backgroundImage(Css.url("/images/path/dirt/junction_bottom.png")),
                          /* [] */0
                        ]) : Curry._1(Css.style, /* :: */[
                          Css.backgroundImage(Css.url("/images/path/dirt/turn_bottom_left.png")),
                          /* [] */0
                        ])
                )
            ) : (
              match$7 ? (
                  match$8 ? Curry._1(Css.style, /* :: */[
                          Css.backgroundImage(Css.url("/images/path/dirt/junction_right.png")),
                          /* [] */0
                        ]) : Curry._1(Css.style, /* :: */[
                          Css.backgroundImage(Css.url("/images/path/dirt/vertical.png")),
                          /* [] */0
                        ])
                ) : (
                  match$8 ? Curry._1(Css.style, /* :: */[
                          Css.backgroundImage(Css.url("/images/path/dirt/turn_right_bottom.png")),
                          /* [] */0
                        ]) : Curry._1(Css.style, /* :: */[
                          Css.backgroundImage(Css.url("/images/path/dirt/end_bottom.png")),
                          /* [] */0
                        ])
                )
            )
        ) : (
          match$6 ? (
              match$7 ? (
                  match$8 ? Curry._1(Css.style, /* :: */[
                          Css.backgroundImage(Css.url("/images/path/dirt/junction_top.png")),
                          /* [] */0
                        ]) : Curry._1(Css.style, /* :: */[
                          Css.backgroundImage(Css.url("/images/path/dirt/turn_left_top.png")),
                          /* [] */0
                        ])
                ) : (
                  match$8 ? Curry._1(Css.style, /* :: */[
                          Css.backgroundImage(Css.url("/images/path/dirt/horizontal.png")),
                          /* [] */0
                        ]) : Curry._1(Css.style, /* :: */[
                          Css.backgroundImage(Css.url("/images/path/dirt/end_left.png")),
                          /* [] */0
                        ])
                )
            ) : (
              match$7 ? (
                  match$8 ? Curry._1(Css.style, /* :: */[
                          Css.backgroundImage(Css.url("/images/path/dirt/turn_top_right.png")),
                          /* [] */0
                        ]) : Curry._1(Css.style, /* :: */[
                          Css.backgroundImage(Css.url("/images/path/dirt/end_top.png")),
                          /* [] */0
                        ])
                ) : (
                  match$8 ? Curry._1(Css.style, /* :: */[
                          Css.backgroundImage(Css.url("/images/path/dirt/end_right.png")),
                          /* [] */0
                        ]) : ""
                )
            )
        );
    } else {
      exit = 1;
    }
    if (exit === 1) {
      stateStyle = Curry._1(Css.style, /* :: */[
            Css.backgroundImage(Css.url("/images/path/dirt/filled.png")),
            /* [] */0
          ]);
    }
    
  } else {
    var neighbours$1 = Pathfinder$Mazr.getNeighbours(tiles, tile);
    var match$9 = Caml_array.caml_array_get(neighbours$1, 2);
    stateStyle = match$9 !== undefined ? "" : Curry._1(Css.style, /* :: */[
            Css.backgroundImage(Css.url("/images/edge.png")),
            /* [] */0
          ]);
  }
  var match$10 = tile.objects;
  var tmp;
  if (typeof match$10 === "number") {
    tmp = null;
  } else {
    switch (match$10.tag | 0) {
      case /* Tree */0 :
          tmp = React.createElement(Tree$Mazr.make, {
                treeType: match$10[0]
              });
          break;
      case /* Plant */1 :
          tmp = React.createElement(Plant$Mazr.make, {
                plantType: match$10[0]
              });
          break;
      case /* Waypoint */2 :
          tmp = React.createElement(Waypoint$Mazr.make, {
                waypointType: match$10[0]
              });
          break;
      
    }
  }
  return React.createElement("button", {
              className: Curry._1(Css.merge, /* :: */[
                    mapTile,
                    /* :: */[
                      stateStyle,
                      /* [] */0
                    ]
                  ]),
              onClick: handleStateChange
            }, tmp);
}

var make = MapTile;

exports.Styles = Styles;
exports.make = make;
/* mapTile Not a pure module */

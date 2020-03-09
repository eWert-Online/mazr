'use strict';

var Css = require("bs-css-emotion/src/Css.js");
var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");
var Grid$Mazr = require("../Grid.bs.js");
var Caml_array = require("bs-platform/lib/js/caml_array.js");

var mob = Curry._1(Css.style, /* :: */[
      Css.position(Css.absolute),
      /* :: */[
        Css.top(Css.px(0)),
        /* :: */[
          Css.left(Css.px(0)),
          /* :: */[
            Css.width(Css.pxFloat(Grid$Mazr.tileSize)),
            /* :: */[
              Css.display(Css.block),
              /* :: */[
                Css.margin(Css.auto),
                /* :: */[
                  Css.transitionProperty("all"),
                  /* :: */[
                    Css.transitionTimingFunction(Css.linear),
                    /* :: */[
                      Css.backgroundPosition4(/* left */-944764921, Css.px(0), /* top */5793429, Css.px(0)),
                      /* :: */[
                        Css.backgroundRepeat(Css.noRepeat),
                        /* :: */[
                          Css.selector("&::before", /* :: */[
                                Css.contentRule(/* `text */[
                                      -856044371,
                                      ""
                                    ]),
                                /* :: */[
                                  Css.display(Css.block),
                                  /* :: */[
                                    Css.paddingTop(Css.pct(100.0)),
                                    /* [] */0
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
    ]);

var Styles = {
  mob: mob
};

function Mob(Props) {
  var mob$1 = Props.mob;
  var tiles = Props.tiles;
  var mobType = Curry._1(Css.style, /* :: */[
        Css.backgroundImage(Css.url("/images/characters/skeleton.png")),
        /* [] */0
      ]);
  var match = React.useState((function () {
          return {
                  x: mob$1.coordinates.x,
                  y: mob$1.coordinates.y
                };
        }));
  var setCoordinate = match[1];
  var coordinate = match[0];
  var match$1 = React.useState((function () {
          return false;
        }));
  var setHasBeacon = match$1[1];
  var hasBeacon = match$1[0];
  React.useEffect((function (param) {
          var currentTile = Caml_array.caml_array_get(Caml_array.caml_array_get(tiles, coordinate.x), coordinate.y);
          var id = setTimeout((function (param) {
                  var match = currentTile.nextPath.length;
                  if (match !== 1) {
                    if (match !== 2) {
                      return /* () */0;
                    } else if (hasBeacon) {
                      return Curry._1(setCoordinate, (function (param) {
                                    return Caml_array.caml_array_get(currentTile.nextPath, 1);
                                  }));
                    } else {
                      return Curry._1(setCoordinate, (function (param) {
                                    return Caml_array.caml_array_get(currentTile.nextPath, 0);
                                  }));
                    }
                  } else {
                    return Curry._1(setCoordinate, (function (param) {
                                  return Caml_array.caml_array_get(currentTile.nextPath, 0);
                                }));
                  }
                }), mob$1.speed);
          var match = currentTile.objects;
          if (typeof match !== "number" && match.tag === /* Waypoint */2 && match[0] === 1) {
            Curry._1(setHasBeacon, (function (hadBeacon) {
                    if (hadBeacon) {
                      return hadBeacon;
                    } else {
                      return true;
                    }
                  }));
          }
          return (function (param) {
                    clearTimeout(id);
                    return /* () */0;
                  });
        }), /* tuple */[
        coordinate.x,
        coordinate.y,
        hasBeacon
      ]);
  var calculatedStyle = Curry._1(Css.style, /* :: */[
        Css.transforms(/* :: */[
              Css.translate(Css.pxFloat(coordinate.x * Grid$Mazr.tileSize), Css.pxFloat(coordinate.y * Grid$Mazr.tileSize)),
              /* :: */[
                Css.translateY(Css.pct(-33.0)),
                /* [] */0
              ]
            ]),
        /* :: */[
          Css.transitionDuration(mob$1.speed),
          /* [] */0
        ]
      ]);
  return React.createElement("div", {
              className: Curry._1(Css.merge, /* :: */[
                    mob,
                    /* :: */[
                      mobType,
                      /* :: */[
                        calculatedStyle,
                        /* [] */0
                      ]
                    ]
                  ])
            });
}

var make = Mob;

exports.Styles = Styles;
exports.make = make;
/* mob Not a pure module */

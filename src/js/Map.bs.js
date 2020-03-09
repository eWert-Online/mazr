'use strict';

var Css = require("bs-css-emotion/src/Css.js");
var List = require("bs-platform/lib/js/list.js");
var $$Array = require("bs-platform/lib/js/array.js");
var Block = require("bs-platform/lib/js/block.js");
var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");
var Random = require("bs-platform/lib/js/random.js");
var Mob$Mazr = require("./Mobs/Mob.bs.js");
var Belt_List = require("bs-platform/lib/js/belt_List.js");
var Grid$Mazr = require("./Grid.bs.js");
var Belt_Array = require("bs-platform/lib/js/belt_Array.js");
var Caml_array = require("bs-platform/lib/js/caml_array.js");
var Caml_option = require("bs-platform/lib/js/caml_option.js");
var MapTile$Mazr = require("./MapTile.bs.js");
var Pathfinder$Mazr = require("./Pathfinder.bs.js");
var GameContext$Mazr = require("./GameContext.bs.js");
var Mobs_Skeleton$Mazr = require("./Mobs/Mobs_Skeleton.bs.js");

var map = Curry._1(Css.style, /* :: */[
      Css.display(/* flex */-1010954439),
      /* :: */[
        Css.flexWrap(Css.nowrap),
        /* :: */[
          Css.alignItems(Css.center),
          /* :: */[
            Css.justifyContent(Css.center),
            /* [] */0
          ]
        ]
      ]
    ]);

var gridCell = Curry._1(Css.style, /* :: */[
      Css.position(Css.relative),
      /* :: */[
        Css.display(Css.block),
        /* :: */[
          Css.width(Css.pxFloat(Grid$Mazr.tileSize)),
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
    ]);

var Styles = {
  map: map,
  gridCell: gridCell
};

function $$Map(Props) {
  var context = React.useContext(GameContext$Mazr.context);
  var match = React.useState((function () {
          return false;
        }));
  var setHasPath = match[1];
  var hasPath = match[0];
  var match$1 = React.useState((function () {
          return true;
        }));
  var setNeedToRecalculatePath = match$1[1];
  var needToRecalculatePath = match$1[0];
  var match$2 = React.useState((function () {
          return $$Array.init(Grid$Mazr.width, (function (x) {
                        return $$Array.init(Grid$Mazr.height, (function (y) {
                                      var match = Random.$$int(5);
                                      var tmp;
                                      if (match !== 0) {
                                        tmp = match !== 1 ? /* None */0 : /* Plant */Block.__(1, [/* HighGrass */0]);
                                      } else {
                                        var match$1 = Random.$$int(10);
                                        tmp = match$1 !== 0 ? /* Tree */Block.__(0, [/* DarkGreen */1]) : /* Tree */Block.__(0, [/* Trunk */2]);
                                      }
                                      return {
                                              coordinates: {
                                                x: x,
                                                y: y
                                              },
                                              state: /* Empty */0,
                                              nextPath: [],
                                              objects: tmp
                                            };
                                    }));
                      }));
        }));
  var setTiles = match$2[1];
  var tiles = match$2[0];
  var match$3 = React.useState((function () {
          return [];
        }));
  var setMobs = match$3[1];
  React.useEffect((function (param) {
          if (needToRecalculatePath) {
            Curry._1(setTiles, (function (tiles) {
                    return Belt_Array.map(tiles, (function (row) {
                                  return Belt_Array.map(row, (function (tile) {
                                                return {
                                                        coordinates: tile.coordinates,
                                                        state: /* Empty */0,
                                                        nextPath: [],
                                                        objects: tile.objects
                                                      };
                                              }));
                                }));
                  }));
            var match = context.startNode;
            var match$1 = context.beacon;
            var pathToBeacon;
            if (match !== undefined && match$1 !== undefined) {
              var beacon = match$1;
              var startNode = match;
              var path = Pathfinder$Mazr.find(tiles, Caml_array.caml_array_get(Caml_array.caml_array_get(tiles, startNode.coordinates.x), startNode.coordinates.y), Caml_array.caml_array_get(Caml_array.caml_array_get(tiles, beacon.coordinates.x), beacon.coordinates.y));
              pathToBeacon = path !== undefined ? path : /* [] */0;
            } else {
              pathToBeacon = /* [] */0;
            }
            var match$2 = context.beacon;
            var match$3 = context.endNode;
            var pathToEnd;
            if (match$2 !== undefined && match$3 !== undefined) {
              var endNode = match$3;
              var beacon$1 = match$2;
              var path$1 = Pathfinder$Mazr.find(tiles, Caml_array.caml_array_get(Caml_array.caml_array_get(tiles, beacon$1.coordinates.x), beacon$1.coordinates.y), Caml_array.caml_array_get(Caml_array.caml_array_get(tiles, endNode.coordinates.x), endNode.coordinates.y));
              pathToEnd = path$1 !== undefined ? path$1 : /* [] */0;
            } else {
              pathToEnd = /* [] */0;
            }
            var completePath = List.append(pathToBeacon, pathToEnd);
            Curry._1(setTiles, (function (tiles) {
                    var newTiles = tiles.slice(0);
                    Belt_List.forEachWithIndex(completePath, (function (index, pathTile) {
                            var match = Belt_List.get(completePath, index + 1 | 0);
                            var nextPath;
                            if (match !== undefined) {
                              var tile = match;
                              nextPath = [{
                                  x: tile.coordinates.x,
                                  y: tile.coordinates.y
                                }];
                            } else {
                              nextPath = [];
                            }
                            var tile$1 = Caml_array.caml_array_get(Caml_array.caml_array_get(newTiles, pathTile.coordinates.x), pathTile.coordinates.y);
                            var tile_coordinates = tile$1.coordinates;
                            var tile_nextPath = $$Array.concat(/* :: */[
                                  tile$1.nextPath,
                                  /* :: */[
                                    nextPath,
                                    /* [] */0
                                  ]
                                ]);
                            var tile_objects = tile$1.objects;
                            var tile$2 = {
                              coordinates: tile_coordinates,
                              state: /* Path */1,
                              nextPath: tile_nextPath,
                              objects: tile_objects
                            };
                            console.log(tile$2);
                            return Caml_array.caml_array_set(Caml_array.caml_array_get(newTiles, tile_coordinates.x), tile_coordinates.y, tile$2);
                          }));
                    return newTiles;
                  }));
            Curry._1(setHasPath, (function (param) {
                    if (List.length(pathToEnd) > 0) {
                      return List.length(pathToBeacon) > 0;
                    } else {
                      return false;
                    }
                  }));
            Curry._1(setNeedToRecalculatePath, (function (param) {
                    return false;
                  }));
          }
          return ;
        }), /* tuple */[
        context.startNode,
        context.beacon,
        context.endNode,
        tiles,
        needToRecalculatePath
      ]);
  React.useEffect((function () {
          var match = context.startNode;
          var match$1 = context.beacon;
          var match$2 = context.endNode;
          var timer;
          if (hasPath && match !== undefined && match$1 !== undefined && match$2 !== undefined) {
            var start = match;
            timer = Caml_option.some(setInterval((function (param) {
                        return Curry._1(setMobs, (function (mobs) {
                                      var newMob = Mobs_Skeleton$Mazr.make(start.coordinates);
                                      return Belt_Array.concat(mobs, [newMob]);
                                    }));
                      }), 8000));
          } else {
            timer = undefined;
          }
          if (timer !== undefined) {
            var timerId = Caml_option.valFromOption(timer);
            return (function (param) {
                      clearInterval(timerId);
                      return /* () */0;
                    });
          }
          
        }), [hasPath]);
  return React.createElement("div", {
              className: map
            }, Belt_Array.mapWithIndex(Grid$Mazr.grid, (function (x, row) {
                    return React.createElement("div", {
                                key: String(x)
                              }, Belt_Array.mapWithIndex(row, (function (y, _column) {
                                      var tile = Caml_array.caml_array_get(Caml_array.caml_array_get(tiles, x), y);
                                      return React.createElement("div", {
                                                  key: "tile_" + (String(x) + ("-" + String(y))),
                                                  className: gridCell
                                                }, React.createElement(MapTile$Mazr.make, {
                                                      tiles: tiles,
                                                      tile: tile,
                                                      setObjects: (function (objects) {
                                                          var tile$1 = tile;
                                                          var objects$1 = objects;
                                                          Curry._1(setTiles, (function (tiles) {
                                                                  var tiles$1 = $$Array.copy(tiles);
                                                                  Caml_array.caml_array_set(Caml_array.caml_array_get(tiles$1, tile$1.coordinates.x), tile$1.coordinates.y, {
                                                                        coordinates: tile$1.coordinates,
                                                                        state: tile$1.state,
                                                                        nextPath: tile$1.nextPath,
                                                                        objects: objects$1
                                                                      });
                                                                  return tiles$1;
                                                                }));
                                                          Curry._1(setNeedToRecalculatePath, (function (param) {
                                                                  return true;
                                                                }));
                                                          if (typeof objects$1 === "number" || objects$1.tag !== /* Waypoint */2) {
                                                            return /* () */0;
                                                          } else {
                                                            switch (objects$1[0]) {
                                                              case /* StartNode */0 :
                                                                  return Curry._1(context.setStartNode, (function (param) {
                                                                                return tile$1;
                                                                              }));
                                                              case /* Beacon */1 :
                                                                  return Curry._1(context.setBeacon, (function (param) {
                                                                                return tile$1;
                                                                              }));
                                                              case /* EndNode */2 :
                                                                  return Curry._1(context.setEndNode, (function (param) {
                                                                                return tile$1;
                                                                              }));
                                                              
                                                            }
                                                          }
                                                        })
                                                    }));
                                    })));
                  })), Belt_Array.mapWithIndex(match$3[0], (function (index, mob) {
                    return React.createElement(Mob$Mazr.make, {
                                mob: mob,
                                tiles: tiles,
                                key: String(index)
                              });
                  })));
}

var make = $$Map;

exports.Styles = Styles;
exports.make = make;
/* map Not a pure module */

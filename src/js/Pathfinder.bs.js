'use strict';

var List = require("bs-platform/lib/js/list.js");
var $$Array = require("bs-platform/lib/js/array.js");
var Grid$Mazr = require("./Grid.bs.js");
var Belt_Array = require("bs-platform/lib/js/belt_Array.js");
var Caml_array = require("bs-platform/lib/js/caml_array.js");
var Pervasives = require("bs-platform/lib/js/pervasives.js");

function getDistance(nodeA, nodeB) {
  return Pervasives.abs(nodeA.coordinates.x - nodeB.coordinates.x | 0) + Pervasives.abs(nodeA.coordinates.y - nodeB.coordinates.y | 0) | 0;
}

function isObstacle(tile) {
  var match = tile.objects;
  if (typeof match === "number" || match.tag) {
    return false;
  } else {
    return true;
  }
}

function getNeighbours(tiles, tile) {
  var north = tile.coordinates.y > 0 ? Caml_array.caml_array_get(Caml_array.caml_array_get(tiles, tile.coordinates.x), tile.coordinates.y - 1 | 0) : undefined;
  var east = tile.coordinates.x < (Grid$Mazr.width - 1 | 0) ? Caml_array.caml_array_get(Caml_array.caml_array_get(tiles, tile.coordinates.x + 1 | 0), tile.coordinates.y) : undefined;
  var west = tile.coordinates.x > 0 ? Caml_array.caml_array_get(Caml_array.caml_array_get(tiles, tile.coordinates.x - 1 | 0), tile.coordinates.y) : undefined;
  var south = tile.coordinates.y < (Grid$Mazr.height - 1 | 0) ? Caml_array.caml_array_get(Caml_array.caml_array_get(tiles, tile.coordinates.x), tile.coordinates.y + 1 | 0) : undefined;
  return [
          north,
          east,
          south,
          west
        ];
}

function find(tiles, startTile, endTile) {
  var parent = $$Array.make_matrix(Grid$Mazr.width, Grid$Mazr.height, undefined);
  var distanceCost = $$Array.make_matrix(Grid$Mazr.width, Grid$Mazr.height, Pervasives.max_int);
  var remainingCost = $$Array.make_matrix(Grid$Mazr.width, Grid$Mazr.height, 0);
  var openSet = {
    contents: []
  };
  var closedSet = $$Array.make_matrix(Grid$Mazr.width, Grid$Mazr.height, false);
  Caml_array.caml_array_set(Caml_array.caml_array_get(distanceCost, startTile.coordinates.x), startTile.coordinates.y, 0);
  openSet.contents.push(startTile);
  var finalPath = /* [] */0;
  while(openSet.contents.length !== 0) {
    var current = Belt_Array.reduce(openSet.contents, Caml_array.caml_array_get(openSet.contents, 0), (function (initial, item) {
            if (Caml_array.caml_array_get(Caml_array.caml_array_get(distanceCost, item.coordinates.x), item.coordinates.y) < Caml_array.caml_array_get(Caml_array.caml_array_get(distanceCost, initial.coordinates.x), initial.coordinates.y) || Caml_array.caml_array_get(Caml_array.caml_array_get(distanceCost, item.coordinates.x), item.coordinates.y) === Caml_array.caml_array_get(Caml_array.caml_array_get(distanceCost, initial.coordinates.x), initial.coordinates.y) && Caml_array.caml_array_get(Caml_array.caml_array_get(remainingCost, item.coordinates.x), item.coordinates.y) < Caml_array.caml_array_get(Caml_array.caml_array_get(remainingCost, initial.coordinates.x), initial.coordinates.y)) {
              return item;
            } else {
              return initial;
            }
          }));
    openSet.contents = Belt_Array.keep(openSet.contents, (function(current){
        return function (item) {
          return item !== current;
        }
        }(current)));
    Caml_array.caml_array_set(Caml_array.caml_array_get(closedSet, current.coordinates.x), current.coordinates.y, true);
    if (current.coordinates.x === endTile.coordinates.x && current.coordinates.y === endTile.coordinates.y) {
      var getPath = function (pathSegment) {
        var nextParent = Caml_array.caml_array_get(Caml_array.caml_array_get(parent, pathSegment.coordinates.x), pathSegment.coordinates.y);
        return /* :: */[
                pathSegment,
                nextParent !== undefined ? getPath(nextParent) : /* [] */0
              ];
      };
      finalPath = getPath(current);
    } else {
      var neighbours = getNeighbours(tiles, current);
      Belt_Array.forEach(neighbours, (function(current){
          return function (neighbour) {
            if (neighbour !== undefined) {
              var neighbour$1 = neighbour;
              if (Caml_array.caml_array_get(Caml_array.caml_array_get(closedSet, neighbour$1.coordinates.x), neighbour$1.coordinates.y) === false && !isObstacle(neighbour$1)) {
                var newDistanceToNeigbour = Caml_array.caml_array_get(Caml_array.caml_array_get(distanceCost, current.coordinates.x), current.coordinates.y) + getDistance(current, neighbour$1) | 0;
                var remaining = getDistance(neighbour$1, endTile);
                var isOpen = Belt_Array.some(openSet.contents, (function (item) {
                        if (item.coordinates.x === neighbour$1.coordinates.x) {
                          return item.coordinates.y === neighbour$1.coordinates.y;
                        } else {
                          return false;
                        }
                      }));
                if (newDistanceToNeigbour < Caml_array.caml_array_get(Caml_array.caml_array_get(distanceCost, neighbour$1.coordinates.x), neighbour$1.coordinates.y) || !isOpen) {
                  Caml_array.caml_array_set(Caml_array.caml_array_get(distanceCost, neighbour$1.coordinates.x), neighbour$1.coordinates.y, newDistanceToNeigbour);
                  Caml_array.caml_array_set(Caml_array.caml_array_get(remainingCost, neighbour$1.coordinates.x), neighbour$1.coordinates.y, remaining);
                  Caml_array.caml_array_set(Caml_array.caml_array_get(parent, neighbour$1.coordinates.x), neighbour$1.coordinates.y, current);
                  if (isOpen) {
                    return 0;
                  } else {
                    openSet.contents.push(neighbour$1);
                    return /* () */0;
                  }
                } else {
                  return 0;
                }
              } else {
                return 0;
              }
            } else {
              return /* () */0;
            }
          }
          }(current)));
    }
  };
  if (List.length(finalPath) > 0) {
    return List.rev(finalPath);
  }
  
}

exports.getDistance = getDistance;
exports.isObstacle = isObstacle;
exports.getNeighbours = getNeighbours;
exports.find = find;
/* Grid-Mazr Not a pure module */

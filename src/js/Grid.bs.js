'use strict';

var $$Array = require("bs-platform/lib/js/array.js");

var tileSize = window.innerWidth / 50;

var grid = $$Array.init(50, (function (x) {
        return $$Array.init(25, (function (y) {
                      return {
                              x: x,
                              y: y
                            };
                    }));
      }));

var width = 50;

var height = 25;

exports.width = width;
exports.height = height;
exports.tileSize = tileSize;
exports.grid = grid;
/* tileSize Not a pure module */

'use strict';

var Css = require("bs-css-emotion/src/Css.js");
var Block = require("bs-platform/lib/js/block.js");
var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");
var Ui$Mazr = require("./Ui.bs.js");
var Map$Mazr = require("./Map.bs.js");
var GameContext$Mazr = require("./GameContext.bs.js");

var gameWrapper = Curry._1(Css.style, /* :: */[
      Css.display(/* flex */-1010954439),
      /* :: */[
        Css.flexDirection(Css.column),
        /* :: */[
          Css.backgroundImage(Css.url("/images/abyss.png")),
          /* :: */[
            Css.height(Css.pct(100.0)),
            /* [] */0
          ]
        ]
      ]
    ]);

var Styles = {
  gameWrapper: gameWrapper
};

function Game(Props) {
  var match = React.useState((function () {
          return /* Building */[/* Tree */Block.__(0, [/* DarkGreen */1])];
        }));
  var match$1 = React.useState((function () {
          return ;
        }));
  var startNode = match$1[0];
  var match$2 = React.useState((function () {
          return ;
        }));
  var endNode = match$2[0];
  var match$3 = React.useState((function () {
          return ;
        }));
  var beacon = match$3[0];
  var value_setStartNode = match$1[1];
  var value_setEndNode = match$2[1];
  var value_setBeacon = match$3[1];
  var value_selectedElement = match[0];
  var value_setSelectedElement = match[1];
  var value_playing = startNode !== undefined && beacon !== undefined ? endNode !== undefined : false;
  var value = {
    startNode: startNode,
    setStartNode: value_setStartNode,
    endNode: endNode,
    setEndNode: value_setEndNode,
    beacon: beacon,
    setBeacon: value_setBeacon,
    selectedElement: value_selectedElement,
    setSelectedElement: value_setSelectedElement,
    playing: value_playing
  };
  return React.createElement(GameContext$Mazr.make, {
              value: value,
              children: React.createElement("div", {
                    className: gameWrapper
                  }, React.createElement(Map$Mazr.make, { }), React.createElement(Ui$Mazr.make, { }))
            });
}

var make = Game;

exports.Styles = Styles;
exports.make = make;
/* gameWrapper Not a pure module */

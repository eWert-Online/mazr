'use strict';

var Block = require("bs-platform/lib/js/block.js");
var React = require("react");

var context = React.createContext({
      startNode: undefined,
      setStartNode: (function (param) {
          return /* () */0;
        }),
      endNode: undefined,
      setEndNode: (function (param) {
          return /* () */0;
        }),
      beacon: undefined,
      setBeacon: (function (param) {
          return /* () */0;
        }),
      selectedElement: /* Building */[/* Tree */Block.__(0, [/* DarkGreen */1])],
      setSelectedElement: (function (param) {
          return /* () */0;
        }),
      playing: false
    });

function GameContext(Props) {
  var value = Props.value;
  var children = Props.children;
  return React.createElement(context.Provider, {
              value: value,
              children: children
            });
}

var make = GameContext;

exports.context = context;
exports.make = make;
/* context Not a pure module */

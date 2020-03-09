'use strict';

var Css = require("bs-css-emotion/src/Css.js");
var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");
var Game$Mazr = require("./Game.bs.js");
var ReactDOMRe = require("reason-react/src/ReactDOMRe.js");

Curry._2(Css.$$global, "*", /* :: */[
      Css.margin(Css.px(0)),
      /* :: */[
        Css.padding(Css.px(0)),
        /* :: */[
          Css.outlineStyle(Css.none),
          /* [] */0
        ]
      ]
    ]);

Curry._2(Css.$$global, "html, body, #app", /* :: */[
      Css.margin(Css.px(0)),
      /* :: */[
        Css.height(Css.pct(100.0)),
        /* [] */0
      ]
    ]);

ReactDOMRe.renderToElementWithId(React.createElement(Game$Mazr.make, { }), "app");

/*  Not a pure module */

'use strict';

var Css = require("bs-css-emotion/src/Css.js");
var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");
var Objects_Generic$Mazr = require("./Objects_Generic.bs.js");

function Plant(Props) {
  Props.plantType;
  var plantType = Curry._1(Css.style, /* :: */[
        Css.backgroundImage(Css.url("/images/objects/high_grass.png")),
        /* [] */0
      ]);
  return React.createElement("div", {
              className: Curry._1(Css.merge, /* :: */[
                    Objects_Generic$Mazr.Styles.gameObject,
                    /* :: */[
                      plantType,
                      /* [] */0
                    ]
                  ])
            });
}

var make = Plant;

exports.make = make;
/* Css Not a pure module */

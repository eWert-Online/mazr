'use strict';

var Css = require("bs-css-emotion/src/Css.js");
var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");
var Objects_Generic$Mazr = require("./Objects_Generic.bs.js");

function Waypoint(Props) {
  var waypointType = Props.waypointType;
  var waypointType$1;
  switch (waypointType) {
    case /* StartNode */0 :
        waypointType$1 = Curry._1(Css.style, /* :: */[
              Css.backgroundImage(Css.url("/images/objects/hole.png")),
              /* [] */0
            ]);
        break;
    case /* Beacon */1 :
        waypointType$1 = Curry._1(Css.style, /* :: */[
              Css.backgroundImage(Css.url("/images/objects/key.png")),
              /* [] */0
            ]);
        break;
    case /* EndNode */2 :
        waypointType$1 = Curry._1(Css.style, /* :: */[
              Css.backgroundImage(Css.url("/images/objects/chest.png")),
              /* [] */0
            ]);
        break;
    
  }
  return React.createElement("div", {
              className: Curry._1(Css.merge, /* :: */[
                    Objects_Generic$Mazr.Styles.gameObject,
                    /* :: */[
                      waypointType$1,
                      /* [] */0
                    ]
                  ])
            });
}

var make = Waypoint;

exports.make = make;
/* Css Not a pure module */

'use strict';

var Css = require("bs-css-emotion/src/Css.js");
var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");
var Objects_Generic$Mazr = require("./Objects_Generic.bs.js");

function Tree(Props) {
  var treeType = Props.treeType;
  var treeType$1;
  switch (treeType) {
    case /* LightGreen */0 :
        treeType$1 = Curry._1(Css.style, /* :: */[
              Css.backgroundImage(Css.url("/images/objects/tree_green.png")),
              /* [] */0
            ]);
        break;
    case /* DarkGreen */1 :
        treeType$1 = Curry._1(Css.style, /* :: */[
              Css.backgroundImage(Css.url("/images/objects/tree_darkgreen.png")),
              /* [] */0
            ]);
        break;
    case /* Trunk */2 :
        treeType$1 = Curry._1(Css.style, /* :: */[
              Css.backgroundImage(Css.url("/images/objects/tree_trunk.png")),
              /* [] */0
            ]);
        break;
    
  }
  return React.createElement("div", {
              className: Curry._1(Css.merge, /* :: */[
                    Objects_Generic$Mazr.Styles.gameObject,
                    /* :: */[
                      treeType$1,
                      /* [] */0
                    ]
                  ])
            });
}

var make = Tree;

exports.make = make;
/* Css Not a pure module */

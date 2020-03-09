'use strict';

var Css = require("bs-css-emotion/src/Css.js");
var Block = require("bs-platform/lib/js/block.js");
var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");
var GameContext$Mazr = require("./GameContext.bs.js");

var toolbar = Curry._1(Css.style, /* :: */[
      Css.display(/* flex */-1010954439),
      /* :: */[
        Css.alignItems(Css.center),
        /* :: */[
          Css.padding(Css.px(15)),
          /* :: */[
            Css.flexGrow(1.0),
            /* [] */0
          ]
        ]
      ]
    ]);

var button = Curry._1(Css.style, /* :: */[
      Css.height(Css.px(40)),
      /* :: */[
        Css.width(Css.px(40)),
        /* :: */[
          Css.display(/* flex */-1010954439),
          /* :: */[
            Css.alignItems(Css.center),
            /* :: */[
              Css.justifyContent(Css.center),
              /* :: */[
                Css.backgroundColor(Css.transparent),
                /* :: */[
                  Css.borderStyle(Css.none),
                  /* :: */[
                    Css.marginRight(Css.px(15)),
                    /* :: */[
                      Css.cursor(/* pointer */-786317123),
                      /* :: */[
                        Css.backgroundImage(Css.url("/images/ui/sign.png")),
                        /* :: */[
                          Css.backgroundRepeat(Css.noRepeat),
                          /* :: */[
                            Css.backgroundSize(Css.cover),
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
      ]
    ]);

var Styles = {
  toolbar: toolbar,
  button: button
};

function Ui(Props) {
  var context = React.useContext(GameContext$Mazr.context);
  var match = context.selectedElement;
  var tmp;
  if (match) {
    var match$1 = match[0];
    tmp = typeof match$1 === "number" || match$1.tag || match$1[0] !== 1 ? Css.backgroundImage(Css.url("/images/ui/sign_tree.png")) : Css.backgroundImage(Css.url("/images/ui/sign_tree_active.png"));
  } else {
    tmp = Css.backgroundImage(Css.url("/images/ui/sign_tree.png"));
  }
  var match$2 = context.selectedElement;
  return React.createElement("div", {
              className: toolbar
            }, React.createElement("button", {
                  className: Curry._1(Css.merge, /* :: */[
                        button,
                        /* :: */[
                          Curry._1(Css.style, /* :: */[
                                tmp,
                                /* [] */0
                              ]),
                          /* [] */0
                        ]
                      ]),
                  onClick: (function (param) {
                      return Curry._1(context.setSelectedElement, (function (param) {
                                    return /* Building */[/* Tree */Block.__(0, [/* DarkGreen */1])];
                                  }));
                    })
                }), React.createElement("button", {
                  className: Curry._1(Css.merge, /* :: */[
                        button,
                        /* :: */[
                          Curry._1(Css.style, /* :: */[
                                match$2 ? Css.backgroundImage(Css.url("/images/ui/sign_sell.png")) : Css.backgroundImage(Css.url("/images/ui/sign_sell_active.png")),
                                /* [] */0
                              ]),
                          /* [] */0
                        ]
                      ]),
                  onClick: (function (param) {
                      return Curry._1(context.setSelectedElement, (function (param) {
                                    return /* Sell */0;
                                  }));
                    })
                }));
}

var make = Ui;

exports.Styles = Styles;
exports.make = make;
/* toolbar Not a pure module */

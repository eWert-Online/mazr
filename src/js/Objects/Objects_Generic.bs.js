'use strict';

var Css = require("bs-css-emotion/src/Css.js");
var Curry = require("bs-platform/lib/js/curry.js");

var gameObject = Curry._1(Css.style, /* :: */[
      Css.position(Css.absolute),
      /* :: */[
        Css.top(Css.zero),
        /* :: */[
          Css.bottom(Css.zero),
          /* :: */[
            Css.left(Css.zero),
            /* :: */[
              Css.right(Css.zero),
              /* :: */[
                Css.display(Css.block),
                /* :: */[
                  Css.backgroundSize(Css.contain),
                  /* :: */[
                    Css.backgroundPosition(Css.center),
                    /* :: */[
                      Css.backgroundRepeat(Css.noRepeat),
                      /* [] */0
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
  gameObject: gameObject
};

exports.Styles = Styles;
/* gameObject Not a pure module */

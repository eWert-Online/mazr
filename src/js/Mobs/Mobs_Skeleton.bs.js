'use strict';


function make(coordinates) {
  return {
          coordinates: coordinates,
          health: 100,
          speed: 500,
          typ: /* Skeleton */0
        };
}

exports.make = make;
/* No side effect */

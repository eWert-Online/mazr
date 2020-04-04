let translateTo = (coordinates: (int, int)) => {
  let (x, y) = coordinates;
  Css.(translate((float_of_int(x) *. 100.0)->pct, (float_of_int(y) *. 100.0)->pct));
};
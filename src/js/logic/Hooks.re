let useInterval = (callback: unit => unit, delay) => {
  let savedCallback = React.useRef(() => ());

  React.useEffect1(
    () => {
      React.Ref.setCurrent(savedCallback, callback);
      None;
    },
    [|callback|],
  );

  React.useEffect1(
    () => {
      let tick = React.Ref.current(savedCallback);
      let id = Js.Global.setInterval(tick, delay);
      Some(() => Js.Global.clearInterval(id));
    },
    [|delay|],
  );
};
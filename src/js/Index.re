open Css;

global("*", [boxSizing(borderBox), margin(0->px), padding(0->px), outlineStyle(none)]);
global("html, body, #app", [margin(0->px), height(100.0->pct)]);

ReactDOMRe.renderToElementWithId(<Game />, "app");
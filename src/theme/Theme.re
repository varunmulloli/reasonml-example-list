open Css;

let marginWidth = px(16);
let paddingWidth = px(8);

let backgroundColor = hex("ffffff");

let brandColor = hex("3d70b2");
let brandTextColor = hex("ffffff");

let buttonColor = hex("5596e6");
let buttonTextColor = hex("f5f7fa");
let buttonHoverColor = hex("41d6c3");

let buttonStyle = style([
  marginTop(marginWidth),
  paddingLeft(marginWidth),
  paddingRight(marginWidth),
  height(px(28)),
  outline(`zero, `none, buttonHoverColor),
  background(buttonColor),
  color(buttonTextColor),
  cursor(`pointer),
  border(px(1), solid, buttonHoverColor),
  hover([
    background(buttonHoverColor),
  ]),
]);

let borderColor = hex("dfe3e6");

let itemHoverColor = hex("f0f3f6");

let roboto = fontFace(
  ~fontFamily="Roboto, sans-serif",
  ~src=[localUrl("Roboto")],
  ~fontStyle=normal,
  ~fontWeight=`num(400),
  (),
);

global("body", [
  margin(px(0)),
  fontFamily(`custom(roboto))
]);
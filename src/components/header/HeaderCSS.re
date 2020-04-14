open Css;

let container = style([
  display(flexBox),
  background(Theme.brandColor),
  color(Theme.brandTextColor),
  height(px(50)),
]);

let titleContainer = style([
  fontFamily(`custom(Theme.roboto)),
  fontWeight(`num(700)),
  fontSize(px(24)),
  marginTop(`auto),
  marginBottom(`auto),
  marginLeft(Theme.marginWidth),
]);


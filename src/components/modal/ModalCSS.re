open Css;

let modalOverlay = style([
  position(`fixed),
  top(px(0)),
  left(px(0)),
  width(pct(100.)),
  height(pct(100.)),
  zIndex(50),
  background(rgba(0, 0, 0, 0.6)),
]);

let modal = style([
  display(`block),
  width(px(600)),
  maxWidth(pct(100.)),
  height(px(140)),
  maxHeight(pct(100.)),
  position(`fixed),
  zIndex(100),
  left(pct(50.)),
  top(pct(25.)),
  transform(translate(pct(-50.), pct(-50.))),
  background(Theme.backgroundColor),
  boxShadow(Shadow.box(~x=px(0), ~y=px(0), ~blur=px(60), ~spread=px(10), rgba(0, 0, 0, 0.9))),
]);

let modalHeader = style([
  display(`flex),
  background(Theme.brandColor),
  color(Theme.brandTextColor),
]);

let modalHeaderTitle = style([
  flexGrow(1.0),
  padding(Theme.paddingWidth),
]);

let modalCloseButton = style([
  zIndex(1),
  fontSize(px(28)),
  cursor(`pointer),
  paddingLeft(Theme.paddingWidth),
  paddingRight(Theme.paddingWidth),
  hover([
    background(Theme.buttonColor),
  ]),
]);

let modalBody = style([
  position(`absolute),
  top(px(0)),
  left(px(0)),
  width(pct(100.)),
  height(pct(100.)),
  overflow(`auto),
  marginTop(px(34)),
]);
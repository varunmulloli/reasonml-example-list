open Css;

let container = style([
  width(px(600)),
  marginTop(Theme.marginWidth),
  marginLeft(`auto),
  marginRight(`auto),
]);

let createNewButton = merge([
  Theme.buttonStyle,
  style([
    width(pct(100.)),
    height(px(37)),
    textAlign(`center),
  ]),
]);

let listItemContainer = style([
  display(`flex),
  border(px(1), solid, Theme.borderColor),
  marginTop(Theme.marginWidth),
  height(px(35)),
  lineHeight(px(35)),
]);

let listItem = style([
  flexGrow(1.0),
  paddingLeft(Theme.paddingWidth),
  cursor(`pointer),
  hover([
    background(Theme.itemHoverColor),
  ]),
]);

let actionButton = style([
  width(px(25)),
  textAlign(`right),
  paddingTop(px(4)),
  paddingBottom(px(4)),
  paddingLeft(Theme.paddingWidth),
  paddingRight(Theme.paddingWidth),
  cursor(`pointer),
  hover([
    background(Theme.itemHoverColor),
  ]),
]);

let modalBodyContents = style([
  margin(Theme.marginWidth),
]);

let itemNameInput = style([
  width(pct(100.)),
  height(px(24)),
]);

let submitButton = Theme.buttonStyle;

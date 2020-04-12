let decodeListItem = (json: Js.Json.t) : Types.listItem => Json.Decode.{
  id: json |> field("id", int),
  name: json |> field("name", string),
};

let encodeListItem = (listItem: Types.listItem) : Js.Json.t => Json.Encode.(
  object_([
    ("id", int(listItem.id)),
    ("name", string(listItem.name)),
  ])
);

let decodeListData = (json: Js.Json.t) : Types.listData => Json.Decode.{
  listItems: json |> field("listItems", list(decodeListItem)),
};

let encodeListData = (listData: Types.listData) : Js.Json.t => Json.Encode.(
  object_([
    ("listItems", listData.listItems |> list(encodeListItem)),
  ])
);
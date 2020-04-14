module type ListServiceSignature = {
  let fetchListItems: unit => list(Types.listItem);
  let createNewItem: string => list(Types.listItem);
  let editItem: (int, string) => list(Types.listItem);
  let deleteItem: int => list(Types.listItem);
};

module LocalStorage : ListServiceSignature = {
  let appName: string = "reasonreact_example_list";

  let emitErrorAsLogAndIgnore = (message: exn) => {
    Js.Console.error(message);
  };

  let writeToLocalStorage = (content: string) : unit => {
    open Dom.Storage;
    localStorage |> setItem(appName, content); 
  };

  let writeListDataToLocalStorage = (listData: Types.listData) : unit => {
    listData |> JsonHelper.encodeListData |> Json.stringify |> writeToLocalStorage;
  };

  let initializeLocalStorage = () : unit => {
    let emptyData: Types.listData = { 
      listItems: [],
    };
    writeListDataToLocalStorage(emptyData); 
  };

  let emitErrorAndInitializeLocalStorage = (error: exn) : unit => {
    emitErrorAsLogAndIgnore(error);
    initializeLocalStorage();
  };

  let retrieveDataOrInitializeLocalStorage = () : option(string) => {
    open Dom.Storage;
    let data: option(string) = localStorage |> getItem(appName);
    switch(data) {
      | Some(json) => Some(json)
      | None => { initializeLocalStorage(); None; }
    };
  }

  let getListItems = (listData: Types.listData) : list(Types.listItem) => listData.listItems;

  let parseListDataAsJson = data => 
    switch(data) {
    | Some(jsonString) =>  Some(Json.parseOrRaise(jsonString))
    | None => None
  };

  let decodeListDataJson = (listDataJson: option(Js.Json.t)) : list(Types.listItem) => 
    switch(listDataJson) {
    | Some(json) => json |> JsonHelper.decodeListData |> getListItems
    | None => []
  };

  let fetchListItems = () : list(Types.listItem) => {
    let data: option(string) = retrieveDataOrInitializeLocalStorage();
    let listDataJson: option(Js.Json.t) = try (parseListDataAsJson(data)) {
      | error => { emitErrorAndInitializeLocalStorage(error); None; }
    }
    let listItems: list(Types.listItem) = try (decodeListDataJson(listDataJson)) {
      | error => { emitErrorAndInitializeLocalStorage(error); []; }
    };
    listItems;
  };

  let createNewItem = (itemName: string) : list(Types.listItem) => {
    let listItems: list(Types.listItem) = fetchListItems();
    let itemId: int = try (List.hd(listItems).id + 1) {
      | _ => 1
    };
    let item: Types.listItem = {
      id: itemId,
      name: itemName,
    };
    let newListData: Types.listData = {
      listItems: [item, ...listItems],
    };
    writeListDataToLocalStorage(newListData);
    fetchListItems();
  };

  let editItem = (id: int, newName: string) : list(Types.listItem) => {
    let newItem: Types.listItem = {
      id: id,
      name: newName,
    };
    let replaceItemWithId = (item: Types.listItem) : Types.listItem => (item.id === id) ? newItem : item;
    let listData: list(Types.listItem) = fetchListItems();
    let newListData: Types.listData = {
      listItems: List.map(replaceItemWithId, listData),
    };
    writeListDataToLocalStorage(newListData);
    fetchListItems();
  };

  let deleteItem = (id: int) : list(Types.listItem) => {
    let allOtherItems = (item: Types.listItem) : bool => item.id !== id;
    let listData: list(Types.listItem) = fetchListItems();
    let newListData: Types.listData = {
      listItems: List.filter(allOtherItems, listData),
    };
    writeListDataToLocalStorage(newListData);
    fetchListItems();
  };
};
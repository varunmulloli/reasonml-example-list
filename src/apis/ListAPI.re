let fetchListItems = () : list(Types.listItem) => {
  ListService.LocalStorage.fetchListItems();
};

let createNewItem = (name: string) : list(Types.listItem) => {
  ListService.LocalStorage.createNewItem(name);
};

let editItem = (id: int, newName: string) : list(Types.listItem) => {
  ListService.LocalStorage.editItem(id, newName);
};

let deleteItem = (id: int) : list(Types.listItem) => {
  ListService.LocalStorage.deleteItem(id);
};

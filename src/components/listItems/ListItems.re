type modalStates = 
  | Closed
  | Creating
  | Editing(int);

type listAction = 
  | Fetch
  | CreateNew(string)
  | Edit(int, string)
  | Delete(int);

let initialState: Types.listData = { 
  listItems: [],
};

let reducer = (state: Types.listData, action: listAction) : Types.listData => 
  switch (action) {
  | Fetch => { listItems: ListAPI.fetchListItems() } 
  | CreateNew(name) => { listItems: ListAPI.createNewItem(name) }
  | Edit(id, name) => { listItems: ListAPI.editItem(id, name) }
  | Delete(id) => { listItems: ListAPI.deleteItem(id) }
};

let displayListItem = 
  (openModal: int => unit, deleteItem: int => unit, setNewName: string => unit) => 
  (index: int, listItem: Types.listItem) : React.element => {

  let openModalAndPrefillInputField = _ => {
    openModal(listItem.id);
    setNewName(listItem.name); 
  };

  let deleteCurrentItem = _ => {
    deleteItem(listItem.id);
  };

  <div key=string_of_int(index) className=ListItemsCSS.listItemContainer title=("Open " ++ listItem.name)>
    <div className=ListItemsCSS.listItem>
      {React.string(listItem.name)}
    </div>

    <div className=ListItemsCSS.actionButton title=("Edit " ++ listItem.name) onClick=openModalAndPrefillInputField>
      <img src="./public/edit.png" width="20" />
    </div>
    <div className=ListItemsCSS.actionButton title=("Delete " ++ listItem.name) onClick=deleteCurrentItem>
      <img src="./public/delete.png" width="20" />
    </div>
  </div>
};

let displayModal = 
  (closeModal: unit => unit, itemName: string, setNewName: string => unit) => 
  (dispatchAction: string => unit, modalTitle: string, buttonTitle: string) : React.element => {

  let processTextInput = (event: ReactEvent.Form.t) : unit => {
    setNewName(ReactEvent.Form.target(event)##value);
  };

  let dispatchActionAndCloseModal = _ => {
    dispatchAction(itemName); 
    closeModal();
  };
  
  <Modal closeModal=closeModal title=modalTitle>
    <div className=ListItemsCSS.modalBodyContents>
      <input value=itemName onChange=processTextInput placeholder="Item Name" className=ListItemsCSS.itemNameInput type_="text" autoFocus=true />
      
      <button className=ListItemsCSS.submitButton onClick=dispatchActionAndCloseModal>
        {React.string(buttonTitle)}
      </button>
    </div>
  </Modal>
};

  
[@react.component]
let make = () => {
  let (state, dispatch) = React.useReducer(reducer, initialState);
  let (showModal, setShowModal) = React.useState(() => Closed);
  let (itemName, setItemName) = React.useState(() => "");
  let closeModal = () => { 
    setShowModal(_ => Closed);
    setItemName(_ => "");
  }
  let openModalForCreate = () =>  setShowModal(_ => Creating);
  let openModalForEdit = (id: int) : unit =>  setShowModal(_ => Editing(id));
  let setNewName = (name: string) : unit=> setItemName(_ => name);
  let dispatchCreateAction = (name: string) : unit => dispatch(CreateNew(name));
  let dispatchEditAction = (id: int) => (name: string) : unit => dispatch(Edit(id, name));
  let dispatchDeleteAction = (id: int) : unit => dispatch(Delete(id));

  let renderListItem = displayListItem(openModalForEdit, dispatchDeleteAction, setNewName);
  let renderModal = displayModal(closeModal, itemName, setNewName);
  
  React.useEffect0(() => {
    dispatch(Fetch);
    None;
  });  

  <div className=ListItemsCSS.container>
    <button className=ListItemsCSS.createNewButton title="Create New Item" onClick={_ => openModalForCreate()}>
      {React.string("+ CREATE NEW ITEM")}
    </button>

    { state.listItems |> List.mapi(renderListItem) |> Array.of_list |> ReasonReact.array }

    { 
      switch showModal {
      | Creating => renderModal(dispatchCreateAction, "Create New Item", "Create")
      | Editing(id) => renderModal(dispatchEditAction(id), "Update Item Name", "Update")
      | Closed => <div></div>
      };
    }
  </div>
};
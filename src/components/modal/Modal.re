[@react.component]
let make = (~closeModal: unit => unit, ~title: string, ~children) => {
  <>
    <div className=ModalCSS.modal>
      <div className=ModalCSS.modalHeader>
        <div className=ModalCSS.modalHeaderTitle>{React.string(title)}</div>
        <div className=ModalCSS.modalCloseButton onClick={_ => closeModal()}>
          {React.string({j|×|j})}
        </div>
      </div>

      <div className=ModalCSS.modalBody>
        {children}
      </div>
    </div>

    <div className=ModalCSS.modalOverlay onClick={_ => closeModal()}></div>
  </>
};
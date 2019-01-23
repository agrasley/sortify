open Utils;

requireCSS("./Select.css");

type state = {
  selected: int,
  isOpen: bool,
  selectRef: ref(option(Dom.element))
};

type action =
  | Select(int)
  | Close
  | Toggle;

type selectOption('optionType) = {
  key: string,
  optionType: 'optionType,
  text: string,
  onClick: (ReactEvent.Mouse.t, 'optionType) => unit,
};

type eventTarget;
type clickEvent = Js.t({
  .
  target: Dom.element,
});
[@bs.val] external document: eventTarget = "";
[@bs.send] external addClickEventListener: (eventTarget, [@bs.as "click"] _, (clickEvent => unit)) => unit = "addEventListener";
[@bs.send] external removeClickEventListener: (eventTarget, [@bs.as "click"] _, (clickEvent => unit)) => unit = "removeEventListener";
[@bs.send] external contains: (Dom.element, Dom.element) => bool = "";

let component = ReasonReact.reducerComponent("Select");

let setSectionRef = (theRef, {ReasonReact.state}) => {
  state.selectRef := Js.Nullable.toOption(theRef);
};

let make = (
  ~selected=0,
  ~options,
  _children,
) => {
  {
    ...component,
    initialState: () => { selected, isOpen: false, selectRef: ref(None) },
    reducer: (action, state) =>
      switch (action) {
      | Select(i) => ReasonReact.Update({ ...state, selected: i, isOpen: false })
      | Toggle => ReasonReact.Update({ ...state, isOpen: !state.isOpen })
      | Close => ReasonReact.Update({ ...state, isOpen: false })
      },
    didMount: self => {
      let onClick = event =>
        switch (self.state.selectRef^) {
          | None => ()
          | Some(theRef) => if (!theRef->contains(event##target)) self.send(Close)
        };
      document->addClickEventListener(onClick);
      self.onUnmount(() => document->removeClickEventListener(onClick));
    },
    render: self =>
      <div className="SelectContainer" ref=self.handle(setSectionRef)>
        <button type_="button"  onClick=(_event => self.send(Toggle)) className="SelectButton">
          { ReasonReact.string(options[self.state.selected].text) }
        </button>
        {
          if (self.state.isOpen)
              <ul className="SelectItems">
                {
                  options
                  |> Array.mapi(
                    (i, { text, onClick, optionType, key }) => {
                      let handleClick = event => {
                        self.send(Select(i));
                        onClick(event, optionType);
                      };
                      <li key=key onClick=handleClick className="SelectItem">
                        { ReasonReact.string(text) }
                      </li>
                    }
                  )
                  |> ReasonReact.array;
                }
              </ul>
          else
            ReasonReact.null
        }
      </div>,
  }
}
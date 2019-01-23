Utils.requireCSS("./Search.css");

type state = string;

type action = string;

let component = ReasonReact.reducerComponent("Search");


let make = (~onSubmit, _children) => {
  let handleKeyPress = (event, self) =>
    if (event->ReactEvent.Keyboard.key === "Enter") onSubmit(self.ReasonReact.state);
  {
    ...component,
    initialState: () => "",
    reducer: (action, _state) => ReasonReact.Update(action),
    render: self => {
      let handleChange = (event) => self.ReasonReact.send(event->ReactEvent.Form.target##value);
      <input
        type_="text"
        value=self.state
        onChange=handleChange
        onKeyPress=self.handle(handleKeyPress)
        className="TextInput"
        placeholder="Search for an album"
      />
    },
  }
}
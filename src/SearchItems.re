Utils.requireCSS("./SearchItems.css");
let component = ReasonReact.statelessComponent("SearchItems");

let make = (~items, ~handleClick, _children) => {
  ...component,
  render: _self => 
    <ul className="Container">
      { ReasonReact.array(Array.map(
          item =>
            <li key=item.Data.id onClick=handleClick(item) className="Item">
              <img src=item.image className="Image" />
              <div className="Name">{ ReasonReact.string(item.Data.name) }</div>
              <div className="Artists">{ item.artists |> Js.Array.joinWith(",") |> ReasonReact.string }</div>
            </li>,
          items
        ))
      }
    </ul>,
};
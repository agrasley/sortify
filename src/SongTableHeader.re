let component = ReasonReact.statelessComponent("SongTableHeader");

let make = (~valueName: string, ~onHeaderClick, _children) => {
  ...component,
  render: _self =>
    <thead>
      <tr>
        <th onClick=onHeaderClick(Data.Value)>
          { ReasonReact.string("Rank") }
        </th>
        <th onClick=onHeaderClick(Data.Value)>
          { ReasonReact.string(valueName) }
        </th>
        <th onClick=onHeaderClick(Data.Title)>
          { ReasonReact.string("Title") }
        </th>
        <th onClick=onHeaderClick(Data.Artists)>
          { ReasonReact.string("Artist") }
        </th>
        <th onClick=onHeaderClick(Data.Album)>
          { ReasonReact.string("Album") }
        </th>
      </tr>
    </thead>,
};
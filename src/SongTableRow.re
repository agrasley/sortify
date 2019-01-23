let component = ReasonReact.statelessComponent("SongTableRow");

let make = (
  ~rank: int,
  ~value: string,
  ~title: string,
  ~artists: list(string),
  ~albumName: string,
  _children
) => {
  ...component,
  render: _self =>
    <tr>
      <td>
        { ReasonReact.string(string_of_int(rank)) }
      </td>
      <td>
        { ReasonReact.string(value) }
      </td>
      <td>
        { ReasonReact.string(title) }
      </td>
      <td>
        { ReasonReact.string(String.concat(", ", artists)) }
      </td>
      <td>
        { ReasonReact.string(albumName) }
      </td>
    </tr>,
};
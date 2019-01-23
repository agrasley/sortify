let component = ReasonReact.statelessComponent("SongTable");

let valueToStr = (value: Data.value, songAttrs: Data.songAttrs) =>
  switch value {
  | Popularity => string_of_int(songAttrs.popularity)
  | Danceability => Js.String.make(songAttrs.danceability)
  | Energy => Js.String.make(songAttrs.energy)
  | Speechiness => Js.String.make(songAttrs.speechiness)
  | Acousticness => Js.String.make(songAttrs.acousticness)
  | Instrumentalness => Js.String.make(songAttrs.instrumentalness)
  | Liveness => Js.String.make(songAttrs.liveness)
  | Valence => Js.String.make(songAttrs.valence)
  | Tempo => Js.String.make(songAttrs.tempo)
  | Loudness => Js.String.make(songAttrs.loudness)
  };

let make = (
  ~songs: array((int, Data.song)),
  ~value: Data.value,
  ~onHeaderClick,
  _children
) => {
  ...component,
  render: _self =>
    <table>
      <SongTableHeader valueName=Data.getValueName(value) onHeaderClick=onHeaderClick />
      <tbody>
        {
          songs
          |> Array.map(
            ( (i, song: Data.song) ) => 
              <SongTableRow
                key=song.id
                rank={ i+1 }
                value=valueToStr(value, song.attrs)
                title=song.display.title
                artists=song.display.artists
                albumName=song.display.albumName
              />
          )
          |> ReasonReact.array
        }
      </tbody>
    </table>,
};
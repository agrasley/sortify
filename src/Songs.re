open Utils;

requireCSS("./Songs.css");

type state = {
  value: Data.value,
  sortBy: Data.sortBy,
  songs: array((int, Data.song)),
};

type action =
  | UpdateValue(Data.value)
  | SortBy(Data.sortBy);

let component = ReasonReact.reducerComponentWithRetainedProps("Songs");

let flippedSort = flip(Belt.SortArray.stableSortBy);
let sortFn = (getter: Data.song => 'a) => {
  let tupleGetter = ((_, song)) => getter(song);
  flippedSort((a, b) => switch (compare(tupleGetter(a), tupleGetter(b))) {
  | 0 => compare(snd(a).id, snd(b).id)
  | i => i
  });
}


let sortSongsByStr = (sortBy: Data.sortBy, songs: array((int, Data.song))) => {
  let getStr = Data.(switch(sortBy) {
  | Title => song => song.display.title
  | Album => song => song.display.albumName
  | _ => song => String.concat("", song.display.artists)
  });
  sortFn(getStr, songs);
}

let sortSongsByValue = (value: Data.value, songs: array((int, Data.song))) => {
  let sort = Data.(switch (value) {
  | Popularity => sortFn(song => song.attrs.popularity)
  | Danceability => sortFn(song => song.attrs.danceability)
  | Energy => sortFn(song => song.attrs.energy)
  | Speechiness => sortFn(song => song.attrs.speechiness)
  | Acousticness => sortFn(song => song.attrs.acousticness)
  | Instrumentalness => sortFn(song => song.attrs.instrumentalness)
  | Liveness => sortFn(song => song.attrs.liveness)
  | Valence => sortFn(song => song.attrs.valence)
  | Tempo => sortFn(song => song.attrs.tempo)
  | Loudness => sortFn(song => ~-.song.attrs.loudness)
  });
  Array.mapi((rank, (_, song)) => (rank, song), songs |> sort |> Belt.Array.reverse);
}

let make = (~songs, _children) => {
  ...component,
  initialState: () => {
    value: Data.Popularity,
    sortBy: Data.Value,
    songs: songs |> Array.mapi((i, song) => (i, song)) |> sortSongsByValue(Data.Popularity),
  },
  retainedProps: songs,
  willReceiveProps: self =>
    if (self.retainedProps !== songs)
      {
        value: Data.Popularity,
        sortBy: Data.Value,
        songs: sortSongsByValue(Data.Popularity, Array.mapi((i, song) => (i, song), songs: array(Data.song))),
      }
    else 
      self.state,
  reducer: (action, state) =>
    switch (action, state) {
    | (UpdateValue(value), { value: stValue }) when value === stValue => ReasonReact.NoUpdate
    | (UpdateValue(value), _) =>
        ReasonReact.Update({
          sortBy: Data.Value,
          value: value,
          songs: sortSongsByValue(value, state.songs),
        })
    | (SortBy(sortBy), { sortBy: stSortBy, songs: songs }) when sortBy === stSortBy =>
        ReasonReact.Update({ ...state, songs: Belt.Array.reverse(songs) })
    | (SortBy(Data.Value), { value: value }) =>
        ReasonReact.Update({
          sortBy: Data.Value,
          value: value,
          songs: sortSongsByValue(value, state.songs),
        })
    | (SortBy(sortBy), _) =>
        ReasonReact.Update({
          ...state,
          sortBy: sortBy,
          songs: sortSongsByStr(sortBy, state.songs),
        })
    },
  render: self => {
    let selectOptions: array(Select.selectOption(Data.value)) = 
      Array.map(
        value => Select.{
          key: Data.getValueName(value),
          optionType: value,
          text: Data.getValueName(value),
          onClick: (_event, value) => self.send(UpdateValue(value))
        },
        [|
          Popularity,
          Danceability,
          Energy,
          Speechiness,
          Acousticness,
          Instrumentalness,
          Liveness,
          Valence,
          Tempo,
          Loudness
        |]
      );
    <div>
      <Select options=selectOptions />
      <div className="TableGrid">
        <SongTable
          songs=self.state.songs
          value=self.state.value
          onHeaderClick=((sortBy, _event) => self.send(SortBy(sortBy)))
        />
      </div>
    </div>
  },
};
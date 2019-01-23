type state = array(Data.song);

type action = SetSongs(array(Data.song));

let component = ReasonReact.reducerComponent("App");

let make = _children => {
  ...component,
  initialState: () => [||],
  reducer: (SetSongs(songs), _state) => ReasonReact.Update(songs),
  render: self => {
    let handleItemClick = searchItem  => Js.Promise.(
      SpotifyAPI.Request.getAlbumHack(searchItem.Data.id)
        |> then_(trackIds =>
          all2((
            SpotifyAPI.Request.getTracksHack(trackIds),
            SpotifyAPI.Request.getAudioFeaturesHack(trackIds)
          ))
        )
        |> then_(((tracks: array(SpotifyAPI.track), features: array(SpotifyAPI.audioFeatures))) => {
          let sortedTracks = Belt.SortArray.stableSortBy(tracks, (a, b) => compare(a.id, b.id));
          let sortedFeatures = Belt.SortArray.stableSortBy(features, (a, b) => compare(a.id, b.id));
          let zipped = Belt.Array.zip(sortedTracks, sortedFeatures);
          self.send(SetSongs(zipped |> Array.map(Data.songAdapter)))
          |> resolve;
        })
        |> ignore
    );
    <div>
      <Picker handleItemClick=handleItemClick handleSearchSubmit={ () => self.send(SetSongs([||])) } />
      { if (Array.length(self.state) > 0) <Songs songs=self.state /> else ReasonReact.null  }
    </div>
  },
}
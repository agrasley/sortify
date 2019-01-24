type state = {
  songs: array(Data.song),
  token: string,
};

type action = SetSongs(array(Data.song));

let component = ReasonReact.reducerComponent("App");

let getTokenFromHash = str => {
  let r = [%bs.re "/token=(.*)&/"]
  let match = str |> Js.String.match(r);
  switch(match) {
  | Some(arr) when Array.length(arr) > 1 => Some(arr[1])
  | _ => None
  }
};

[@bs.val] external replaceLocation: string => 'a = "document.location.replace";

let spotifyAccountsUrl = "https://accounts.spotify.com/authorize?client_id=af50ed257bcb4783bb2d86c74b7c54a1&redirect_uri=https:%2F%2Fagrasley.github.io%2Fsortify&response_type=token";

let make = _children => {
  ...component,
  initialState: () => {
    let optionToken = ReasonReact.Router.dangerouslyGetInitialUrl().hash |> getTokenFromHash;
    let token = switch(optionToken) {
    | Some(token) => token
    | None => replaceLocation(spotifyAccountsUrl)
    };
    {
      songs: [||],
      token: token,
    }
  },
  reducer: (SetSongs(songs), state) => ReasonReact.Update({ ...state, songs }),
  render: self => {
    let handleItemClick = searchItem  => Js.Promise.(
      SpotifyAPI.Request.getAlbum(self.state.token, searchItem.Data.id)
        |> then_(trackIds =>
          all2((
            SpotifyAPI.Request.getTracks(self.state.token, trackIds),
            SpotifyAPI.Request.getAudioFeatures(self.state.token, trackIds)
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
      <Picker
        handleItemClick=handleItemClick
        handleSearchSubmit={ () => self.send(SetSongs([||])) }
        token=self.state.token
      />
      { if (Array.length(self.state.songs) > 0) <Songs songs=self.state.songs /> else ReasonReact.null  }
    </div>
  },
}
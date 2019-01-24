type albumSearchResult = {
  id: string,
  name: string,
  artists: array(string),
  image: string,
};

type albumTracks = array(string);

type track = {
  albumName: string,
  artists: array(string),
  name: string,
  popularity: int,
  id: string,
};

type audioFeatures = {
  id: string,
  danceability: float,
  energy: float,
  speechiness: float,
  acousticness: float,
  instrumentalness: float,
  liveness: float,
  valence: float,
  tempo: float,
  loudness: float,
};

module Decode = {
  let accessToken = json => Json.Decode.(
    json |> field("access_token", string)
  );

  let albumSearchResults = json => Json.Decode.(
    json |> field("albums", field("items", array(json =>
      {
        id: json |> field("id", string),
        name: json |> field("name", string),
        artists: json |> field("artists", array(field("name", string))),
        image: {
          let arr = json |> field("images", array(field("url", string)));
          arr[1]
        },
      }
    )))
  ); 

  let albumTracks = json => Json.Decode.(
    json |> field("tracks", field("items", array(field("id", string))))
  );

  let tracks = json => Json.Decode.(
    json |> field("tracks", array(json =>
      {
        albumName: json |> field("album", field("name", string)),
        artists: json |> field("artists", array(field("name", string))),
        name: json |> field("name", string),
        popularity: json |> field("popularity", int),
        id: json |> field("id", string),
      }
    ))
  );

  let audioFeatures = json => Json.Decode.(
    json |> field("audio_features", array(json =>
      {
        id: json |> field("id", string),
        danceability: json |> field("danceability", Json.Decode.float),
        energy: json |> field("energy", Json.Decode.float),
        speechiness: json |> field("speechiness", Json.Decode.float),
        acousticness: json |> field("acousticness", Json.Decode.float),
        instrumentalness: json |> field("instrumentalness", Json.Decode.float),
        liveness: json |> field("liveness", Json.Decode.float),
        valence: json |> field("valence", Json.Decode.float),
        tempo: json |> field("tempo", Json.Decode.float),
        loudness: json |> field("loudness", Json.Decode.float),
      }
    ))
  );
};

module Request = {
  [@bs.val] external replaceLocation: string => 'a = "document.location.replace";
  let spotifyAccountsUrl = "https://accounts.spotify.com/authorize?client_id=af50ed257bcb4783bb2d86c74b7c54a1&redirect_uri=https:%2F%2Fagrasley.github.io%2Fsortify&response_type=token";
  let redirectToAuth = () => replaceLocation(spotifyAccountsUrl);
  let apiUrl = "https://api.spotify.com/v1";
  let searchUrl = (q: string) => {j|$(apiUrl)/search?q=$(q)&type=album&limit=5&market=US|j};
  let albumUrl = (id: string) => {j|$(apiUrl)/albums/$(id)?market=US|j};
  let tracksUrl = (ids: array(string)) => {
    let strIds = Js.Array.joinWith(",", ids);
    {j|$(apiUrl)/tracks?ids=$(strIds)&market=US|j}
  };
  let audioFeaturesUrl = (ids: array(string)) => {
    let strIds = Js.Array.joinWith(",", ids);
    {j|$(apiUrl)/audio-features?ids=$(strIds)|j}
  };

  let makeRequest = (token: string, url) =>
    Js.Promise.(
      Fetch.fetchWithInit(
        url,
        Fetch.RequestInit.make(
          ~method_=Get,
          ~headers=Fetch.HeadersInit.make({
            "Accept": "application/json",
            "Authorization": {j|Bearer $(token)|j},
          }),
          ()
        )
      )
      |> then_(response => {
        let status = response |> Fetch.Response.status;
        if (status === 401) {
          redirectToAuth();
        };
        response |> resolve;
      })
      |> then_(Fetch.Response.json)
    );
  
  let search = (token, q) => Js.Promise.(
    makeRequest(token, searchUrl(q))
      |> then_(json => json |> Decode.albumSearchResults |> resolve)
  );
  let getAlbum = (token, id) => Js.Promise.(
    makeRequest(token, albumUrl(id))
      |> then_(json => json |> Decode.albumTracks |> resolve)
  );
  let getTracks = (token, ids) => Js.Promise.(
    makeRequest(token, tracksUrl(ids))
      |> then_(json => json |> Decode.tracks |> resolve)
  );
  let getAudioFeatures = (token, ids) => Js.Promise.(
    makeRequest(token, audioFeaturesUrl(ids))
      |> then_(json => json |> Decode.audioFeatures |> resolve)
  );
};

type songAttrs = {
  popularity: int,
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

type songDisplay = {
  title: string,
  artists: list(string),
  albumName: string,
};

type song = {
  id: string,
  attrs: songAttrs,
  display: songDisplay,
};

let songAdapter = ((track: SpotifyAPI.track, features: SpotifyAPI.audioFeatures)) => {
  id: track.id,
  attrs: {
    popularity: track.popularity,
    danceability: features.danceability,
    energy: features.energy,
    speechiness: features.speechiness,
    acousticness: features.acousticness,
    instrumentalness: features.instrumentalness,
    liveness: features.liveness,
    valence: features.valence,
    tempo: features.tempo,
    loudness: features.loudness,
  },
  display: {
    title: track.name,
    artists: Belt.List.fromArray(track.artists),
    albumName: track.albumName
  },
};

type value =
  | Popularity
  | Danceability 
  | Energy 
  | Speechiness 
  | Acousticness 
  | Instrumentalness 
  | Liveness 
  | Valence 
  | Tempo 
  | Loudness;

let getValueName = value =>
  switch value {
  | Popularity => "Popularity"
  | Danceability => "Danceability"
  | Energy => "Energy"
  | Speechiness => "Speechiness"
  | Acousticness => "Acousticness"
  | Instrumentalness => "Instrumentalness"
  | Liveness => "Liveness"
  | Valence => "Valence"
  | Tempo => "Tempo"
  | Loudness => "Loudness"
  };

type sortBy = Value | Title | Artists | Album;

type searchType = AlbumT | ArtistT | PlaylistT;

let getSearchTypeName = searchType =>
  switch(searchType) {
  | ArtistT => "Artist"
  | AlbumT => "Album"
  | PlaylistT => "Playlist"
  };

type searchItem = {
  name: string,
  id: string,
  artists: array(string),
  image: string,
};

let searchItemAdapter = (fromJSON: SpotifyAPI.albumSearchResult) => {
  name: fromJSON.SpotifyAPI.name,
  id: fromJSON.SpotifyAPI.id,
  artists: fromJSON.SpotifyAPI.artists,
  image: fromJSON.SpotifyAPI.image,
};

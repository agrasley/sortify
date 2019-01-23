Utils.requireCSS("./Picker.css");

type state = {
  /* searchType: Data.searchType, */
  items: array(Data.searchItem),
};

type action =
  /* | SetSearchType(Data.searchType) */
  | SetItems(array(Data.searchItem));

let component = ReasonReact.reducerComponent("Picker");

let make = (~handleItemClick, ~handleSearchSubmit, _children) => {
  ...component,
  initialState: () => { /* searchType: Data.ArtistT, */ items: [||] },
  reducer: (action, _state) =>
    switch(action) {
    /* | SetSearchType(searchType) => ReasonReact.Update({ ...state, searchType }) */
    | SetItems(items) => ReasonReact.Update({ /* ...state, */ items: items })
    },
  render: self => {
    /* let selectOptions: array(Select.selectOption(Data.searchType)) = 
      Array.map(
        searchType => Select.{
          key: Data.getSearchTypeName(searchType),
          optionType: searchType,
          text: Data.getSearchTypeName(searchType),
          onClick: (_event, searchType) => self.send(SetSearchType(searchType))
        },
        [|
          ArtistT,
          AlbumT,
          PlaylistT,
        |]
      ); */
    let handleSubmit = q =>
      if (String.length(q) > 0) {
        handleSearchSubmit();
        Js.Promise.(
          SpotifyAPI.Request.searchHack(q) |> then_(fromJSON =>
            self.send(SetItems(fromJSON |> Array.map(Data.searchItemAdapter)))
            |> resolve
          ) |> ignore
        );
      };
    let handleClick = (searchItem, _event) => {
      self.send(SetItems([||]));
      handleItemClick(searchItem);
    };
    <div className="Picker">
      /* <Select options=selectOptions /> */
      <div className="SearchBox">
        <Search onSubmit=handleSubmit />
      </div>
      <SearchItems items=self.state.items handleClick=handleClick />
    </div>
  },
};
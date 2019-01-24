// Generated by BUCKLESCRIPT VERSION 4.0.14, PLEASE EDIT WITH CARE
'use strict';

var $$Array = require("bs-platform/lib/js/array.js");
var Block = require("bs-platform/lib/js/block.js");
var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");
var Belt_Array = require("bs-platform/lib/js/belt_Array.js");
var Caml_array = require("bs-platform/lib/js/caml_array.js");
var ReasonReact = require("reason-react/src/ReasonReact.js");
var Belt_SortArray = require("bs-platform/lib/js/belt_SortArray.js");
var Caml_primitive = require("bs-platform/lib/js/caml_primitive.js");
var Data$ReactTemplate = require("./Data.bs.js");
var Songs$ReactTemplate = require("./Songs.bs.js");
var Picker$ReactTemplate = require("./Picker.bs.js");
var SpotifyAPI$ReactTemplate = require("./SpotifyAPI.bs.js");

var component = ReasonReact.reducerComponent("App");

function getTokenFromHash(str) {
  var r = (/token=(.*)&/);
  var match_ = str.match(r);
  if (match_ !== null && match_.length > 1) {
    return Caml_array.caml_array_get(match_, 1);
  }
  
}

var spotifyAccountsUrl = "https://accounts.spotify.com/authorize?client_id=af50ed257bcb4783bb2d86c74b7c54a1&redirect_uri=https:%2F%2Fagrasley.github.io%2Fsortify&response_type=token";

function make(_children) {
  return /* record */[
          /* debugName */component[/* debugName */0],
          /* reactClassInternal */component[/* reactClassInternal */1],
          /* handedOffState */component[/* handedOffState */2],
          /* willReceiveProps */component[/* willReceiveProps */3],
          /* didMount */component[/* didMount */4],
          /* didUpdate */component[/* didUpdate */5],
          /* willUnmount */component[/* willUnmount */6],
          /* willUpdate */component[/* willUpdate */7],
          /* shouldUpdate */component[/* shouldUpdate */8],
          /* render */(function (self) {
              var handleItemClick = function (searchItem) {
                SpotifyAPI$ReactTemplate.Request[/* getAlbum */7](self[/* state */1][/* token */1], searchItem[/* id */1]).then((function (trackIds) {
                          return Promise.all(/* tuple */[
                                      SpotifyAPI$ReactTemplate.Request[/* getTracks */8](self[/* state */1][/* token */1], trackIds),
                                      SpotifyAPI$ReactTemplate.Request[/* getAudioFeatures */9](self[/* state */1][/* token */1], trackIds)
                                    ]);
                        })).then((function (param) {
                        var sortedTracks = Belt_SortArray.stableSortBy(param[0], (function (a, b) {
                                return Caml_primitive.caml_string_compare(a[/* id */4], b[/* id */4]);
                              }));
                        var sortedFeatures = Belt_SortArray.stableSortBy(param[1], (function (a, b) {
                                return Caml_primitive.caml_string_compare(a[/* id */0], b[/* id */0]);
                              }));
                        var zipped = Belt_Array.zip(sortedTracks, sortedFeatures);
                        return Promise.resolve(Curry._1(self[/* send */3], /* SetSongs */[$$Array.map(Data$ReactTemplate.songAdapter, zipped)]));
                      }));
                return /* () */0;
              };
              return React.createElement("div", undefined, ReasonReact.element(undefined, undefined, Picker$ReactTemplate.make(handleItemClick, (function (param) {
                                    return Curry._1(self[/* send */3], /* SetSongs */[/* array */[]]);
                                  }), self[/* state */1][/* token */1], /* array */[])), self[/* state */1][/* songs */0].length !== 0 ? ReasonReact.element(undefined, undefined, Songs$ReactTemplate.make(self[/* state */1][/* songs */0], /* array */[])) : null);
            }),
          /* initialState */(function (param) {
              var optionToken = getTokenFromHash(ReasonReact.Router[/* dangerouslyGetInitialUrl */3](/* () */0)[/* hash */1]);
              var token = optionToken !== undefined ? optionToken : document.location.replace(spotifyAccountsUrl);
              return /* record */[
                      /* songs : array */[],
                      /* token */token
                    ];
            }),
          /* retainedProps */component[/* retainedProps */11],
          /* reducer */(function (param, state) {
              return /* Update */Block.__(0, [/* record */[
                          /* songs */param[0],
                          /* token */state[/* token */1]
                        ]]);
            }),
          /* jsElementWrapped */component[/* jsElementWrapped */13]
        ];
}

exports.component = component;
exports.getTokenFromHash = getTokenFromHash;
exports.spotifyAccountsUrl = spotifyAccountsUrl;
exports.make = make;
/* component Not a pure module */

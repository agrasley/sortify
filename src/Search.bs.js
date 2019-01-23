// Generated by BUCKLESCRIPT VERSION 4.0.14, PLEASE EDIT WITH CARE
'use strict';

var Block = require("bs-platform/lib/js/block.js");
var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");
var ReasonReact = require("reason-react/src/ReasonReact.js");

require("./Search.css");

var component = ReasonReact.reducerComponent("Search");

function make(onSubmit, _children) {
  var handleKeyPress = function ($$event, self) {
    if ($$event.key === "Enter") {
      return Curry._1(onSubmit, self[/* state */1]);
    } else {
      return 0;
    }
  };
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
              var handleChange = function ($$event) {
                return Curry._1(self[/* send */3], $$event.target.value);
              };
              return React.createElement("input", {
                          className: "TextInput",
                          placeholder: "Search for an album",
                          type: "text",
                          value: self[/* state */1],
                          onKeyPress: Curry._1(self[/* handle */0], handleKeyPress),
                          onChange: handleChange
                        });
            }),
          /* initialState */(function (param) {
              return "";
            }),
          /* retainedProps */component[/* retainedProps */11],
          /* reducer */(function (action, _state) {
              return /* Update */Block.__(0, [action]);
            }),
          /* jsElementWrapped */component[/* jsElementWrapped */13]
        ];
}

exports.component = component;
exports.make = make;
/*  Not a pure module */

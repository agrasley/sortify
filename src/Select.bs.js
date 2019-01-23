// Generated by BUCKLESCRIPT VERSION 4.0.14, PLEASE EDIT WITH CARE
'use strict';

var $$Array = require("bs-platform/lib/js/array.js");
var Block = require("bs-platform/lib/js/block.js");
var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");
var Caml_array = require("bs-platform/lib/js/caml_array.js");
var Caml_option = require("bs-platform/lib/js/caml_option.js");
var ReasonReact = require("reason-react/src/ReasonReact.js");

require("./Select.css");

var component = ReasonReact.reducerComponent("Select");

function setSectionRef(theRef, param) {
  param[/* state */1][/* selectRef */2][0] = (theRef == null) ? undefined : Caml_option.some(theRef);
  return /* () */0;
}

function make($staropt$star, options, _children) {
  var selected = $staropt$star !== undefined ? $staropt$star : 0;
  return /* record */[
          /* debugName */component[/* debugName */0],
          /* reactClassInternal */component[/* reactClassInternal */1],
          /* handedOffState */component[/* handedOffState */2],
          /* willReceiveProps */component[/* willReceiveProps */3],
          /* didMount */(function (self) {
              var onClick = function ($$event) {
                var match = self[/* state */1][/* selectRef */2][0];
                if (match !== undefined && !Caml_option.valFromOption(match).contains($$event.target)) {
                  return Curry._1(self[/* send */3], /* Close */0);
                } else {
                  return /* () */0;
                }
              };
              document.addEventListener("click", onClick);
              return Curry._1(self[/* onUnmount */4], (function (param) {
                            document.removeEventListener("click", onClick);
                            return /* () */0;
                          }));
            }),
          /* didUpdate */component[/* didUpdate */5],
          /* willUnmount */component[/* willUnmount */6],
          /* willUpdate */component[/* willUpdate */7],
          /* shouldUpdate */component[/* shouldUpdate */8],
          /* render */(function (self) {
              return React.createElement("div", {
                          ref: Curry._1(self[/* handle */0], setSectionRef),
                          className: "SelectContainer"
                        }, React.createElement("button", {
                              className: "SelectButton",
                              type: "button",
                              onClick: (function (_event) {
                                  return Curry._1(self[/* send */3], /* Toggle */1);
                                })
                            }, Caml_array.caml_array_get(options, self[/* state */1][/* selected */0])[/* text */2]), self[/* state */1][/* isOpen */1] ? React.createElement("ul", {
                                className: "SelectItems"
                              }, $$Array.mapi((function (i, param) {
                                      var onClick = param[/* onClick */3];
                                      var optionType = param[/* optionType */1];
                                      var handleClick = function ($$event) {
                                        Curry._1(self[/* send */3], /* Select */[i]);
                                        return Curry._2(onClick, $$event, optionType);
                                      };
                                      return React.createElement("li", {
                                                  key: param[/* key */0],
                                                  className: "SelectItem",
                                                  onClick: handleClick
                                                }, param[/* text */2]);
                                    }), options)) : null);
            }),
          /* initialState */(function (param) {
              return /* record */[
                      /* selected */selected,
                      /* isOpen */false,
                      /* selectRef : record */[/* contents */undefined]
                    ];
            }),
          /* retainedProps */component[/* retainedProps */11],
          /* reducer */(function (action, state) {
              if (typeof action === "number") {
                if (action !== 0) {
                  return /* Update */Block.__(0, [/* record */[
                              /* selected */state[/* selected */0],
                              /* isOpen */!state[/* isOpen */1],
                              /* selectRef */state[/* selectRef */2]
                            ]]);
                } else {
                  return /* Update */Block.__(0, [/* record */[
                              /* selected */state[/* selected */0],
                              /* isOpen */false,
                              /* selectRef */state[/* selectRef */2]
                            ]]);
                }
              } else {
                return /* Update */Block.__(0, [/* record */[
                            /* selected */action[0],
                            /* isOpen */false,
                            /* selectRef */state[/* selectRef */2]
                          ]]);
              }
            }),
          /* jsElementWrapped */component[/* jsElementWrapped */13]
        ];
}

exports.component = component;
exports.setSectionRef = setSectionRef;
exports.make = make;
/*  Not a pure module */

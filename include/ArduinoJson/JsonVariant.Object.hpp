// Copyright Benoit Blanchon 2014-2015
// MIT License
//
// Arduino JSON library
// https://github.com/bblanchon/ArduinoJson

#pragma once

namespace ArduinoJson {

inline JsonVariant::JsonVariant(JsonObject &object) {
  _type = Internals::JSON_OBJECT;
  _content.asObject = &object;
}
}

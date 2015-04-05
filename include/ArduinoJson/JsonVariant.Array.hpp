// Copyright Benoit Blanchon 2014-2015
// MIT License
//
// Arduino JSON library
// https://github.com/bblanchon/ArduinoJson

#pragma once

namespace ArduinoJson {

inline JsonVariant::JsonVariant(JsonArray &array) {
  _type = Internals::JSON_ARRAY;
  _content.asArray = &array;
}
}

// Copyright Benoit Blanchon 2014-2015
// MIT License
//
// Arduino JSON library
// https://github.com/bblanchon/ArduinoJson

#pragma once

namespace ArduinoJson {

inline JsonVariant::JsonVariant(unsigned long value) {
  _type = Internals::JSON_LONG;
  _content.asLong = value;
}
}

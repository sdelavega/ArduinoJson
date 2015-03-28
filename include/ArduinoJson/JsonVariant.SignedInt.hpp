// Copyright Benoit Blanchon 2014-2015
// MIT License
//
// Arduino JSON library
// https://github.com/bblanchon/ArduinoJson

#pragma once

namespace ArduinoJson {

inline JsonVariant::JsonVariant(signed int value) {
  _type = Internals::JSON_LONG;
  _content.asLong = value;
}

inline JsonVariant::operator signed int() const {
  return _type == Internals::JSON_LONG
             ? static_cast<signed int>(_content.asLong)
             : 0;
}

template <>
inline bool JsonVariant::is<signed int>() const {
  return _type == Internals::JSON_LONG;
}
}

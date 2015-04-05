// Copyright Benoit Blanchon 2014-2015
// MIT License
//
// Arduino JSON library
// https://github.com/bblanchon/ArduinoJson

#pragma once

namespace ArduinoJson {

inline JsonVariant::JsonVariant(unsigned short value) {
  _type = Internals::JSON_LONG;
  _content.asLong = value;
}

template <>
inline unsigned short JsonVariant::as<unsigned short>() const {
  return _type == Internals::JSON_LONG
             ? static_cast<unsigned short>(_content.asLong)
             : 0;
}

template <>
inline bool JsonVariant::is<unsigned short>() const {
  return _type == Internals::JSON_LONG;
}
}

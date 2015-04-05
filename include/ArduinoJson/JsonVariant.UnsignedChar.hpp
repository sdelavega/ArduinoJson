// Copyright Benoit Blanchon 2014-2015
// MIT License
//
// Arduino JSON library
// https://github.com/bblanchon/ArduinoJson

#pragma once

namespace ArduinoJson {

inline JsonVariant::JsonVariant(unsigned char value) {
  _type = Internals::JSON_LONG;
  _content.asLong = value;
}

template <>
inline unsigned char JsonVariant::as<unsigned char>() const {
  return _type == Internals::JSON_LONG
             ? static_cast<unsigned char>(_content.asLong)
             : 0;
}
}

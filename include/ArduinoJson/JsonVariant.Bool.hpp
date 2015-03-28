// Copyright Benoit Blanchon 2014-2015
// MIT License
//
// Arduino JSON library
// https://github.com/bblanchon/ArduinoJson

#pragma once

namespace ArduinoJson {

inline JsonVariant::JsonVariant(bool value) {
  _type = Internals::JSON_BOOLEAN;
  _content.asBoolean = value;
}

inline JsonVariant::operator bool() const {
  return _type == Internals::JSON_BOOLEAN ? _content.asBoolean : false;
}

template <>
inline bool JsonVariant::is<bool>() const {
  return _type == Internals::JSON_BOOLEAN;
}
}

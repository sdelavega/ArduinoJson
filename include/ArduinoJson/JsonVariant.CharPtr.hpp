// Copyright Benoit Blanchon 2014-2015
// MIT License
//
// Arduino JSON library
// https://github.com/bblanchon/ArduinoJson

#pragma once

namespace ArduinoJson {

inline JsonVariant::JsonVariant(const char* value) {
  _type = Internals::JSON_STRING;
  _content.asString = value;
}

template <>
inline const char* JsonVariant::as<const char*>() const {
  return _type == Internals::JSON_STRING ? _content.asString : NULL;
}

template <>
inline bool JsonVariant::is<const char*>() const {
  return _type == Internals::JSON_STRING;
}
}

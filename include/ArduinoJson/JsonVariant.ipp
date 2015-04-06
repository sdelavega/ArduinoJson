// Copyright Benoit Blanchon 2014-2015
// MIT License
//
// Arduino JSON library
// https://github.com/bblanchon/ArduinoJson

#pragma once

#include "JsonVariant.hpp"

namespace ArduinoJson {

inline JsonVariant::JsonVariant(bool value) {
  _type = Internals::JSON_BOOLEAN;
  _content.asBoolean = value;
}

inline JsonVariant::JsonVariant(const char *value) {
  _type = Internals::JSON_STRING;
  _content.asString = value;
}

inline JsonVariant::JsonVariant(double value, uint8_t decimals) {
  _type = static_cast<Internals::JsonVariantType>(
      Internals::JSON_DOUBLE_0_DECIMALS + decimals);
  _content.asDouble = value;
}

inline JsonVariant::JsonVariant(float value, uint8_t decimals) {
  _type = static_cast<Internals::JsonVariantType>(
      Internals::JSON_DOUBLE_0_DECIMALS + decimals);
  _content.asDouble = value;
}

inline JsonVariant::JsonVariant(JsonArray &array) {
  _type = Internals::JSON_ARRAY;
  _content.asArray = &array;
}

inline JsonVariant::JsonVariant(JsonObject &object) {
  _type = Internals::JSON_OBJECT;
  _content.asObject = &object;
}

inline JsonVariant::JsonVariant(signed char value) {
  _type = Internals::JSON_LONG;
  _content.asLong = value;
}

inline JsonVariant::JsonVariant(signed int value) {
  _type = Internals::JSON_LONG;
  _content.asLong = value;
}

inline JsonVariant::JsonVariant(signed long value) {
  _type = Internals::JSON_LONG;
  _content.asLong = value;
}

inline JsonVariant::JsonVariant(signed short value) {
  _type = Internals::JSON_LONG;
  _content.asLong = value;
}

inline JsonVariant::JsonVariant(unsigned char value) {
  _type = Internals::JSON_LONG;
  _content.asLong = value;
}

inline JsonVariant::JsonVariant(unsigned int value) {
  _type = Internals::JSON_LONG;
  _content.asLong = value;
}

inline JsonVariant::JsonVariant(unsigned long value) {
  _type = Internals::JSON_LONG;
  _content.asLong = value;
}

inline JsonVariant::JsonVariant(unsigned short value) {
  _type = Internals::JSON_LONG;
  _content.asLong = value;
}

template <typename T>
inline T JsonVariant::as() const {
  return Internals::matches<T>(_type) ? Internals::get<T>(_content)
                                      : Internals::invalid<T>();
}

// Tells weither the variant has the specified type.
// Returns true if the variant has type type T, false otherwise.
template <typename T>
inline bool JsonVariant::is() const {
  return Internals::matches<T>(_type);
}

// Copy the value of the specified variant
inline JsonVariant &JsonVariant::operator=(const JsonVariant &other) {
  _type = other._type;
  _content = other._content;
  return *this;
}
}

// Copyright Benoit Blanchon 2014-2015
// MIT License
//
// Arduino JSON library
// https://github.com/bblanchon/ArduinoJson

#pragma once

namespace ArduinoJson {
class JsonArray;
class JsonObject;

namespace Internals {

// Enumerated type to know the current type of a JsonVariant.
// The value determines which member of JsonVariantContent is used.
enum JsonVariantType {
  JSON_UNDEFINED,  // the JsonVariant has not been initialized
  JSON_ARRAY,      // the JsonVariant stores a pointer to a JsonArray
  JSON_OBJECT,     // the JsonVariant stores a pointer to a JsonObject
  JSON_BOOLEAN,    // the JsonVariant stores a bool
  JSON_STRING,     // the JsonVariant stores a const char*
  JSON_LONG,       // the JsonVariant stores a long

  // The following values are reserved for double values
  // Multiple values are used for double, depending on the number of decimal
  // digits that must be printed in the JSON output.
  // This little trick allow to save one extra member in JsonVariant
  JSON_DOUBLE_0_DECIMALS
  // JSON_DOUBLE_1_DECIMAL
  // JSON_DOUBLE_2_DECIMALS
  // ...
};

template <typename T>
inline bool matches(JsonVariantType) {
  return false;
}

template <>
inline bool matches<bool>(JsonVariantType t) {
  return t == JSON_BOOLEAN;
}

template <>
inline bool matches<char const*>(JsonVariantType t) {
  return t == JSON_STRING;
}

template <>
inline bool matches<double>(JsonVariantType t) {
  return t >= JSON_DOUBLE_0_DECIMALS;
}

template <>
inline bool matches<float>(JsonVariantType t) {
  return t >= JSON_DOUBLE_0_DECIMALS;
}

template <>
inline bool matches<JsonArray&>(JsonVariantType t) {
  return t == JSON_ARRAY;
}

template <>
inline bool matches<JsonArray const&>(JsonVariantType t) {
  return t == JSON_ARRAY;
}

template <>
inline bool matches<JsonObject&>(JsonVariantType t) {
  return t == JSON_OBJECT;
}

template <>
inline bool matches<JsonObject const&>(JsonVariantType t) {
  return t == JSON_OBJECT;
}

template <>
inline bool matches<signed char>(JsonVariantType t) {
  return t == JSON_LONG;
}

template <>
inline bool matches<signed int>(JsonVariantType t) {
  return t == JSON_LONG;
}

template <>
inline bool matches<signed long>(JsonVariantType t) {
  return t == JSON_LONG;
}

template <>
inline bool matches<signed short>(JsonVariantType t) {
  return t == JSON_LONG;
}

template <>
inline bool matches<unsigned char>(JsonVariantType t) {
  return t == JSON_LONG;
}

template <>
inline bool matches<unsigned int>(JsonVariantType t) {
  return t == JSON_LONG;
}

template <>
inline bool matches<unsigned long>(JsonVariantType t) {
  return t == JSON_LONG;
}

template <>
inline bool matches<unsigned short>(JsonVariantType t) {
  return t == JSON_LONG;
}
}
}

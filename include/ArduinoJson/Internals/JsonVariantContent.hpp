// Copyright Benoit Blanchon 2014-2015
// MIT License
//
// Arduino JSON library
// https://github.com/bblanchon/ArduinoJson

#pragma once

namespace ArduinoJson {

// Forward declarations
class JsonArray;
class JsonObject;

namespace Internals {

// A union that defines the actual content of a JsonVariant.
// The enum JsonVariantType determines which member is in use.
union JsonVariantContent {
  bool asBoolean;
  double asDouble;       // asDouble is also used for float
  long asLong;           // asLong is also used for char, short and int
  const char* asString;  // asString can be null
  JsonArray* asArray;    // asArray cannot be null
  JsonObject* asObject;  // asObject cannot be null
};

template <typename T>
T get(JsonVariantContent);

template <>
inline bool get<bool>(JsonVariantContent c) {
  return c.asBoolean;
}

template <>
inline char const* get<char const*>(JsonVariantContent c) {
  return c.asString;
}

template <>
inline double get<double>(JsonVariantContent c) {
  return c.asDouble;
}

template <>
inline float get<float>(JsonVariantContent c) {
  return static_cast<float>(c.asDouble);
}

template <>
inline JsonArray& get<JsonArray&>(JsonVariantContent c) {
  return *c.asArray;
}

template <>
inline const JsonArray& get<JsonArray const&>(JsonVariantContent c) {
  return *c.asArray;
}

template <>
inline JsonObject& get<JsonObject&>(JsonVariantContent c) {
  return *c.asObject;
}

template <>
inline const JsonObject& get<JsonObject const&>(JsonVariantContent c) {
  return *c.asObject;
}

template <>
inline signed char get<signed char>(JsonVariantContent c) {
  return static_cast<signed char>(c.asLong);
}

template <>
inline signed int get<signed int>(JsonVariantContent c) {
  return static_cast<signed int>(c.asLong);
}

template <>
inline signed long get<signed long>(JsonVariantContent c) {
  return static_cast<signed long>(c.asLong);
}

template <>
inline signed short get<signed short>(JsonVariantContent c) {
  return static_cast<signed short>(c.asLong);
}

template <>
inline unsigned char get<unsigned char>(JsonVariantContent c) {
  return static_cast<unsigned char>(c.asLong);
}

template <>
inline unsigned int get<unsigned int>(JsonVariantContent c) {
  return static_cast<unsigned int>(c.asLong);
}

template <>
inline unsigned long get<unsigned long>(JsonVariantContent c) {
  return static_cast<unsigned long>(c.asLong);
}

template <>
inline unsigned short get<unsigned short>(JsonVariantContent c) {
  return static_cast<unsigned short>(c.asLong);
}

template <typename T>
inline T invalid() {
  return T();
}
}
}

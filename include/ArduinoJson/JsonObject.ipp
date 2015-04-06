// Copyright Benoit Blanchon 2014-2015
// MIT License
//
// Arduino JSON library
// https://github.com/bblanchon/ArduinoJson

#pragma once

#include "JsonObject.hpp"
#include "JsonObjectSubscript.hpp"

namespace ArduinoJson {

inline JsonVariant JsonObject::get(key_type key) const {
  node_type *node = getNodeAt(key);
  return node ? node->content.value : JsonVariant();
}

inline JsonObjectSubscript JsonObject::operator[](key_type key) {
  return JsonObjectSubscript(*this, key);
}

inline const JsonObjectSubscript JsonObject::operator[](key_type key) const {
  return JsonObjectSubscript(*const_cast<JsonObject *>(this), key);
}

inline const JsonVariant JsonVariant::operator[](const char *key) const {
  if (_type != Internals::JSON_OBJECT) return JsonVariant();
  return _content.asObject->operator[](key);
}

inline bool JsonObject::containsKey(key_type key) const {
  return getNodeAt(key) != NULL;
}

inline void JsonObject::remove(key_type key) { removeNode(getNodeAt(key)); }

namespace Internals {
template <>
inline JsonObject const &invalid<JsonObject const &>() {
  return JsonObject::invalid();
}

template <>
inline JsonObject &invalid<JsonObject &>() {
  return JsonObject::invalid();
}
}
}

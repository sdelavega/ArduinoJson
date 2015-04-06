// Copyright Benoit Blanchon 2014-2015
// MIT License
//
// Arduino JSON library
// https://github.com/bblanchon/ArduinoJson

#pragma once

#include "JsonArray.hpp"
#include "JsonArraySubscript.hpp"

namespace ArduinoJson {

inline JsonArraySubscript JsonArray::operator[](size_t index) {
  return JsonArraySubscript(*this, index);
}

inline void JsonArray::add(double value, uint8_t decimals) {
  add(JsonVariant(value, decimals));
}

inline JsonVariant JsonArray::get(size_t index) const {
  node_type *node = getNodeAt(index);
  return node ? node->content : JsonVariant();
}

inline const JsonVariant JsonVariant::operator[](int index) const {
  if (_type != Internals::JSON_ARRAY) return JsonVariant();
  return _content.asArray->operator[](index);
}

namespace Internals {
template <>
inline JsonArray &invalid<JsonArray &>() {
  return JsonArray::invalid();
}

template <>
inline JsonArray const &invalid<JsonArray const &>() {
  return JsonArray::invalid();
}
}
}

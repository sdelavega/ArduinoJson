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

inline const JsonArraySubscript JsonArray::operator[](size_t index) const {
  return JsonArraySubscript(*const_cast<JsonArray *>(this), index);
}

inline JsonVariant JsonArray::get(size_t index) const {
  node_type *node = getNodeAt(index);
  return node ? node->content : JsonVariant();
}

inline void JsonArray::set(size_t index, const JsonVariant &value) {
  node_type *node = getNodeAt(index);
  if (node)
    node->content = value;
  else
    add(value);
}

inline const JsonArraySubscript JsonVariant::operator[](int index) const {
  return asArray()[index];
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

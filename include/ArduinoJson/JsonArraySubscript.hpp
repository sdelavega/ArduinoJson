// Copyright Benoit Blanchon 2014-2015
// MIT License
//
// Arduino JSON library
// https://github.com/bblanchon/ArduinoJson

#pragma once

#include "JsonVariantBase.hpp"

namespace ArduinoJson {
class JsonArraySubscript : public JsonVariantBase<JsonArraySubscript> {
 public:
  JsonArraySubscript(JsonArray& array, size_t index)
      : _array(array), _index(index) {}

  JsonArraySubscript& operator=(const JsonVariant& value) {
    _array.set(_index, value);
    return *this;
  }

  bool success() const { return _index < _array.size(); }

  operator JsonVariant() const { return _array.get(_index); }

  template <typename T>
  T as() const {
    return _array.get(_index).as<T>();
  }

  template <typename T>
  T is() const {
    return _array.get(_index).is<T>();
  }

 private:
  JsonArray& _array;
  const size_t _index;
};
}

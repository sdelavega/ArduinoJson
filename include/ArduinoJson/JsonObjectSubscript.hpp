// Copyright Benoit Blanchon 2014-2015
// MIT License
//
// Arduino JSON library
// https://github.com/bblanchon/ArduinoJson

#pragma once

#include "JsonVariantBase.hpp"

namespace ArduinoJson {
class JsonObjectSubscript : public JsonVariantBase<JsonObjectSubscript> {
 public:
  JsonObjectSubscript(JsonObject& object, const char* key)
      : _object(object), _key(key) {}

  JsonObjectSubscript& operator=(const JsonVariant& value) {
    _object.add(_key, value);
    return *this;
  }

  bool success() const { return _object.containsKey(_key); }

  operator JsonVariant() const { return _object.get(_key); }

  template <typename T>
  T as() const {
    return _object.get(_key).as<T>();
  }

  template <typename T>
  T is() const {
    return _object.get(_key).is<T>();
  }

 private:
  JsonObject& _object;
  const char* _key;
};
}

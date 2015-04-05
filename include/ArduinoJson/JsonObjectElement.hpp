// Copyright Benoit Blanchon 2014-2015
// MIT License
//
// Arduino JSON library
// https://github.com/bblanchon/ArduinoJson

#pragma once

#include "JsonValue.hpp"

namespace ArduinoJson {
class JsonObjectElement : public JsonValue<JsonObjectElement> {
 public:
  JsonObjectElement(JsonObject& object, const char* key)
      : _object(object), _key(key) {}

  JsonObjectElement& operator=(const JsonVariant& value) {
    _object.add(_key, value);
    return *this;
  }

  bool success() const { return _object.at(_key).success(); }

  operator JsonVariant() const { return _object.at(_key); }

  JsonArray& asArray() const { return as<JsonArray&>(); }
  operator JsonArray&() const { return asArray(); }

  JsonObject& asObject() const { return as<JsonObject&>(); }
  operator JsonObject&() const { return asObject(); }

  template <typename T>
  T as() const {
    return _object.at(_key).as<T>();
  }

  template <typename T>
  T is() const {
    return _object.at(_key).is<T>();
  }

 private:
  JsonObject& _object;
  const char* _key;
};
}

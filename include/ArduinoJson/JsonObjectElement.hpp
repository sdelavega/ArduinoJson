// Copyright Benoit Blanchon 2014-2015
// MIT License
//
// Arduino JSON library
// https://github.com/bblanchon/ArduinoJson

#pragma once

namespace ArduinoJson {
class JsonObjectElement {
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

  operator double() const { return as<double>(); }
  operator float() const { return as<float>(); }
  operator const char*() const { return as<const char*>(); }
  operator signed char() const { return as<signed char>(); }
  operator signed short() const { return as<signed short>(); }
  operator signed int() const { return as<signed int>(); }
  operator signed long() const { return as<signed long>(); }
  operator unsigned char() const { return as<unsigned char>(); }
  operator unsigned short() const { return as<unsigned short>(); }
  operator unsigned int() const { return as<unsigned int>(); }
  operator unsigned long() const { return as<unsigned long>(); }

  template <typename T>
  T as() const {
    return _object.at(_key).as<T>();
  }

 private:
  JsonObject& _object;
  const char* _key;
};

template <typename T>
inline bool operator==(const JsonObjectElement& left, T right) {
  return left.success() && left.as<T>() == right;
}

template <typename T>
inline bool operator==(T left, const JsonObjectElement& right) {
  return right.success() && left == right.as<T>();
}
}

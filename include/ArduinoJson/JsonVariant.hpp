// Copyright Benoit Blanchon 2014-2015
// MIT License
//
// Arduino JSON library
// https://github.com/bblanchon/ArduinoJson

#pragma once

#include <stddef.h>
#include <stdint.h>  // for uint8_t

#include "Internals/JsonPrintable.hpp"
#include "Internals/JsonVariantContent.hpp"
#include "Internals/JsonVariantType.hpp"

namespace ArduinoJson {

// Forward declarations.
class JsonArray;
class JsonObject;

// A variant that can be a any value serializable to a JSON value.
//
// It can be set to:
// - a boolean
// - a char, short, int or a long (signed or unsigned)
// - a string (const char*)
// - a reference to a JsonArray or JsonObject
class JsonVariant : public Internals::JsonPrintable<JsonVariant> {
 public:
  // Creates an uninitialized JsonVariant
  JsonVariant() : _type(Internals::JSON_UNDEFINED) {}

  // Create a JsonVariant containing a boolean value.
  // It will be serialized as "true" or "false" in JSON.
  JsonVariant(bool value) : _type(Internals::JSON_BOOLEAN), _content(value) {}

  // Create a JsonVariant containing a floating point value.
  // The second argument specifies the number of decimal digits to write in
  // the JSON string.
  JsonVariant(double value, uint8_t decimals = 2)
      : _type(static_cast<Internals::JsonVariantType>(
            Internals::JSON_DOUBLE_0_DECIMALS + decimals)),
        _content(value) {}

  // Create a JsonVariant containing an integer value.
  JsonVariant(signed char value)
      : _type(Internals::JSON_LONG), _content(value) {}

  JsonVariant(signed long value)
      : _type(Internals::JSON_LONG), _content(value) {}

  JsonVariant(signed int value)
      : _type(Internals::JSON_LONG), _content(value) {}

  JsonVariant(signed short value)
      : _type(Internals::JSON_LONG), _content(value) {}

  JsonVariant(unsigned char value)
      : _type(Internals::JSON_LONG), _content(value) {}

  JsonVariant(unsigned long value)
      : _type(Internals::JSON_LONG), _content(value) {}

  JsonVariant(unsigned int value)
      : _type(Internals::JSON_LONG), _content(value) {}

  JsonVariant(unsigned short value)
      : _type(Internals::JSON_LONG), _content(value) {}

  // Create a JsonVariant containing a string.
  JsonVariant(const char *value)
      : _type(Internals::JSON_STRING), _content(value) {}

  // Create a JsonVariant containing a reference to an array.
  JsonVariant(JsonArray &array)
      : _type(Internals::JSON_ARRAY), _content(&array) {}

  // Create a JsonVariant containing a reference to an object.
  JsonVariant(JsonObject &object)
      : _type(Internals::JSON_OBJECT), _content(&object) {}

  // Tells weither the variant is valid.
  bool success() const {
    return _type != Internals::JSON_INVALID &&
           _type != Internals::JSON_UNDEFINED;
  }

  // Create a JsonVariant containing the specified value.
  JsonVariant &operator=(const JsonVariant &other) {
    if (_type != Internals::JSON_INVALID) {
      _type = other._type;
      _content = other._content;
    }
    return *this;
  }

  // Gets the variant as a boolean value.
  // Returns false if the variant is not a boolean value.
  operator bool() const;

  // Gets the variant as a floating-point value.
  // Returns 0.0 if the variant is not a floating-point value
  operator double() const;
  operator float() const { return static_cast<float>(as<double>()); }

  // Gets the variant as an integer value.
  // Returns 0 if the variant is not an integer value.
  operator signed long() const;
  operator signed char() const { return cast_long_to<signed char>(); }
  operator signed int() const { return cast_long_to<signed int>(); }
  operator signed short() const { return cast_long_to<signed short>(); }
  operator unsigned char() const { return cast_long_to<unsigned char>(); }
  operator unsigned int() const { return cast_long_to<unsigned int>(); }
  operator unsigned long() const { return cast_long_to<unsigned long>(); }
  operator unsigned short() const { return cast_long_to<unsigned short>(); }

  // Gets the variant as a string.
  // Returns NULL if variant is not a string.
  operator const char *() const;
  const char *asString() const { return as<const char *>(); }

  // Gets the variant as an array.
  // Returns a reference to the JsonArray or JsonArray::invalid() if the variant
  // is not an array.
  operator JsonArray &() const;
  JsonArray &asArray() const { return as<JsonArray &>(); }

  // Gets the variant as an object.
  // Returns a reference to the JsonObject or JsonObject::invalid() if the
  // variant is not an object.
  operator JsonObject &() const;
  JsonObject &asObject() const { return as<JsonObject &>(); }

  // Get the variant as the specified type.
  // See cast operators for details.
  template <typename T>
  T as() const {
    return static_cast<T>(*this);
  }

  // Tells weither the variant has the specified type.
  // Returns true if the variant has type type T, false otherwise.
  template <typename T>
  bool is() const {
    return false;
  }

  // Returns an invalid variant.
  // This is meant to replace a NULL pointer.
  static JsonVariant &invalid() { return _invalid; }

  // Serialize the variant to a JsonWriter
  void writeTo(Internals::JsonWriter &writer) const;

  // Mimics an array or an object.
  // Returns the size of the array or object if the variant has that type.
  // Returns 0 if the variant is neither an array nor an object
  size_t size() const;

  // Mimics an array.
  // Returns the element at specified index if the variant is an array.
  // Returns JsonVariant::invalid() if the variant is not an array.
  JsonVariant &operator[](int index);

  // Mimics an object.
  // Returns the value associated with the specified key if the variant is an
  // object.
  // Return JsonVariant::invalid() if the variant is not an object.
  JsonVariant &operator[](const char *key);

 private:
  // Special constructor used only to create _invalid.
  explicit JsonVariant(Internals::JsonVariantType type) : _type(type) {}

  // Helper for interger cast operators
  template <typename T>
  T cast_long_to() const {
    return static_cast<T>(as<long>());
  }

  // The current type of the variant
  Internals::JsonVariantType _type;

  // The various alternatives for the value of the variant.
  Internals::JsonVariantContent _content;

  // The instance returned by JsonVariant::invalid()
  static JsonVariant _invalid;
};

template <>
inline bool JsonVariant::is<long>() const {
  return _type == Internals::JSON_LONG;
}

template <>
inline bool JsonVariant::is<double>() const {
  return _type >= Internals::JSON_DOUBLE_0_DECIMALS;
}

template <>
inline bool JsonVariant::is<bool>() const {
  return _type == Internals::JSON_BOOLEAN;
}

template <>
inline bool JsonVariant::is<const char *>() const {
  return _type == Internals::JSON_STRING;
}

template <>
inline bool JsonVariant::is<JsonArray &>() const {
  return _type == Internals::JSON_ARRAY;
}

template <>
inline bool JsonVariant::is<const JsonArray &>() const {
  return _type == Internals::JSON_ARRAY;
}

template <>
inline bool JsonVariant::is<JsonObject &>() const {
  return _type == Internals::JSON_OBJECT;
}

template <>
inline bool JsonVariant::is<const JsonObject &>() const {
  return _type == Internals::JSON_OBJECT;
}

template <typename T>
inline bool operator==(const JsonVariant &left, T right) {
  return left.as<T>() == right;
}

template <typename T>
inline bool operator==(T left, const JsonVariant &right) {
  return left == right.as<T>();
}

template <typename T>
inline bool operator!=(const JsonVariant &left, T right) {
  return left.as<T>() != right;
}

template <typename T>
inline bool operator!=(T left, const JsonVariant &right) {
  return left != right.as<T>();
}

template <typename T>
inline bool operator<=(const JsonVariant &left, T right) {
  return left.as<T>() <= right;
}

template <typename T>
inline bool operator<=(T left, const JsonVariant &right) {
  return left <= right.as<T>();
}

template <typename T>
inline bool operator>=(const JsonVariant &left, T right) {
  return left.as<T>() >= right;
}

template <typename T>
inline bool operator>=(T left, const JsonVariant &right) {
  return left >= right.as<T>();
}

template <typename T>
inline bool operator<(const JsonVariant &left, T right) {
  return left.as<T>() < right;
}

template <typename T>
inline bool operator<(T left, const JsonVariant &right) {
  return left < right.as<T>();
}

template <typename T>
inline bool operator>(const JsonVariant &left, T right) {
  return left.as<T>() > right;
}

template <typename T>
inline bool operator>(T left, const JsonVariant &right) {
  return left > right.as<T>();
}
}

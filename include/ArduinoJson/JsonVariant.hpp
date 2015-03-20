// Copyright Benoit Blanchon 2014-2015
// MIT License
//
// Arduino JSON library
// https://github.com/bblanchon/ArduinoJson

#pragma once

#include <stddef.h>
#include <stdint.h>  // for uint8_t

#include "Arduino/String.hpp"
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

  // Initializes a JsonVariant with the specified value.
  explicit JsonVariant(bool x) { set(x); }
  explicit JsonVariant(char const *x) { set(x); }
  explicit JsonVariant(char signed x) { set(x); }
  explicit JsonVariant(char unsigned x) { set(x); }
  explicit JsonVariant(double x, uint8_t decimals = 2) { set(x, decimals); }
  explicit JsonVariant(int signed x) { set(x); }
  explicit JsonVariant(int unsigned x) { set(x); }
  explicit JsonVariant(JsonArray &x) { set(x); }
  explicit JsonVariant(JsonObject &x) { set(x); }
  explicit JsonVariant(long signed x) { set(x); }
  explicit JsonVariant(long unsigned x) { set(x); }
  explicit JsonVariant(short signed x) { set(x); }
  explicit JsonVariant(short unsigned x) { set(x); }
  explicit JsonVariant(String const &x) { set(x); }

  // Set the variant to the specified value.
  void set(bool x);
  void set(char const *x);
  void set(char signed x) { assignLong(x); }
  void set(char unsigned x) { assignLong(x); }
  void set(double x, uint8_t decimals = 2);
  void set(int signed x) { assignLong(x); }
  void set(int unsigned x) { assignLong(x); }
  void set(JsonArray &x);
  void set(JsonObject &x);
  void set(long signed x);
  void set(long unsigned x) { assignLong(x); }
  void set(short signed x) { assignLong(x); }
  void set(short unsigned x) { assignLong(x); }
  void set(String const &x) { set(x.c_str()); }

  // Set the variant to the specified value.
  JsonVariant &operator=(bool x) { return assignValue<bool>(x); }
  JsonVariant &operator=(char const *x) { return assignValue<char const *>(x); }
  JsonVariant &operator=(char signed x) { return assignValue<long>(x); }
  JsonVariant &operator=(char unsigned x) { return assignValue<long>(x); }
  JsonVariant &operator=(double x) { return assignValue<double>(x); }
  JsonVariant &operator=(int signed x) { return assignValue<long>(x); }
  JsonVariant &operator=(int unsigned x) { return assignValue<long>(x); }
  JsonVariant &operator=(JsonArray &x) { return assignRef(x); }
  JsonVariant &operator=(JsonObject &x) { return assignRef(x); }
  JsonVariant &operator=(long signed x) { return assignValue<long>(x); }
  JsonVariant &operator=(long unsigned x) { return assignValue<long>(x); }
  JsonVariant &operator=(short signed x) { return assignValue<long>(x); }
  JsonVariant &operator=(short unsigned x) { return assignValue<long>(x); }
  JsonVariant &operator=(String const &x) { return assignValue(x.c_str()); }

  // Gets the variant as the specified type
  operator bool() const;

  // Gets the variant as a floating-point value.
  // Returns 0.0 if the variant is not a floating-point value
  operator double() const;
  operator float() const { return get<float, double>(); }

  // Gets the variant as an integer value.
  // Returns 0 if the variant is not an integer value.
  operator long signed() const;
  operator signed char() const { return get<char signed, long signed>(); }
  operator signed int() const { return get<int signed, long signed>(); }
  operator signed short() const { return get<short signed, long signed>(); }
  operator unsigned char() const { return get<char unsigned, long signed>(); }
  operator unsigned int() const { return get<int unsigned, long signed>(); }
  operator unsigned long() const { return get<long unsigned, long signed>(); }
  operator unsigned short() const { return get<short unsigned, long signed>(); }

  // Gets the variant as a string.
  // Returns NULL if variant is not a string.
  operator char const *() const;
  char const *asString() const { return as<char const *>(); }

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

  // Mimics an array.
  // Returns the element at specified index if the variant is an array.
  // Returns JsonVariant::invalid() if the variant is not an array.
  JsonVariant &operator[](int index);

  // Mimics an object.
  // Returns the value associated with the specified key if the variant is an
  // object.
  // Return JsonVariant::invalid() if the variant is not an object.
  JsonVariant &operator[](const char *key);

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

  // Mimics an array or an object.
  // Returns the size of the array or object if the variant has that type.
  // Returns 0 if the variant is neither an array nor an object
  size_t size() const;

  // Tells weither the variant is valid.
  bool success() const {
    return _type != Internals::JSON_INVALID &&
           _type != Internals::JSON_UNDEFINED;
  }

  // Serialize the variant to a JsonWriter
  void writeTo(Internals::JsonWriter &writer) const;

  // Returns an invalid variant.
  // This is meant to replace a NULL pointer.
  static JsonVariant &invalid() { return _invalid; }

 private:
  // Special constructor used only to create _invalid.
  explicit JsonVariant(Internals::JsonVariantType type) : _type(type) {}

  // Helper function
  template <typename T, typename U>
  T get() const {
    return static_cast<T>(as<U>());
  }

  // Helper function
  template <typename T>
  JsonVariant &assignLong(T value) {
    set(static_cast<long signed>(value));
    return *this;
  }

  // Helper function
  template <typename T>
  JsonVariant &assignValue(T value) {
    set(value);
    return *this;
  }

  // Helper function
  template <typename T>
  JsonVariant &assignRef(T &value) {
    set(value);
    return *this;
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

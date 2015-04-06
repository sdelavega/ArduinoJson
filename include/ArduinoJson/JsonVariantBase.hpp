// Copyright Benoit Blanchon 2014-2015
// MIT License
//
// Arduino JSON library
// https://github.com/bblanchon/ArduinoJson

#pragma once

namespace ArduinoJson {

template <typename TImpl>
class JsonVariantBase {
 public:
  // Gets the variant as a boolean value.
  // Returns false if the variant is not a boolean value.
  operator bool() const { return as<bool>(); }

  // Gets the variant as a floating-point value.
  // Returns 0.0 if the variant is not a floating-point value
  operator double() const { return as<double>(); }
  operator float() const { return as<float>(); }

  // Gets the variant as an integer value.
  // Returns 0 if the variant is not an integer value.
  operator signed long() const { return as<signed long>(); }
  operator signed char() const { return as<signed char>(); }
  operator signed int() const { return as<signed int>(); }
  operator signed short() const { return as<signed short>(); }
  operator unsigned char() const { return as<unsigned char>(); }
  operator unsigned int() const { return as<unsigned int>(); }
  operator unsigned long() const { return as<unsigned long>(); }
  operator unsigned short() const { return as<unsigned short>(); }

  // Gets the variant as a string.
  // Returns NULL if variant is not a string.
  operator const char *() const { return as<const char *>(); }
  const char *asString() const { return as<const char *>(); }

  // Gets the variant as an array.
  // Returns a reference to the JsonArray or JsonArray::invalid() if the
  // variant
  // is not an array.
  operator JsonArray &() const { return as<JsonArray &>(); }
  JsonArray &asArray() const { return as<JsonArray &>(); }

  // Gets the variant as an object.
  // Returns a reference to the JsonObject or JsonObject::invalid() if the
  // variant is not an object.
  operator JsonObject &() const { return as<JsonObject &>(); }
  JsonObject &asObject() const { return as<JsonObject &>(); }

  template <typename T>
  const T as() const {
    return impl()->template as<T>();
  }

 private:
  const TImpl *impl() const { return static_cast<const TImpl *>(this); }
};

template <typename TImpl, typename TComparand>
inline bool operator==(const JsonVariantBase<TImpl> &left, TComparand right) {
  return left.template as<TComparand>() == right;
}

template <typename TImpl, typename TComparand>
inline bool operator==(TComparand left, const JsonVariantBase<TImpl> &right) {
  return left == right.template as<TComparand>();
}

template <typename TImpl, typename TComparand>
inline bool operator!=(const JsonVariantBase<TImpl> &left, TComparand right) {
  return left.template as<TComparand>() != right;
}

template <typename TImpl, typename TComparand>
inline bool operator!=(TComparand left, const JsonVariantBase<TImpl> &right) {
  return left != right.template as<TComparand>();
}

template <typename TImpl, typename TComparand>
inline bool operator<=(const JsonVariantBase<TImpl> &left, TComparand right) {
  return left.template as<TComparand>() <= right;
}

template <typename TImpl, typename TComparand>
inline bool operator<=(TComparand left, const JsonVariantBase<TImpl> &right) {
  return left <= right.template as<TComparand>();
}

template <typename TImpl, typename TComparand>
inline bool operator>=(const JsonVariantBase<TImpl> &left, TComparand right) {
  return left.template as<TComparand>() >= right;
}

template <typename TImpl, typename TComparand>
inline bool operator>=(TComparand left, const JsonVariantBase<TImpl> &right) {
  return left >= right.template as<TComparand>();
}

template <typename TImpl, typename TComparand>
inline bool operator<(const JsonVariantBase<TImpl> &left, TComparand right) {
  return left.template as<TComparand>() < right;
}

template <typename TImpl, typename TComparand>
inline bool operator<(TComparand left, const JsonVariantBase<TImpl> &right) {
  return left < right.template as<TComparand>();
}

template <typename TImpl, typename TComparand>
inline bool operator>(const JsonVariantBase<TImpl> &left, TComparand right) {
  return left.template as<TComparand>() > right;
}

template <typename TImpl, typename TComparand>
inline bool operator>(TComparand left, const JsonVariantBase<TImpl> &right) {
  return left > right.template as<TComparand>();
}
}

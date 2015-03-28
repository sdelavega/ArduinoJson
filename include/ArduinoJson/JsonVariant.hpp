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
  JsonVariant(bool value);

  // Create a JsonVariant containing a floating point value.
  // The second argument specifies the number of decimal digits to write in
  // the JSON string.
  JsonVariant(float value, uint8_t decimals = 2);
  JsonVariant(double value, uint8_t decimals = 2);

  // Create a JsonVariant containing an integer value.
  JsonVariant(signed char value);
  JsonVariant(signed long value);
  JsonVariant(signed int value);
  JsonVariant(signed short value);
  JsonVariant(unsigned char value);
  JsonVariant(unsigned long value);
  JsonVariant(unsigned int value);
  JsonVariant(unsigned short value);

  // Create a JsonVariant containing a string.
  JsonVariant(const char *value);

  // Create a JsonVariant containing a reference to an array.
  JsonVariant(JsonArray &array);

  // Create a JsonVariant containing a reference to an object.
  JsonVariant(JsonObject &object);

  // Gets the variant as a boolean value.
  // Returns false if the variant is not a boolean value.
  operator bool() const;

  // Gets the variant as a floating-point value.
  // Returns 0.0 if the variant is not a floating-point value
  operator double() const;
  operator float() const;

  // Gets the variant as an integer value.
  // Returns 0 if the variant is not an integer value.
  operator signed long() const;
  operator signed char() const;
  operator signed int() const;
  operator signed short() const;
  operator unsigned char() const;
  operator unsigned int() const;
  operator unsigned long() const;
  operator unsigned short() const;

  // Gets the variant as a string.
  // Returns NULL if variant is not a string.
  operator const char *() const { return asString(); }
  const char *asString() const;

  // Gets the variant as an array.
  // Returns a reference to the JsonArray or JsonArray::invalid() if the
  // variant
  // is not an array.
  operator JsonArray &() const { return asArray(); }
  JsonArray &asArray() const;

  // Gets the variant as an object.
  // Returns a reference to the JsonObject or JsonObject::invalid() if the
  // variant is not an object.
  operator JsonObject &() const { return asObject(); }
  JsonObject &asObject() const;

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

  // Create a JsonVariant containing the specified value.
  JsonVariant &operator=(const JsonVariant &other) {
    if (_type != Internals::JSON_INVALID) {
      _type = other._type;
      _content = other._content;
    }
    return *this;
  }

  // Tells weither the variant is valid.
  bool success() const {
    return _type != Internals::JSON_INVALID &&
           _type != Internals::JSON_UNDEFINED;
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
  // Returns the value associated with the specified key if the variant is
  // an
  // object.
  // Return JsonVariant::invalid() if the variant is not an object.
  JsonVariant &operator[](const char *key);

 private:
  // Special constructor used only to create _invalid.
  explicit JsonVariant(Internals::JsonVariantType type) : _type(type) {}

  // The current type of the variant
  Internals::JsonVariantType _type;

  // The various alternatives for the value of the variant.
  Internals::JsonVariantContent _content;

  // The instance returned by JsonVariant::invalid()
  static JsonVariant _invalid;
};
}

#include "JsonVariant.Array.hpp"
#include "JsonVariant.Bool.hpp"
#include "JsonVariant.CharPtr.hpp"
#include "JsonVariant.Double.hpp"
#include "JsonVariant.Float.hpp"
#include "JsonVariant.Object.hpp"
#include "JsonVariant.SignedChar.hpp"
#include "JsonVariant.SignedInt.hpp"
#include "JsonVariant.SignedLong.hpp"
#include "JsonVariant.SignedShort.hpp"
#include "JsonVariant.UnsignedChar.hpp"
#include "JsonVariant.UnsignedInt.hpp"
#include "JsonVariant.UnsignedLong.hpp"
#include "JsonVariant.UnsignedShort.hpp"

#include "JsonVariant.Comparisons.hpp"

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
#include "JsonVariantBase.hpp"

namespace ArduinoJson {

// Forward declarations.
class JsonArray;
class JsonArraySubscript;
class JsonObject;
class JsonObjectSubscript;

// A variant that can be a any value serializable to a JSON value.
//
// It can be set to:
// - a boolean
// - a char, short, int or a long (signed or unsigned)
// - a string (const char*)
// - a reference to a JsonArray or JsonObject
class JsonVariant : public Internals::JsonPrintable<JsonVariant>,
                    public JsonVariantBase<JsonVariant> {
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

  // Get the variant as the specified type.
  // See cast operators for details.
  template <typename T>
  T as() const;

  // Tells weither the variant has the specified type.
  // Returns true if the variant has type type T, false otherwise.
  template <typename T>
  bool is() const;

  // Copy the value of the specified variant
  JsonVariant &operator=(const JsonVariant &other);

  // Tells weither the variant is valid.
  bool success() const { return _type != Internals::JSON_UNDEFINED; }

  // Serialize the variant to a JsonWriter
  void writeTo(Internals::JsonWriter &writer) const;

  // Mimics an array or an object.
  // Returns the size of the array or object if the variant has that type.
  // Returns 0 if the variant is neither an array nor an object
  size_t size() const;

  // Mimics an array.
  // Returns the element at specified index if the variant is an array.
  // Returns JsonVariant::invalid() if the variant is not an array.
  const JsonArraySubscript operator[](int index) const;

  // Mimics an object.
  // Returns the value associated with the specified key if the variant is
  // an object.
  // Return JsonVariant::invalid() if the variant is not an object.
  const JsonObjectSubscript operator[](const char *key) const;

 private:
  // The current type of the variant
  Internals::JsonVariantType _type;

  // The various alternatives for the value of the variant.
  Internals::JsonVariantContent _content;
};

inline JsonVariant float_with_n_digits(float value, uint8_t digits) {
  return JsonVariant(value, digits);
}

inline JsonVariant double_with_n_digits(double value, uint8_t digits) {
  return JsonVariant(value, digits);
}
}

// Include inline implementations
#include "JsonVariant.ipp"

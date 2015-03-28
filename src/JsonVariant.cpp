// Copyright Benoit Blanchon 2014-2015
// MIT License
//
// Arduino JSON library
// https://github.com/bblanchon/ArduinoJson

#include "../include/ArduinoJson/JsonVariant.hpp"

#include "../include/ArduinoJson/JsonArray.hpp"
#include "../include/ArduinoJson/JsonObject.hpp"

using namespace ArduinoJson;
using namespace ArduinoJson::Internals;

JsonVariant JsonVariant::_invalid(JSON_INVALID);

JsonArray &JsonVariant::asArray() const {
  return _type == Internals::JSON_ARRAY ? *_content.asArray
                                        : JsonArray::invalid();
}

JsonObject &JsonVariant::asObject() const {
  return _type == Internals::JSON_OBJECT ? *_content.asObject
                                         : JsonObject::invalid();
}

size_t JsonVariant::size() const {
  if (_type == JSON_ARRAY) return _content.asArray->size();
  if (_type == JSON_OBJECT) return _content.asObject->size();
  return 0;
}

JsonVariant &JsonVariant::operator[](int index) {
  if (_type != JSON_ARRAY) return JsonVariant::invalid();
  return _content.asArray->operator[](index);
}

JsonVariant &JsonVariant::operator[](const char *key) {
  if (_type != JSON_OBJECT) return JsonVariant::invalid();
  return _content.asObject->operator[](key);
}

void JsonVariant::writeTo(JsonWriter &writer) const {
  if (is<const JsonArray &>())
    as<const JsonArray &>().writeTo(writer);
  else if (is<const JsonObject &>())
    as<const JsonObject &>().writeTo(writer);
  else if (is<const char *>())
    writer.writeString(as<const char *>());
  else if (is<long>())
    writer.writeLong(as<long>());
  else if (is<bool>())
    writer.writeBoolean(as<bool>());
  else if (is<double>()) {
    uint8_t decimals = static_cast<uint8_t>(_type - JSON_DOUBLE_0_DECIMALS);
    writer.writeDouble(as<double>(), decimals);
  }
}

// Copyright Benoit Blanchon 2014-2015
// MIT License
//
// Arduino JSON library
// https://github.com/bblanchon/ArduinoJson

#include "../include/ArduinoJson/JsonBuffer.hpp"

#include "../include/ArduinoJson/Internals/JsonParser.hpp"
#include "../include/ArduinoJson/JsonArray.hpp"
#include "../include/ArduinoJson/JsonObject.hpp"

using namespace ArduinoJson;
using namespace ArduinoJson::Internals;

template <typename T>
T &JsonBuffer::create() {
  T *ptr = new (this) T(this);
  return ptr ? *ptr : T::invalid();
}

JsonArray &JsonBuffer::parseArray(char *json, uint8_t nestingLimit) {
  JsonParser parser(this, json, nestingLimit);
  return parser.parseArray();
}

JsonObject &JsonBuffer::parseObject(char *json, uint8_t nestingLimit) {
  JsonParser parser(this, json, nestingLimit);
  return parser.parseObject();
}

template JsonArray &JsonBuffer::create<JsonArray>();
template JsonObject &JsonBuffer::create<JsonObject>();
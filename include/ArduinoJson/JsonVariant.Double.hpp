// Copyright Benoit Blanchon 2014-2015
// MIT License
//
// Arduino JSON library
// https://github.com/bblanchon/ArduinoJson

#pragma once

namespace ArduinoJson {

inline JsonVariant::JsonVariant(double value, uint8_t decimals) {
  _type = static_cast<Internals::JsonVariantType>(
      Internals::JSON_DOUBLE_0_DECIMALS + decimals);
  _content.asDouble = value;
}
}

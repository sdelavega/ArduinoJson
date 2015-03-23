// Copyright Benoit Blanchon 2014-2015
// MIT License
//
// Arduino JSON library
// https://github.com/bblanchon/ArduinoJson

#pragma once

#include "Arduino/String.hpp"

namespace ArduinoJson {

class JsonString {
 public:
  JsonString(const char* data) : _data(data) {}

  JsonString(const String& s) : _data(const_cast<char*>(s.c_str())) {}

  operator const char*() const { return _data; }

 private:
  const char* _data;
};
}

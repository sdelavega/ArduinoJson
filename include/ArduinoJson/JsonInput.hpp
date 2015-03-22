// Copyright Benoit Blanchon 2014-2015
// MIT License
//
// Arduino JSON library
// https://github.com/bblanchon/ArduinoJson

#pragma once

#include "Arduino/String.hpp"

namespace ArduinoJson {

class JsonInput {
 public:
  JsonInput(char* data) : _data(data) {}

  JsonInput(String& s) : _data(const_cast<char*>(s.c_str())) {}

  operator char*() { return _data; }

 private:
  char* _data;
};
}

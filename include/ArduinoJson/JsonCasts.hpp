// Copyright Benoit Blanchon 2014-2015
// MIT License
//
// Arduino JSON library
// https://github.com/bblanchon/ArduinoJson

#pragma once

#include "Arduino/String.hpp"

namespace ArduinoJson {

inline const char* to_cstr(const String& s) { return s.c_str(); }
inline char* to_str(String& s) { return const_cast<char*>(s.c_str()); }

inline const char* to_value(const String& s) { return s.c_str(); }
inline long to_value(signed long value) { return static_cast<long>(value); }
inline long to_value(signed char value) { return static_cast<long>(value); }
inline long to_value(signed int value) { return static_cast<long>(value); }
inline long to_value(signed short value) { return static_cast<long>(value); }
inline long to_value(unsigned char value) { return static_cast<long>(value); }
inline long to_value(unsigned int value) { return static_cast<long>(value); }
inline long to_value(unsigned long value) { return static_cast<long>(value); }
inline long to_value(unsigned short value) { return static_cast<long>(value); }
}

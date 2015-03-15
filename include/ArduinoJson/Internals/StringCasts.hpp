// Copyright Benoit Blanchon 2014-2015
// MIT License
//
// Arduino JSON library
// https://github.com/bblanchon/ArduinoJson

#pragma once

#include "../Arduino/String.hpp"

namespace ArduinoJson {
namespace Internals {

inline const char* to_cstr(char* s) { return s; }
inline const char* to_cstr(const char* s) { return s; }
inline const char* to_cstr(const String& s) { return s.c_str(); }

inline char* to_str(char* s) { return s; }
inline char* to_str(const String& s) { return const_cast<char*>(s.c_str()); }
}
}

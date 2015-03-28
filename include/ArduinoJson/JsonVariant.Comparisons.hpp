// Copyright Benoit Blanchon 2014-2015
// MIT License
//
// Arduino JSON library
// https://github.com/bblanchon/ArduinoJson

#pragma once

namespace ArduinoJson {

template <typename T>
inline bool operator==(const JsonVariant &left, T right) {
  return left.as<T>() == right;
}

template <typename T>
inline bool operator==(T left, const JsonVariant &right) {
  return left == right.as<T>();
}

template <typename T>
inline bool operator!=(const JsonVariant &left, T right) {
  return left.as<T>() != right;
}

template <typename T>
inline bool operator!=(T left, const JsonVariant &right) {
  return left != right.as<T>();
}

template <typename T>
inline bool operator<=(const JsonVariant &left, T right) {
  return left.as<T>() <= right;
}

template <typename T>
inline bool operator<=(T left, const JsonVariant &right) {
  return left <= right.as<T>();
}

template <typename T>
inline bool operator>=(const JsonVariant &left, T right) {
  return left.as<T>() >= right;
}

template <typename T>
inline bool operator>=(T left, const JsonVariant &right) {
  return left >= right.as<T>();
}

template <typename T>
inline bool operator<(const JsonVariant &left, T right) {
  return left.as<T>() < right;
}

template <typename T>
inline bool operator<(T left, const JsonVariant &right) {
  return left < right.as<T>();
}

template <typename T>
inline bool operator>(const JsonVariant &left, T right) {
  return left.as<T>() > right;
}

template <typename T>
inline bool operator>(T left, const JsonVariant &right) {
  return left > right.as<T>();
}
}

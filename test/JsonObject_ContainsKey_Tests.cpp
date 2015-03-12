// Copyright Benoit Blanchon 2014-2015
// MIT License
//
// Arduino JSON library
// https://github.com/bblanchon/ArduinoJson

#include <gtest/gtest.h>
#include <ArduinoJson.h>

class JsonObject_ContainsKey_Tests : public ::testing::Test {
 public:
  JsonObject_ContainsKey_Tests() : _object(_jsonBuffer.createObject()) {
    _object.add("defined", 42);
    _object.add("undefined");
  }

 protected:
  template <typename T>
  void mustReturnTrue(T key) {
    ASSERT_TRUE(_object.containsKey(key));
  }

  template <typename T>
  void mustReturnFalse(T key) {
    ASSERT_FALSE(_object.containsKey(key));
  }

 private:
  DynamicJsonBuffer _jsonBuffer;
  JsonObject& _object;
};

TEST_F(JsonObject_ContainsKey_Tests,
       CalledWithCharPtr_ReturnsFalseForNonExistingKey) {
  mustReturnFalse("missing");
}

TEST_F(JsonObject_ContainsKey_Tests,
       CalledWithString_ReturnsFalseForNonExistingKey) {
  String key("missing");
  mustReturnFalse(key);
}

TEST_F(JsonObject_ContainsKey_Tests,
       CalledWithCharPtr_ReturnsTrueForDefinedValue) {
  mustReturnTrue("defined");
}

TEST_F(JsonObject_ContainsKey_Tests,
       CalledWithString_ReturnsTrueForDefinedValue) {
  String key("defined");
  mustReturnTrue(key);
}

TEST_F(JsonObject_ContainsKey_Tests,
       CalledWithCharPtr_ReturnsFalseForUndefinedValue) {
  mustReturnFalse("undefined");
}

TEST_F(JsonObject_ContainsKey_Tests,
       CalledWithString_ReturnsFalseForUndefinedValue) {
  String key("undefined");
  mustReturnFalse(key);
}

// Copyright Benoit Blanchon 2014-2015
// MIT License
//
// Arduino JSON library
// https://github.com/bblanchon/ArduinoJson

#include <gtest/gtest.h>
#include <ArduinoJson.h>

class JsonObject_ContainsKey_Tests : public ::testing::Test {
 public:
  JsonObject_ContainsKey_Tests() : _object(_jsonBuffer.createObject()) {}

 protected:
  DynamicJsonBuffer _jsonBuffer;
  JsonObject& _object;
};

TEST_F(JsonObject_ContainsKey_Tests, ContainsKeyReturnFalseForNonExistingKey) {
  EXPECT_FALSE(_object.containsKey("hello"));
}

TEST_F(JsonObject_ContainsKey_Tests, ContainsKeyReturnTrueForDefinedValue) {
  _object.add("hello", 42);
  EXPECT_TRUE(_object.containsKey("hello"));
}

TEST_F(JsonObject_ContainsKey_Tests, ContainsKeyReturnFalseForUndefinedValue) {
  _object.add("hello");
  EXPECT_FALSE(_object.containsKey("hello"));
}

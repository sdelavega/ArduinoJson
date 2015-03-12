// Copyright Benoit Blanchon 2014-2015
// MIT License
//
// Arduino JSON library
// https://github.com/bblanchon/ArduinoJson

#include <gtest/gtest.h>
#include <ArduinoJson.h>

class JsonObject_Remove_Tests : public ::testing::Test {
 public:
  JsonObject_Remove_Tests() : _object(_jsonBuffer.createObject()) {
    _object.add("defined", 0);
    _object.add("undefined");
    _object.add("hidden", 1);
  }

 protected:
  template <typename T>
  void testWith(T key) {
    _object.remove(key);
    ASSERT_FALSE(_object.containsKey(key));
    ASSERT_TRUE(_object.containsKey("hidden"));
  }

 private:
  DynamicJsonBuffer _jsonBuffer;
  JsonObject& _object;
};

TEST_F(JsonObject_Remove_Tests, CalledWithCharPtr_OnNonExistingKey) {
  testWith("missing");
}

TEST_F(JsonObject_Remove_Tests, CalledWithString_OnNonExistingKey) {
  testWith(String("missing"));
}

TEST_F(JsonObject_Remove_Tests, CalledWithCharPtr_ReturnsTrueForDefinedValue) {
  testWith("defined");
}

TEST_F(JsonObject_Remove_Tests, CalledWithString_ReturnsTrueForDefinedValue) {
  testWith(String("defined"));
}

TEST_F(JsonObject_Remove_Tests, CalledWithCharPtr_OnUndefinedValue) {
  testWith("undefined");
}

TEST_F(JsonObject_Remove_Tests, CalledWithString_OnUndefinedValue) {
  testWith(String("undefined"));
}

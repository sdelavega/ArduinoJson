// Copyright Benoit Blanchon 2014-2015
// MIT License
//
// Arduino JSON library
// https://github.com/bblanchon/ArduinoJson

#include <gtest/gtest.h>
#include <ArduinoJson.h>

class JsonVariant_Subscript_Tests : public ::testing::Test {
 protected:
  void sizeMustBe(int expected) { EXPECT_EQ(expected, _variant.size()); }

  template <typename T>
  void subscriptMustFail(T key) {
    EXPECT_FALSE(_variant[key].success());
  }

  template <typename T>
  void subscriptMustMatch(T key, char const *expected) {
    EXPECT_STREQ(expected, _variant[key].asString());
  }

 protected:
  DynamicJsonBuffer _jsonBuffer;
  JsonVariant _variant;
};

TEST_F(JsonVariant_Subscript_Tests, Array) {
  JsonArray &array = _jsonBuffer.createArray();
  array.add("element at index 0");
  array.add("element at index 1");

  _variant = array;

  sizeMustBe(2);
  subscriptMustMatch(0, "element at index 0");
  subscriptMustMatch(1, "element at index 1");
  subscriptMustFail(-1);
  subscriptMustFail(3);
  subscriptMustFail("0");
  subscriptMustFail(String("0"));
}

TEST_F(JsonVariant_Subscript_Tests, Object) {
  JsonObject &object = _jsonBuffer.createObject();
  object["a"] = "element at key \"a\"";
  object["b"] = "element at key \"b\"";

  _variant = object;

  sizeMustBe(2);
  subscriptMustMatch("a", "element at key \"a\"");
  subscriptMustMatch("b", "element at key \"b\"");
  subscriptMustFail("c");
  subscriptMustFail(String("c"));
  subscriptMustFail(0);
}

TEST_F(JsonVariant_Subscript_Tests, Undefined) {
  _variant = JsonVariant();
  sizeMustBe(0);
  subscriptMustFail("0");
  subscriptMustFail(String("0"));
  subscriptMustFail(0);
}

TEST_F(JsonVariant_Subscript_Tests, Invalid) {
  _variant = JsonVariant::invalid();
  sizeMustBe(0);
  subscriptMustFail("0");
  subscriptMustFail(String("0"));
  subscriptMustFail(0);
}

TEST_F(JsonVariant_Subscript_Tests, String) {
  _variant = "hello world";
  sizeMustBe(0);
  subscriptMustFail("0");
  subscriptMustFail(String("0"));
  subscriptMustFail(0);
}

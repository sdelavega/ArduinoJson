// Copyright Benoit Blanchon 2014-2015
// MIT License
//
// Arduino JSON library
// https://github.com/bblanchon/ArduinoJson

#include <gtest/gtest.h>
#include <ArduinoJson.h>

class JsonObject_Add_Tests : public ::testing::Test {
 public:
  JsonObject_Add_Tests() : _object(_jsonBuffer.createObject()) {}

 protected:
  template <typename T>
  void testWithSyntax1(const char* key, T value) {
    _object[key] = value;
    assertValueEquals<T>(key, value);
  }

  template <typename T>
  void testWithSyntax2(const char* key, T value) {
    _object.add(key, value);
    assertValueEquals<T>(key, value);
  }

  template <typename T>
  void testWithSyntax3(const char* key, T value) {
    _object.add(key) = value;
    assertValueEquals<T>(key, value);
  }

  template <typename T>
  void assertValueEquals(const char* key, T value) {
    EXPECT_EQ(value, _object[key].as<T>());
  }

  JsonArray& createArray() { return _jsonBuffer.createArray(); }

  JsonObject& createObject() { return _jsonBuffer.createObject(); }

 private:
  DynamicJsonBuffer _jsonBuffer;
  JsonObject& _object;
};

template <>
void JsonObject_Add_Tests::assertValueEquals(const char* key,
                                             JsonArray& value) {
  EXPECT_EQ(&value, &_object[key].asArray());
}

template <>
void JsonObject_Add_Tests::assertValueEquals(const char* key,
                                             JsonObject& value) {
  EXPECT_EQ(&value, &_object[key].asObject());
}

TEST_F(JsonObject_Add_Tests, CanStoreIntegers) {
  testWithSyntax1("tic", 123);
  testWithSyntax2("tac", 456);
  testWithSyntax3("toe", 789);
}

TEST_F(JsonObject_Add_Tests, CanStoreDoubles) {
  testWithSyntax1("tic", 123.45);
  testWithSyntax2("tac", 456.78);
  testWithSyntax3("toe", 789.01);
}

TEST_F(JsonObject_Add_Tests, CanStoreBooleans) {
  testWithSyntax1("tic", false);
  testWithSyntax2("tac", true);
  testWithSyntax3("toe", false);
}

TEST_F(JsonObject_Add_Tests, CanStoreCharPtrs) {
  testWithSyntax1("tic", "tic");
  testWithSyntax2("tac", "tac");
  testWithSyntax3("toe", "toe");
}

TEST_F(JsonObject_Add_Tests, CanStoreStrings) {
  String tic = "tic";
  String tac = "tac";
  String toe = "toe";

  testWithSyntax1("tic", tic);
  testWithSyntax2("tac", tac);
  testWithSyntax3("toe", toe);
}

TEST_F(JsonObject_Add_Tests, CanStoreInnerArrays) {
  testWithSyntax1<JsonArray&>("tic", createArray());
  testWithSyntax2<JsonArray&>("tac", createArray());
  testWithSyntax3<JsonArray&>("toe", createArray());
}

TEST_F(JsonObject_Add_Tests, CanStoreInnerObjects) {
  testWithSyntax1<JsonObject&>("tic", createObject());
  testWithSyntax2<JsonObject&>("tac", createObject());
  testWithSyntax3<JsonObject&>("toe", createObject());
}

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
  void testSyntax1(const char* key, T value) {
    _object[key] = value;
    assertValueEquals<T>(key, value);
  }

  template <typename T>
  void testSyntax2(const char* key, T value) {
    _object.add(key, value);
    assertValueEquals<T>(key, value);
  }

  template <typename T>
  void testSyntax3(const char* key, T value) {
    _object.add(key) = value;
    assertValueEquals<T>(key, value);
  }

  template <typename T>
  void testSyntax4(const char* key, T value) {
    String keyString(key);
    _object[keyString] = value;
    assertValueEquals<T>(key, value);
  }

  template <typename T>
  void testSyntax5(const char* key, T value) {
    String keyString(key);
    _object.add(keyString, value);
    assertValueEquals<T>(key, value);
  }

  template <typename T>
  void testSyntax6(const char* key, T value) {
    String keyString(key);
    _object.add(keyString) = value;
    assertValueEquals<T>(key, value);
  }

  JsonArray& createArray() { return _jsonBuffer.createArray(); }

  JsonObject& createObject() { return _jsonBuffer.createObject(); }

 private:
  DynamicJsonBuffer _jsonBuffer;
  JsonObject& _object;

  template <typename T>
  void assertValueEquals(const char* key, T value) {
    EXPECT_EQ(value, _object[key].as<T>());
  }
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

TEST_F(JsonObject_Add_Tests, AddBooleans) {
  testSyntax1("one", true);
  testSyntax2("two", false);
  testSyntax3("thr", true);
  testSyntax4("fou", false);
  testSyntax5("fiv", true);
  testSyntax6("six", false);
}

TEST_F(JsonObject_Add_Tests, AddCharPtrs) {
  testSyntax1("one", "one");
  testSyntax2("two", "two");
  testSyntax3("thr", "thr");
  testSyntax4("fou", "fou");
  testSyntax5("fiv", "fiv");
  testSyntax6("six", "six");
}

TEST_F(JsonObject_Add_Tests, AddDoubles) {
  testSyntax1("one", 1.2);
  testSyntax2("two", 2.3);
  testSyntax3("thr", 3.4);
  testSyntax4("fou", 4.5);
  testSyntax5("fiv", 5.6);
  testSyntax6("six", 7.8);
}

TEST_F(JsonObject_Add_Tests, AddFloats) {
  testSyntax1("one", 1.2f);
  testSyntax2("two", 2.3f);
  testSyntax3("thr", 3.4f);
  testSyntax4("fou", 4.5f);
  testSyntax5("fiv", 5.6f);
  testSyntax6("six", 7.8f);
}

TEST_F(JsonObject_Add_Tests, AddIntegers) {
  testSyntax1("one", 123);
  testSyntax2("two", 456);
  testSyntax3("thr", 789);
  testSyntax4("fou", 123);
  testSyntax5("fiv", 456);
  testSyntax6("six", 789);
}

TEST_F(JsonObject_Add_Tests, AddLongs) {
  testSyntax1("one", 123L);
  testSyntax2("two", 456L);
  testSyntax3("thr", 789L);
  testSyntax4("fou", 123L);
  testSyntax5("fiv", 456L);
  testSyntax6("six", 789L);
}

TEST_F(JsonObject_Add_Tests, AddNestedArrays) {
  testSyntax1<JsonArray&>("one", createArray());
  testSyntax2<JsonArray&>("two", createArray());
  testSyntax3<JsonArray&>("thr", createArray());
  testSyntax4<JsonArray&>("fou", createArray());
  testSyntax5<JsonArray&>("fiv", createArray());
  testSyntax6<JsonArray&>("six", createArray());
}

TEST_F(JsonObject_Add_Tests, AddNestedObjects) {
  testSyntax1<JsonObject&>("one", createObject());
  testSyntax2<JsonObject&>("two", createObject());
  testSyntax3<JsonObject&>("thr", createObject());
  testSyntax4<JsonObject&>("fou", createObject());
  testSyntax5<JsonObject&>("fiv", createObject());
  testSyntax6<JsonObject&>("six", createObject());
}

TEST_F(JsonObject_Add_Tests, AddStrings) {
  String one("one");
  String two("two");
  String thr("thr");
  String fou("fou");
  String fiv("fiv");
  String six("six");

  testSyntax1("one", one);
  testSyntax2("two", two);
  testSyntax3("thr", thr);
  testSyntax4("fou", fou);
  testSyntax5("fiv", fiv);
  testSyntax6("six", six);
}

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
  void whenValuesAre(T a, T b, T c, T d, T e, T f) {
    static const char* keyA = "a";
    static const char* keyB = "b";
    static const char* keyC = "c";
    static const String keyD = "d";
    static const String keyE = "e";
    static const String keyF = "f";

    _object[keyA] = a;      // syntax 1
    _object.add(keyB, b);   // syntax 2
    _object.add(keyC) = c;  // syntax 3
    _object[keyD] = d;      // syntax 4
    _object.add(keyE, e);   // syntax 5
    _object.add(keyF) = f;  // syntax 6

    assertValueEquals<T>("a", a);
    assertValueEquals<T>("b", b);
    assertValueEquals<T>("c", c);
    assertValueEquals<T>("d", d);
    assertValueEquals<T>("e", e);
    assertValueEquals<T>("f", f);
  }

  JsonArray& createArray(int value) {
    JsonArray& array = _jsonBuffer.createArray();
    array.add(value);
    return array;
  }

  JsonObject& createObject(int value) {
    JsonObject& object = _jsonBuffer.createObject();
    object.add("key", value);
    return object;
  }

  void jsonMustBe(const char* expected) {
    char actual[256];
    _object.printTo(actual, sizeof(actual));
    ASSERT_STREQ(expected, actual);
  }

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
  whenValuesAre(true, false, true, false, true, false);
  jsonMustBe(
      "{\"a\":true,\"b\":false,\"c\":true,"
      "\"d\":false,\"e\":true,\"f\":false}");
}

TEST_F(JsonObject_Add_Tests, AddCharPtrs) {
  whenValuesAre("a", "b", "c", "d", "e", "f");
  jsonMustBe(
      "{\"a\":\"a\",\"b\":\"b\",\"c\":\"c\","
      "\"d\":\"d\",\"e\":\"e\",\"f\":\"f\"}");
}

TEST_F(JsonObject_Add_Tests, AddDoubles) {
  whenValuesAre(1.11, 2.22, 3.33, 4.44, 5.55, 6.66);
  jsonMustBe(
      "{\"a\":1.11,\"b\":2.22,\"c\":3.33,"
      "\"d\":4.44,\"e\":5.55,\"f\":6.66}");
}

TEST_F(JsonObject_Add_Tests, AddFloats) {
  whenValuesAre(1.11f, 2.22f, 3.33f, 4.44f, 5.55f, 6.66f);
  jsonMustBe(
      "{\"a\":1.11,\"b\":2.22,\"c\":3.33,"
      "\"d\":4.44,\"e\":5.55,\"f\":6.66}");
}

TEST_F(JsonObject_Add_Tests, AddIntegers) {
  whenValuesAre(111, 222, 333, 444, 555, 666);
  jsonMustBe(
      "{\"a\":111,\"b\":222,\"c\":333,"
      "\"d\":444,\"e\":555,\"f\":666}");
}

TEST_F(JsonObject_Add_Tests, AddLongs) {
  whenValuesAre(111L, 222L, 333L, 444L, 555L, 666L);
  jsonMustBe(
      "{\"a\":111,\"b\":222,\"c\":333,"
      "\"d\":444,\"e\":555,\"f\":666}");
}

TEST_F(JsonObject_Add_Tests, AddNestedArrays) {
  whenValuesAre<JsonArray&>(createArray(1), createArray(2), createArray(3),
                            createArray(4), createArray(5), createArray(6));
  jsonMustBe(
      "{\"a\":[1],\"b\":[2],\"c\":[3],"
      "\"d\":[4],\"e\":[5],\"f\":[6]}");
}

TEST_F(JsonObject_Add_Tests, AddNestedObjects) {
  whenValuesAre<JsonObject&>(createObject(1), createObject(2), createObject(3),
                             createObject(4), createObject(5), createObject(6));
  jsonMustBe(
      "{\"a\":{\"key\":1},\"b\":{\"key\":2},\"c\":{\"key\":3},"
      "\"d\":{\"key\":4},\"e\":{\"key\":5},\"f\":{\"key\":6}}");
}

TEST_F(JsonObject_Add_Tests, AddStrings) {
  String a("a");
  String b("b");
  String c("c");
  String d("d");
  String e("e");
  String f("f");
  whenValuesAre(a, b, c, d, e, f);
  jsonMustBe(
      "{\"a\":\"a\",\"b\":\"b\",\"c\":\"c\","
      "\"d\":\"d\",\"e\":\"e\",\"f\":\"f\"}");
}

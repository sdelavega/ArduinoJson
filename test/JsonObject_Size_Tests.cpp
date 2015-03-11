// Copyright Benoit Blanchon 2014-2015
// MIT License
//
// Arduino JSON library
// https://github.com/bblanchon/ArduinoJson

#include <gtest/gtest.h>
#include <ArduinoJson.h>

class JsonObject_Size_Tests : public ::testing::Test {
 public:
  JsonObject_Size_Tests() : _object(_jsonBuffer.createObject()) {}

 protected:
  void add(const char* key) { _object.add(key); }

  void remove(const char* key) { _object.remove(key); }

  void sizeMustBe(int expected) { ASSERT_EQ(expected, _object.size()); }

 private:
  DynamicJsonBuffer _jsonBuffer;
  JsonObject& _object;
};

TEST_F(JsonObject_Size_Tests, InitialSizeIsZero) { sizeMustBe(0); }

TEST_F(JsonObject_Size_Tests, Grow_WhenValuesAreAdded) {
  add("hello");
  sizeMustBe(1);

  add("world");
  sizeMustBe(2);
}

TEST_F(JsonObject_Size_Tests, DoNotGrow_WhenSameValueIsAdded) {
  add("hello");
  sizeMustBe(1);

  add("hello");
  sizeMustBe(1);
}

TEST_F(JsonObject_Size_Tests, Shrink_WhenValuesAreRemoved) {
  add("hello");
  add("world");

  remove("hello");
  sizeMustBe(1);

  remove("world");
  sizeMustBe(0);
}

TEST_F(JsonObject_Size_Tests, DoNotShrink_WhenRemoveIsCalledWithAWrongKey) {
  add("hello");
  remove("world");
  sizeMustBe(1);
}

// Copyright Benoit Blanchon 2014-2015
// MIT License
//
// Arduino JSON library
// https://github.com/bblanchon/ArduinoJson

#include <gtest/gtest.h>
#include <ArduinoJson.h>

TEST(Issue56, AddStringAsKeyOfANestedArray_Syntax2) {
  DynamicJsonBuffer jsonBuffer;

  JsonObject& o = jsonBuffer.createObject();
  String s = "key";

  JsonArray& a = o.createNestedArray(s);
  ASSERT_EQ(&a, &o.at(s).asArray());

  char json[128];
  o.printTo(json, sizeof(json));
  ASSERT_STREQ("{\"key\":[]}", json);
}

TEST(Issue56, AddStringAsKeyOfANestedObject_Syntax2) {
  DynamicJsonBuffer jsonBuffer;

  JsonObject& o = jsonBuffer.createObject();
  String s = "key";

  JsonObject& no = o.createNestedObject(s);
  ASSERT_EQ(&no, &o.at(s).asObject());

  char json[128];
  o.printTo(json, sizeof(json));
  ASSERT_STREQ("{\"key\":{}}", json);
}

TEST(Issue56, JsonBuffer_ParseObject) {
  DynamicJsonBuffer jsonBuffer;
  String json("{\"key\":\"value\"}");
  JsonObject& object = jsonBuffer.parseObject(json);
  ASSERT_TRUE(object.success());
}

TEST(Issue56, JsonBuffer_ParseArray) {
  DynamicJsonBuffer jsonBuffer;
  String json("[1,2]");
  JsonArray& array = jsonBuffer.parseArray(json);
  ASSERT_TRUE(array.success());
}

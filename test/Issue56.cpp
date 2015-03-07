// Copyright Benoit Blanchon 2014-2015
// MIT License
//
// Arduino JSON library
// https://github.com/bblanchon/ArduinoJson

#include <gtest/gtest.h>
#include <ArduinoJson.h>

TEST(Issue56, AsValueOfAnObject) {
  DynamicJsonBuffer jsonBuffer;

  JsonObject& o = jsonBuffer.createObject();
  String s = "value";

  o["key"] = s;
  ASSERT_STREQ("value", o["key"]);

  char json[128];
  o.printTo(json, sizeof(json));
  ASSERT_STREQ("{\"key\":\"value\"}", json);
}

TEST(Issue56, AsValueOfAnArray) {
  DynamicJsonBuffer jsonBuffer;

  JsonArray& a = jsonBuffer.createArray();
  String s = "value";

  a.add(s);
  ASSERT_STREQ("value", a[0]);

  char json[128];
  a.printTo(json, sizeof(json));
  ASSERT_STREQ("[\"value\"]", json);
}

TEST(Issue56, UseStringAsKeyOfAnObject_Syntax1) {
  DynamicJsonBuffer jsonBuffer;

  JsonObject& o = jsonBuffer.createObject();
  String s = "key";

  o[s] = "value";
  ASSERT_STREQ("value", o[s]);

  char json[128];
  o.printTo(json, sizeof(json));
  ASSERT_STREQ("{\"key\":\"value\"}", json);
}

TEST(Issue56, AddStringAsKeyOfAnObject_Syntax2) {
  DynamicJsonBuffer jsonBuffer;

  JsonObject& o = jsonBuffer.createObject();
  String s = "key";

  o.add(s, "value");
  ASSERT_STREQ("value", o.at(s));

  char json[128];
  o.printTo(json, sizeof(json));
  ASSERT_STREQ("{\"key\":\"value\"}", json);
}

TEST(Issue56, AddStringAsKeyOfAnObject_Syntax3) {
  DynamicJsonBuffer jsonBuffer;

  JsonObject& o = jsonBuffer.createObject();
  String s = "key";

  o.add(s) = "value";
  ASSERT_STREQ("value", o[s]);

  char json[128];
  o.printTo(json, sizeof(json));
  ASSERT_STREQ("{\"key\":\"value\"}", json);
}

TEST(Issue56, AddStringAsKeyOfANestedArray_Syntax1) {
  DynamicJsonBuffer jsonBuffer;

  JsonObject& o = jsonBuffer.createObject();
  JsonArray& a = jsonBuffer.createArray();
  String s = "key";

  o.add(s, a);
  ASSERT_EQ(&a, &o[s].asArray());

  char json[128];
  o.printTo(json, sizeof(json));
  ASSERT_STREQ("{\"key\":[]}", json);
}

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

TEST(Issue56, AddStringAsKeyOfANestedObject_Syntax1) {
  DynamicJsonBuffer jsonBuffer;

  JsonObject& o = jsonBuffer.createObject();
  JsonObject& no = jsonBuffer.createObject();
  String s = "key";

  o.add(s, no);
  ASSERT_EQ(&no, &o[s].asObject());

  char json[128];
  o.printTo(json, sizeof(json));
  ASSERT_STREQ("{\"key\":{}}", json);
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

TEST(Issue56, ContainsKey) {
  DynamicJsonBuffer jsonBuffer;

  JsonObject& o = jsonBuffer.createObject();
  String key1 = "key1";
  String key2 = "key2";

  o.add("key1", "value");

  ASSERT_TRUE(o.containsKey(key1));
  ASSERT_FALSE(o.containsKey(key2));
}

TEST(Issue56, RemoveKey) {
  DynamicJsonBuffer jsonBuffer;

  JsonObject& o = jsonBuffer.createObject();
  String key = "key";

  o.add("key", "value");
  ASSERT_TRUE(o.containsKey("key"));

  o.remove(key);
  ASSERT_FALSE(o.containsKey("key"));
}

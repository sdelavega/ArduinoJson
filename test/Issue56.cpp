// Copyright Benoit Blanchon 2014-2015
// MIT License
//
// Arduino JSON library
// https://github.com/bblanchon/ArduinoJson

#include <gtest/gtest.h>
#include <ArduinoJson.h>

TEST(Issue56, UseStringAsValueOfAnObject) {
  DynamicJsonBuffer jsonBuffer;

  JsonObject& o = jsonBuffer.createObject();
  String s = "value";

  o["key"] = s;
  ASSERT_STREQ("value", o["key"]);

  char json[128];
  o.printTo(json, sizeof(json));
  ASSERT_STREQ("{\"key\":\"value\"}", json);
}

TEST(Issue56, UseStringAsValueOfAnArray) {
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
  ASSERT_STREQ("value", o[s]);

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

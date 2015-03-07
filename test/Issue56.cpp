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

// Copyright Benoit Blanchon 2014-2015
// MIT License
//
// Arduino JSON library
// https://github.com/bblanchon/ArduinoJson

#include <gtest/gtest.h>
#include <ArduinoJson.h>

TEST(Issue54, ExtractTheData) {
  char json[] =
      "{\"DEVICE\":[{\"G\":\"0\",\"V\":0,\"D\":1011,\"DA\":\"{\\\"on\\\":true,"
      "\\\"hue\\\":65535,\\\"bri\\\":222}\"}]}";

  DynamicJsonBuffer jsonBuffer;

  JsonObject& root = jsonBuffer.parseObject(json);

  char buffer[128];
  strcpy(buffer, root["DEVICE"][0]["DA"]);
  JsonObject& da = jsonBuffer.parseObject(buffer);

  bool on = da["on"];
  ASSERT_TRUE(on);

  long hue = da["hue"];
  ASSERT_EQ(65535, hue);

  long bri = da["bri"];
  ASSERT_EQ(222, bri);
}

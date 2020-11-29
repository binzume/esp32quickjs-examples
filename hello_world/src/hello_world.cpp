#include <Arduino.h>
#include "esp32/QuickJS.h"

static const char *jscode = R"CODE(
  console.log('Hello, JavaScript!');
)CODE";

ESP32QuickJS qjs;

void setup() {
  Serial.begin(115200);
  qjs.begin();
  qjs.exec(jscode);
}

void loop() {
  qjs.loop(); // For timer, async, etc.
}

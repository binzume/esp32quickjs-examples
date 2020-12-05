#include <Arduino.h>
#include "esp32/QuickJS.h"

// see platformio.ini
extern const char jscode[] asm("_binary_src_main_js_start");

ESP32QuickJS qjs;

void setup() {
  Serial.begin(115200);
  qjs.begin();
  qjs.exec(jscode);
}

void loop() {
  qjs.loop(); // For timer, async, etc.
}

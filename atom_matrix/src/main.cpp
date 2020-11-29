#include <Arduino.h>
#include "M5QuickJS.h"

// see platformio.ini
extern const char jscode[] asm("_binary_src_main_js_start");

M5QuickJS qjs;

void setup() {
  Serial.begin(115200);
  M5.begin(false, true, true);
  qjs.begin();
  qjs.exec(jscode);
  // Serial.print("feee mem:");
  //Serial.println((ESP.getFreeHeap()));
}

void loop() {
  M5.update();
  qjs.loop();
}

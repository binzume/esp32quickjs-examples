#include <Arduino.h>
#include <WiFi.h>
#include "esp32/QuickJS.h"

const char *SSID = "your_wifi_ap";
const char *PASSWORD = "********";

// see platformio.ini
extern const char jscode[] asm("_binary_src_main_js_start");

ESP32QuickJS qjs;

void setup() {
  Serial.begin(115200);
  WiFi.begin(SSID, PASSWORD);
  qjs.begin();
  qjs.exec(jscode);
}

void loop() {
  qjs.loop(); // For timer, async, etc.
}

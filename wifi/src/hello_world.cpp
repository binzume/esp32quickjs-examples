#include <Arduino.h>
#include <WiFi.h>
#include "esp32/QuickJS.h"

const char *SSID = "your_wifi_ap";
const char *PASSWORD = "********";

static const char *jscode = R"CODE(
  console.log('Hello, JavaScript!');
  let waitMs = (t) => new Promise((resolve) => setTimeout(resolve, t));
  (async () => {
    while(!esp32.wifiIsConnected) {
      console.log("connecting wifi...");
      await waitMs(500);
    }
    console.log("connected.");
    let res = await esp32.fetch("https://www.binzume.net/");
    console.log("HTTP Status:" + res.status + " size:" + res.body.length);
  })();
)CODE";

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

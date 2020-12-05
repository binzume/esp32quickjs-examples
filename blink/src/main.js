import * as esp32 from "esp32";
console.log("start");

let ledPin = 25;
esp32.pinMode(ledPin, 2); // 2: OUTPUT
setInterval(function () {
  let v = esp32.digitalRead(ledPin);
  esp32.digitalWrite(ledPin, v ^ 1);
}, 500);

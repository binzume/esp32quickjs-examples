import * as esp32 from "esp32";

async function connectWifi() {
    let waitMs = (t) => new Promise((resolve) => setTimeout(resolve, t));
    while (!esp32.isWifiConnected()) {
        console.log(".");
        await waitMs(500);
    }
}

async function httpGet(url) {
    console.log("GET " + url);
    let res = await esp32.fetch(url);
    console.log("HTTP Status:" + res.status + " size:" + res.body.length);
    let m = res.body.match(/<title>(.*)<\/title>/i);
    if (m) {
        console.log(`Title: ${m[1]}`);
    }
}

console.log("start");
console.log("connecting wifi...");
connectWifi().then(() => {
    console.log("connected.");
    httpGet("https://www.binzume.net/");
});

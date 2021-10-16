#include <ESP8266WiFi.h>

void serialInit();
void wifiInit(bool resetSettings);
void otaInit();
void dhtInit();

void wifiLoop();
void otaLoop();
void dhtLoop();

void setup() {
    serialInit();
    wifiInit(false);
    otaInit();
    ledInit(D0);
    dhtInit(D1);
    telegramInit();
}

void loop() {
    wifiLoop();
    otaLoop();
    telegramLoop();
}

void serialInit(){
    Serial.begin(115200);
}

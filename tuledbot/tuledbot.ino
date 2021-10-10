#include <ESP8266WiFi.h>

void serialInit();
void wifiInit(bool resetSettings);
void otaInit();

void wifiLoop();
void otaLoop();

void setup() {
    serialInit();
    wifiInit(false);
    otaInit();
}

void loop() {
    wifiLoop();
    otaLoop();
}

void serialInit(){
    Serial.begin(115200);
}

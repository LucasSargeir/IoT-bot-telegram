#include <ESP8266WiFi.h>

void serialInit();
void wifiInit(bool resetSettings);
void otaInit();

void wifiLoop();
void otaLoop();
void ledBlink(int time);

void setup() {
    serialInit();
    wifiInit(false);
    otaInit();
    ledInit(D1);
}

void loop() {
    wifiLoop();
    otaLoop();
    
    ledBlink(10);
    delay(1000);
}

void serialInit(){
    Serial.begin(115200);
}

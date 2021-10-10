#include <ESP8266WiFi.h>

void serialInit();
void wifiInit(bool resetSettings);
void otaInit();
void dhtInit();

void wifiLoop();
void otaLoop();
void dhtLoop();

void ledBlink(int time);

void setup() {
    serialInit();
    wifiInit(false);
    otaInit();
    ledInit(D0);
    dhtInit();
}

void loop() {
    wifiLoop();
    otaLoop();
    dhtLoop();
    
    ledBlink(10);
    delay(1000);
}

void serialInit(){
    Serial.begin(115200);
}

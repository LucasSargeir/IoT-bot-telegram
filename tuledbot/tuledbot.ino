#include <ESP8266WiFi.h>

void serialInit();
void wifiInit(bool resetSettings);
void otaInit();
void dhtInit();

void wifiLoop();
void otaLoop();
void dhtLoop();

void ledBlink(int time);

const unsigned long BOT_MTBS = 1000; // mean time between scan messages
unsigned long bot_lasttime; // last time messages' scan has been done

void setup() {
    serialInit();
    wifiInit(false);
    otaInit();
    // ledInit(D0);
    // dhtInit(D1);
    telegramInit();
}

void loop() {
    wifiLoop();
    otaLoop();
    // dhtLoop();
    telegramLoop();
    
    // ledBlink(10);
    delay(1000);
}

void serialInit(){
    Serial.begin(115200);
}

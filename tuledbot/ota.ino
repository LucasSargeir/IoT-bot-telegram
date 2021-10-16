#include <Arduino.h>
#include <ArduinoOTA.h>

const char* OTA_HOSTNAME = "TuledBot_OTA";
const char* OTA_SSID = "TuledBot_OTA";
const char* OTA_PASSWORD = "senha";

void otaOnStart();
void otaOnProgress(unsigned int progress, unsigned int total);
void otaOnEnd();
void otaOnError(ota_error_t error);

void otaInit() {
    ArduinoOTA.setHostname(OTA_HOSTNAME);
    ArduinoOTA.setPassword(OTA_PASSWORD);
    
    ArduinoOTA.onStart(otaOnStart);
    ArduinoOTA.onEnd(otaOnEnd);
    ArduinoOTA.onProgress(otaOnProgress);
    ArduinoOTA.onError(otaOnError);

    ArduinoOTA.begin();
}

void otaLoop() {
    ArduinoOTA.handle();
}

void otaOnStart() {
    Serial.println("\n--- OTA Start ---");
}

void otaOnProgress(unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
}

void otaOnEnd() {
    Serial.println("--- OTA End ---");
}

void otaOnError(ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    
    if(error == OTA_AUTH_ERROR){
        Serial.println("Auth Failed");    
    } 
    else if(error == OTA_BEGIN_ERROR){
        Serial.println("Begin Failed");
    }
    else if(error == OTA_CONNECT_ERROR){
        Serial.println("Connect Failed");
    }
    else if(error == OTA_RECEIVE_ERROR){
        Serial.println("Receive Failed");
    }
    else if(error == OTA_END_ERROR){
        Serial.println("End Failed");
    }
}

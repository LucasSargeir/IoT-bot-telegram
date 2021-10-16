#include <Arduino.h>
#include <WiFiManager.h>
#include <ESP8266WebServer.h>

const char* WIFI_HOSTNAME = "Tuledbot";
const char* WIFI_SSID = "TuledBot_Config";
const char* WIFI_PASSWORD = "senha123";

void wifiManagerConfig(bool resetSettings);

void wifiInit(bool resetSettings) {
    WiFi.hostname(WIFI_HOSTNAME);
    wifiManagerConfig(resetSettings);
}

void wifiManagerConfig(bool resetSettings) {
    Serial.println("\n--- Starting wifi configuration ---");
    WiFiManager wifiManager;
    
    if (resetSettings) {
        Serial.println("Reseting credentials...");
        wifiManager.resetSettings();
    }
    
    wifiManager.autoConnect(WIFI_SSID, WIFI_PASSWORD);
    Serial.println("--- Finished wifi configuration ---");
}

void wifiLoop() {
    
    if (WiFi.status() == WL_CONNECTED){
        return;
    }

    Serial.println("\n--- Starting WiFi Connection ---");

    WiFi.hostname(WIFI_HOSTNAME);
    WiFi.begin();

    while (WiFi.status() != WL_CONNECTED) {
        delay(100);
        Serial.println(".");
    }
   
    Serial.print("Conectado com sucesso na rede: ");
    Serial.println(WIFI_SSID);

    Serial.println("--- End WiFi Connection ---");
}

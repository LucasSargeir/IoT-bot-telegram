#include <Arduino.h>
#include <DHT.h>

DHT* dht;

void dhtInit(int PIN) {
    dht = new DHT(PIN, DHT11);
  
    Serial.println("--- Starting DHT ---");
    (*dht).begin();
}


void dhtLoop() {
    float humidity    = (*dht).readHumidity();
    float tempetature = (*dht).readTemperature();
    
    if (isnan(tempetature) || isnan(humidity)) {
        Serial.println("--- Failed to read from DHT ---");
    }
    else {
        Serial.print("--- Umidade: ");
        Serial.print(humidity);
        Serial.println(" %t       ---");
        Serial.print("--- Temperatura: ");
        Serial.print(tempetature);
        Serial.println(" *C   ---");
    }

    delay(2000);
}

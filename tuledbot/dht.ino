#include <Arduino.h>
#include <DHT.h>

DHT* dht;

void dhtPrintMessage(float humidity, float temperature);

void dhtInit(int PIN) {
    dht = new DHT(PIN, DHT11);
  
    Serial.println("--- Starting DHT ---");
    (*dht).begin();
}


void dhtLoop() {
    float humidity    = (*dht).readHumidity();
    float temperature = (*dht).readTemperature();
    
    if (isnan(temperature) || isnan(humidity)) {
        Serial.println("--- Failed to read from DHT ---");
    }
    else {
        dhtPrintMessage(humidity, temperature);
    }

    delay(2000);
}

float dhtGetTemperature() {
    return (*dht).readTemperature();
}

float dhtGetHumidity() {
    return (*dht).readHumidity();
}

void dhtPrintMessage(float humidity, float temperature) {
    Serial.print("--- Umidade: ");
    Serial.print(humidity);
    Serial.println(" %t       ---");
    Serial.print("--- Temperatura: ");
    Serial.print(temperature);
    Serial.println(" *C   ---");
}

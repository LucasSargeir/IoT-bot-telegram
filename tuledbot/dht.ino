#include <Arduino.h>
#include <DHT.h>

DHT dht(D0, DHT11);

void dhtInit() {
    Serial.print("--- Starting DHT ---");
    dht.begin();
}


void dhtLoop() {
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    // testa se retorno é valido, caso contrário algo está errado.
    if (isnan(t) || isnan(h)){
        Serial.println("Failed to read from DHT");
    } else {
        Serial.print("Umidade: ");
        Serial.print(h);
        Serial.print(" %t");
        Serial.print("Temperatura: ");
        Serial.print(t);
        Serial.println(" *C");
    }

    // delay(2000);
}

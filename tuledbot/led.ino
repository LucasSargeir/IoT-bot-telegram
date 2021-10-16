#include <Arduino.h>

int PIN_LED;
int led_status = 0;

void ledInit(int PIN){
    PIN_LED = PIN;
  
    pinMode(PIN_LED, OUTPUT);
    digitalWrite(PIN_LED, LOW);
}

void ledTurnOn(){
  Serial.println("--- Led Aceso               ---");
  digitalWrite(PIN_LED, HIGH);
  led_status = 1;
}


void ledTurnOff(){
  Serial.println("--- Led Apagado             ---");
  digitalWrite(PIN_LED, LOW);
  led_status = 0;
}

int getLedStatus() {
    return led_status;
}

void ledBlink(int time){
    Serial.println("--- Piscando Led            ---");
    
    ledTurnOn();
    delay(time);
    ledTurnOff();
}

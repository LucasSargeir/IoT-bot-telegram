#include <Arduino.h>

int PIN_LED;

void ledInit(int PIN){
    PIN_LED = PIN;
  
    pinMode(PIN_LED, OUTPUT);
    digitalWrite(PIN_LED, LOW);
}

void ledTurnOn(){
  Serial.print("--- Led Aceso ---");
  digitalWrite(PIN_LED, HIGH);
}


void ledTurnOff(){
  Serial.print("--- Led Apagado ---");
  digitalWrite(PIN_LED, LOW);
}


void ledBlink(int time){
    Serial.print("--- Piscando Led ---");
    
    ledTurnOn();
    delay(time);
    ledTurnOff();
}

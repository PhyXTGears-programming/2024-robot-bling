// SPI to Myself

#include <SPI.h>
#include <string.h>
#include "SPISlave.h"

// Wiring:
// RoboRio RX (1) GP0 <-> GP11  Pico TX (15)
// RoboRio CS (2) GP1 <-> GP9   Pico CS (12)
// RoboRio CK (4) GP2 <-> GP10  Pico CK (14)
// RoboRio TX (5) GP3 <-> GP8   Pico RX (11)

SPISettings spisettings(1000000, MSBFIRST, SPI_MODE0);

void blinkLed() {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(200);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(200);                       // wait for a second
}
/*
void p_0(){
    Serial.println("Sending p 0: Start***************"); // Start
    msgOut("p 0");
}

void p_31(){
    Serial.println("Sending p 31: Use Short Timeout"); // Short Timeout 
    msgOut("p 31");
}

void m_1(){
    Serial.println("Sending m 1: Red"); // Red
    msgOut("m 1");
}

void m_2(){
    Serial.println("Sending m 2: Yellow"); // Yellow
    msgOut("m 2");
}
*/

// Core 0 will be SPI RoboRio
void setup() {
  SPI.setRX(0);  // Pin 1
  SPI.setCS(1);  // Pin 2
  SPI.setSCK(2); // Pin 4
  SPI.setTX(3);  // Pin 5
  SPI.begin(true);
  pinMode(LED_BUILTIN, OUTPUT);
  delay(5000);
}

int transmits = 1;
void loop() {
  char msg[6];
  memset(msg, 0, sizeof(msg));
  sprintf(msg, "m 1");
  Serial.printf("RoboRio to Pico Sending: '%s'\n", msg);
  SPI.beginTransaction(spisettings);
  SPI.transfer(msg, sizeof(msg));
  SPI.endTransaction();
  delay(2000);
  blinkLed();
  sprintf(msg, "m 2");
  Serial.printf("RoboRio to Pico Sending: '%s'\n", msg);
  SPI.beginTransaction(spisettings);
  SPI.transfer(msg, sizeof(msg));
  SPI.endTransaction();
  delay(1000);
  blinkLed();
  sprintf(msg, "m 3");
  Serial.printf("RoboRio to Pico Sending: '%s'\n", msg);
  SPI.beginTransaction(spisettings);
  SPI.transfer(msg, sizeof(msg));
  SPI.endTransaction();
  delay(1000);
  blinkLed();  
}

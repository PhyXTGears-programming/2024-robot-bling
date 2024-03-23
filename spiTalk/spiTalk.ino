// Shows how to use SPISlave on a single device.
// Core0 runs as an SPI master and initiates a transmission to the slave
// Core1 runs the SPI Slave mode and provides a unique reply to messages from the master
//
// Released to the public domain 2023 by Earle F. Philhower, III <earlephilhower@yahoo.com>

#include <SPI.h>
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

// SPI master
void setup() {
  SPI.setRX(0);
  SPI.setCS(1);
  SPI.setSCK(2);
  SPI.setTX(3);
  SPI.begin(true);
  pinMode(LED_BUILTIN, OUTPUT);
  delay(5000);
}

void msgOut(char localMsg){
  char msg[15];
  memset(msg, 0, sizeof(msg));
  sprintf(msg, &localMsg);
  SPI.beginTransaction(spisettings);
  SPI.transfer(msg, sizeof(msg));
  SPI.endTransaction();
  blinkLed();
}
int transmits = 0;
void loop() {
/**
  char msg[42];
  memset(msg, 0, sizeof(msg));
  sprintf(msg, "What's up? This is transmission %d", transmits);
  Serial.printf("\n\nM-SEND: '%s'\n", msg);
  SPI.beginTransaction(spisettings);
  SPI.transfer(msg, sizeof(msg));
  SPI.endTransaction();
  Serial.printf("M-RECV: '%s'\n", msg);
  transmits++;
  delay(5000);
**/
  msgOut('My Message Out');  
  delay(5000);
}

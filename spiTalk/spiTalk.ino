// Shows how to use SPISlave on a single device.
// Core0 runs as an SPI master and initiates a transmission to the slave
// Core1 runs the SPI Slave mode and provides a unique reply to messages from the master
//
// Released to the public domain 2023 by Earle F. Philhower, III <earlephilhower@yahoo.com>

#include <SPI.h>
#include "SPISlave.h"

// Wiring:
// Master RX  GP0 <-> GP11  Slave TX
// Master CS  GP1 <-> GP9   Slave CS
// Master CK  GP2 <-> GP10  Slave CK
// Master TX  GP3 <-> GP8   Slave RX

SPISettings spisettings(1000000, MSBFIRST, SPI_MODE0);

// SPI master
void setup() {
  SPI.setRX(0);
  SPI.setCS(1);
  SPI.setSCK(2);
  SPI.setTX(3);
  SPI.begin(true);

  delay(5000);
}

int transmits = 0;
void loop() {
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
}

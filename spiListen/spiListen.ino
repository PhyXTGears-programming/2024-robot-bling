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

// SPI slave
volatile bool recvBuffReady = false;
char recvBuff[42] = "";
int recvIdx = 0;
void recvCallback(uint8_t *data, size_t len) {
  memcpy(recvBuff + recvIdx, data, len);
  recvIdx += len;
  if (recvIdx == sizeof(recvBuff)) {
    recvBuffReady = true;
    recvIdx = 0;
  }
}

int sendcbs = 0;
// Note that the buffer needs to be long lived, the SPISlave doesn't copy it.  So no local stack variables, only globals or heap(malloc/new) allocations.
char sendBuff[42];
void sentCallback() {
  memset(sendBuff, 0, sizeof(sendBuff));
  //sprintf(sendBuff, "Slave to Master Xmission %d", sendcbs++);
  SPISlave1.setData((uint8_t*)sendBuff, sizeof(sendBuff));
}

void blinkLed(int localTimeOut){
    digitalWrite(LED_BUILTIN, HIGH);
    delay(localTimeOut);  
    digitalWrite(LED_BUILTIN, LOW);
    delay(localTimeOut);
}

// Note that we use SPISlave1 here **not** because we're running on
// Core 1, but because SPI0 is being used already.  You can use
// SPISlave or SPISlave1 on any core.
void setup() {
  SPI.begin(true);
  SPISlave.setRX(0);
  SPISlave.setCS(1);
  SPISlave.setSCK(2);
  SPISlave.setTX(3);
  //Serial.begin();
  pinMode(LED_BUILTIN, OUTPUT);
  // Ensure we start with something to send...
  sentCallback();
  // Hook our callbacks into the slave
  SPISlave.onDataRecv(recvCallback);
  SPISlave.onDataSent(sentCallback);
  SPISlave.begin(spisettings);
  delay(3000);
  //Serial.println("S-INFO: SPISlave started");
}

void loop() {
  blinkLed(200);
  if (recvBuffReady) {
    //Serial.printf("S-RECV: '%s'\n", recvBuff);
    recvBuffReady = false;
  }
}

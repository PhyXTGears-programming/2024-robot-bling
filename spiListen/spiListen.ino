// SPI Listen

#include <SPI.h>
#include "SPISlave.h"

// Wiring:
// RoboRio RX (1) GP0 <-> GP11  Pico TX (15)
// RoboRio CS (2) GP1 <-> GP9   Pico CS (12)
// RoboRio CK (4) GP2 <-> GP10  Pico CK (14)
// RoboRio TX (5) GP3 <-> GP8   Pico RX (11)

void blinkLed() {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(200);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(200);                       // wait for a second
}

SPISettings spisettings(1000000, MSBFIRST, SPI_MODE0);
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop(){
}
// Core 1 will be SPI Pico

volatile bool recvBuffReady = false;
char recvBuff[5] = "";
int recvIdx = 0;
void recvCallback(uint8_t *data, size_t len) {
  memcpy(recvBuff + recvIdx, data, len);
  recvIdx += len;
  if (recvIdx > 0) {
    recvBuffReady = true;
    recvIdx = 0;
  }
}

int sendcbs = 0;
// Note that the buffer needs to be long lived, the SPISlave doesn't copy it.  So no local stack variables, only globals or heap(malloc/new) allocations.
char sendBuff[42];
void sentCallback() {
  memset(sendBuff, 0, sizeof(sendBuff));
  sprintf(sendBuff, "Pico to RoboRio transmission %d", sendcbs++);
  SPISlave1.setData((uint8_t*)sendBuff, sizeof(sendBuff));
}

// Note that we use SPISlave1 here **not** because we're running on
// Core 1, but because SPI0 is being used already.  You can use
// SPISlave or SPISlave1 on any core.
void setup1() {
  Serial.begin();
  SPISlave1.setRX(8);   // Pin 11
  SPISlave1.setCS(9);   // Pin 12
  SPISlave1.setSCK(10); // Pin 14
  SPISlave1.setTX(11);  // Pin 15
  // Ensure we start with something to send...
  sentCallback();
  
  // Hook our callbacks into the Pico
  SPISlave1.onDataRecv(recvCallback);
  SPISlave1.onDataSent(sentCallback);
  SPISlave1.begin(spisettings);
  delay(3000);


}

void loop1() {
  if (recvBuffReady) {
    blinkLed();
    Serial.printf("*** Pico-Receiving: '%s'\n", recvBuff);
    recvBuffReady = false;
  }
}

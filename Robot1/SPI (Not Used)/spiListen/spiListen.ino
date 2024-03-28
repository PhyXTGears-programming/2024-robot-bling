// SPI to Myself

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

// Core 0 will be SPI RoboRio
void setup() {
  /*SPI.setRX(0);  // Pin 1
  SPI.setCS(1);  // Pin 2
  SPI.setSCK(2); // Pin 4
  SPI.setTX(3);  // Pin 5
  SPI.begin(true);
  */
  pinMode(LED_BUILTIN, OUTPUT);
  //delay(5000);
}

int transmits = 1;
void loop() {
  /**char msg[42];
  memset(msg, 0, sizeof(msg));
  sprintf(msg, "This is transmission %d", transmits);
  Serial.printf("RoboRio to Pico Sending: '%s'\n", msg);
  SPI.beginTransaction(spisettings);
  SPI.transfer(msg, sizeof(msg));
  SPI.endTransaction();
  Serial.printf("RoboRio from Pico Receiving: '%s'\n", msg);
  transmits++;
  delay(5000);
  //blinkLed();
  **/
}

// Core 1 will be SPI Pico

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
  sprintf(sendBuff, "Pico to RoboRio transmission %d", sendcbs++);
  SPISlave1.setData((uint8_t*)sendBuff, sizeof(sendBuff));
}

// Note that we use SPISlave1 here **not** because we're running on
// Core 1, but because SPI0 is being used already.  You can use
// SPISlave or SPISlave1 on any core.
void setup1() {
  SPISlave1.setRX(8);   // Pin 15
  SPISlave1.setCS(9);   // Pin 12
  SPISlave1.setSCK(10); // Pin 14
  SPISlave1.setTX(11);  // Pin 11
  // Ensure we start with something to send...
  //sentCallback();
  // Hook our callbacks into the Pico
  SPISlave1.onDataRecv(recvCallback);
  SPISlave1.onDataSent(sentCallback);
  SPISlave1.begin(spisettings);
  delay(3000);
  Serial.begin();
  //Serial.println("Pico-Info: SPISlave started");
}

void loop1() {
  if (recvBuffReady) {
    blinkLed();
    Serial.printf("*** Pico-Receiving: '%s'\n", recvBuff);
    recvBuffReady = false;
  }
}

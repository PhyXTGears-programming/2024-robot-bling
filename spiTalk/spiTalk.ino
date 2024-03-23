// SPI Talk
// RoboRio Test Script

#include <string>
#include <SPI.h>
#include "SPISlave.h"
#define veryShortTimeout 200
#define shortTimeout 1000
#define midTimeout 2500
#define longTimeout 10000

// Wiring:
// RoboRio RX GP0 Pin(1) 
// RoboRio CS GP1 Pin(2) 
// RoboRio CK GP2 Pin(4)
// RoboRio TX GP3 Pin(5)

SPISettings spisettings(1000000, MSBFIRST, SPI_MODE0);

void blinkLed(int localTimeOut){
    digitalWrite(LED_BUILTIN, HIGH);
    delay(localTimeOut);  
    digitalWrite(LED_BUILTIN, LOW);
    delay(localTimeOut);
}

void msgOut(std::string localMsg);

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

void msgOut(std::string localMsg){
  SPI.beginTransaction(spisettings);
  SPI.transfer((void *)localMsg.c_str(), localMsg.size() + 1);
  SPI.endTransaction();
  blinkLed(midTimeout);
}

void setup() {
  Serial.begin();
  SPI.setRX(0);
  SPI.setCS(1);
  SPI.setSCK(2);
  SPI.setTX(3);
  SPI.begin();
  pinMode(LED_BUILTIN, OUTPUT);
  delay(5000);
}

void loop() {
    p_0(); // Start
    blinkLed(veryShortTimeout); 
    ///////////////////////////////////////////////////////////
    p_31(); // Short time-out
    blinkLed(veryShortTimeout); 
    m_1();// Red
    blinkLed(midTimeout); 
    delay(100);
}

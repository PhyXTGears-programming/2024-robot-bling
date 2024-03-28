
#include <string>
#include <Adafruit_NeoPixel.h>
#include "SPISlave.h"
#include "RingBuffer.h"

CassiusRingBuffer recvBuff;
SPISettings spiSettings(1000000, MSBFIRST, SPI_MODE0);

/////////////////////////////////////////////////////////////////
// Data Constants
#define numLedBase 40    // # of Base Leds
#define ledPinBase 16    // Base ouput pin
/*
#define numLedClimber1 20    // # of Climber1 Leds (Left)
#define numLedClimber2 20    // # of Climber1 Leds (Right)
#define numLedTrap 36       // # of Trap Leds
#define numLedSpeaker 40    // # of Speaker Leds

#define ledPinClimber1 16    // Climber1 ouput pin (Left)
#define ledPinClimber2 17    // Climber2 ouput pin (Right)
#define ledPinTrap 18       // Trap ouput pin
#define ledPinSpeaker 19    // Speaker ouput pin
*/
#define veryShortTimeout 200
#define shortTimeout 1000
#define midTimeout 2000
#define longTimeout 3000

#define fastRate 150
#define midRate 250
#define slowRate 350

#define lowBright 125
#define midBright  170
#define highBright 255

/////////////////////////////////////////////////////////////////
Adafruit_NeoPixel ledBase(numLedBase, ledPinBase, NEO_GRB + NEO_KHZ800);

/*Adafruit_NeoPixel ledClimber1(numLedClimber1, ledPinClimber1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel ledClimber2(numLedClimber2, ledPinClimber2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel ledTrap(numLedTrap, ledPinTrap, NEO_GRB + NEO_KHZ800); 
Adafruit_NeoPixel ledSpeaker(numLedSpeaker, ledPinSpeaker, NEO_GRB + NEO_KHZ800); 
*/
#define picoRed ledBase.Color(currentBrightness, 0, 0)
#define picoOrange ledBase.Color(currentBrightness, int(0.27*currentBrightness), 0)
#define picoYellow ledBase.Color(currentBrightness, int(0.65*currentBrightness), 0)
#define picoGreen ledBase.Color(0, currentBrightness, 0)
#define picoBlue ledBase.Color(0, 0, currentBrightness)
#define picoPurple ledBase.Color(int(0.58*currentBrightness), int(0.11*currentBrightness), int(0.58*currentBrightness))
#define picoBlack ledBase.Color(0, 0, 0)

/////////////////////////////////////////////////////////////////
// Global control parameters

int ledStripUsed = 1;
// #1 is Base
/*
// #1 is Climber1
// #2 is Climber2
// #3 is Trap
// #4 is Speaker
*/
int currentTimeout = shortTimeout;
// Short Timeout; Mid Timeout; Long Timeout

int currentFlashRate = midRate;
// Slow Rate; Mid Rate; Fast Rate

int currentBrightness = midBright;
// Low Bright; Mid Bright; High Bright

int currentOneColor = picoRed;

int currentTwoColorOn = picoBlue;

int currentTwoColorOff = picoBlack;

bool runOneColor = false; // Controls running of OneColor()

bool runTwoColor = false; // Controls running of TwoColor()

bool char_in = false;

/////////////////////////////////////////////////////////////////

void blinkLed() {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(200);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
}

void clearAll(){
  //Serial.println("Clear All");
  runOneColor = false;
  runTwoColor = false;
  ledBase.clear();
  delay(100);
  ledBase.show();
  /*ledClimber1.clear();
  delay(100);
  ledClimber1.show();
  ledTrap.clear();
  delay(100);
  ledTrap.show();
  ledSpeaker.clear();
  delay(100);
  ledSpeaker.show();
  */
}
void oneColor(int newLedStrip, int newColor, long newDuration) {
  //Serial.println("Starting oneColor() ");
  if (runOneColor) {
    Serial.println("Run One color is true");
  }
  else if (!runOneColor)  {
    //Serial.println("Run One color is false");
  }
    long endTime = millis() + newDuration;
    //Serial.printf("oneColor: End Time is: %u, \n\r",endTime);
    //Serial.printf("oneColor: Current Time is %u, \n\r",millis());
  while ((millis() < endTime) && (runOneColor == true)){
    //Serial.println("In while < endtime");
    //Serial.printf("Current Time is %u, \n\r",millis());
    if (ledStripUsed == 1) {
      ledBase.fill(newColor,0,numLedBase);
      ledBase.show();
    } // End if ledStripUsed is 1
    /*
    if (ledStripUsed == 1) {
      ledClimber1.fill(newColor,0,numLedClimber1);
      ledClimber1.show();
    } // End if ledStripUsed is 1
    else if (ledStripUsed == 2) {
      ledClimber2.fill(newColor,0,numLedClimber1);
      ledClimber2.show();
    } // End if ledStripUsed is 2
    else if (ledStripUsed == 3) {
      ledTrap.fill(newColor,0,numLedTrap);
      ledTrap.show();
    } // End if ledStripUsed is 3
    else if (ledStripUsed == 4) {
      ledSpeaker.fill(newColor,0,numLedTrap);
      ledSpeaker.show();
    } // End if ledStripUsed is 4
    */
    //delay(150);
  } // End while < newTime 
  //Serial.printf("Ending Time for One-Color is %u secs, \n\r",int(millis()/1000));
  if (ledStripUsed == 1) {
    ledBase.clear();
    delay(100);
    ledBase.show();
    } // End if ledStripUsed is 1
    /*
  if (ledStripUsed == 1) {
    ledClimber1.clear();
    ledClimber1.show();
    } // End if ledStripUsed is 1
  else if (ledStripUsed == 1) {
    ledClimber1.clear();
    ledClimber1.show();
    } // End if ledStripUsed is 2
    else if (ledStripUsed == 3) {
      ledTrap.clear();
      ledTrap.show();
    } // End if ledStripUsed is 3
    else if (ledStripUsed == 4) {
      ledSpeaker.clear();
      ledSpeaker.show();
    } // End if ledStripUsed is 4
    */
  //Serial.println("Ending oneColor() ");
  runOneColor = false;
} // End oneColor

/////////////////////////////////////////////////////////////////

void twoColor(int newLedStrip, uint32_t newOnColor, uint32_t newOffColor, long newOnTime, long newOffTime, long newDuration ) {
  //Serial.println("Starting twoColor() ");
  if (runTwoColor) {
    Serial.println("Run Two color is true");
  }
  else if (!runTwoColor)  {
    //Serial.println("Run Two color is false");
  }
  long endTime = millis() + newDuration;
  long currentTime = millis();
  long nextTime;
  //Serial.printf("End Time is: %u, \n\r",endTime);
  while ((millis() < endTime) && (runTwoColor == true)){
    //Serial.println("In while < endtime");
    //Serial.printf("Current Time is %u, \n\r",millis());
    if (ledStripUsed == 1) {
      ledBase.fill(newOnColor,0,numLedBase);
      ledBase.show();
    } // End if ledStripUsed is 1
    /*
    if (ledStripUsed == 1) {
      ledClimber1.fill(newOnColor,0,numLedClimber1);
      ledClimber1.show();
    } // End if ledStripUsed is 1
    if (ledStripUsed == 2) {
      ledClimber2.fill(newOnColor,0,numLedClimber1);
      ledClimber2.show();
    } // End if ledStripUsed is 2
    else if (ledStripUsed == 3) {
      ledTrap.fill(newOnColor,0,numLedTrap);
      ledTrap.show();
    } // End if ledStripUsed is 3
    else if (ledStripUsed == 4) {
      ledSpeaker.fill(newOnColor,0,numLedTrap);
      ledSpeaker.show();
    } // End if ledStripUsed is 4
    */
    nextTime = millis() + newOnTime; // End time for next on-time cycle
    while (millis() < nextTime){ // LED Strip is on
      //Serial.printf("Time while LED strip is on: %u, \n\r",millis());
      delay(150);
    } // End while on-time
    if (ledStripUsed == 1) {
      ledBase.fill(newOffColor,0,numLedBase);
      ledBase.show();
    } // End if ledStripUsed is 1
    /*    
    if (ledStripUsed == 1) {
      ledClimber1.fill(newOffColor,0,numLedClimber1);
      ledClimber1.show();
    } // End if ledStripUsed is 1
    if (ledStripUsed == 2) {
      ledClimber2.fill(newOffColor,0,numLedClimber1);
      ledClimber2.show();
    } // End if ledStripUsed is 2
    else if (ledStripUsed == 3) {
      ledTrap.fill(newOffColor,0,numLedTrap);
      ledTrap.show();
    } // End if ledStripUsed is 3
    else if (ledStripUsed == 4) {
      ledSpeaker.fill(newOffColor,0,numLedTrap);
      ledSpeaker.show();
    } // End if ledStripUsed is 4
    */
    nextTime = millis() + newOffTime; // End time for next off-time cycle
    while (millis() < nextTime){ // LED Strip is oFF
      //Serial.printf("Time while LED strip is off: %u, \n\r",millis());
      delay(150);
    } // End while off-time
  //delay(100);
  } // End while <  End Time 
  //Serial.printf("Ending Time for Two-Color is %u secs, \n\r",int(millis()/1000));
  if (ledStripUsed == 1) {
    ledBase.clear();
    ledBase.show();
   } // End if ledStripUsed is 1
  /*
  if (ledStripUsed == 1) {
    ledClimber1.clear();
    ledClimber1.show();
   } // End if ledStripUsed is 1
  if (ledStripUsed == 2) {
    ledClimber2.clear();
    ledClimber2.show();
   } // End if ledStripUsed is 2
   else if (ledStripUsed == 3) {
      ledTrap.clear();
      ledTrap.show();
    } // End if ledStripUsed is 3
   else if (ledStripUsed == 4) {
      ledSpeaker.clear();
      ledSpeaker.show();
    } // End if ledStripUsed is 4
    */
  //Serial.println("Ending twoColor() ");
    runTwoColor = false;
} // End twoColor

/////////////////////////////////////////////////////////////////
/*
void checkInput() {
  //delay(1000);
  Serial.println("checkInput: Waiting for input");  
  if (char_in == true){
     Serial.println("Char-in true");
     while (buff.hasMessage()) {
      //Serial.printf("Buff: !empty %d\r\n", buff.size());
      if (buff.startsWith("m ")) {
        Serial.println("m-command received");
        clearAll();
        buff.drop(2); // Drops the "m_"; Ready to read the integers
        int localInt1 = buff.getNumber();
        digitalWrite(LED_BUILTIN, HIGH);
        delay(veryShortTimeout);  
        digitalWrite(LED_BUILTIN, LOW);
        delay(veryShortTimeout); 
        if (localInt1 == 1){
          Serial.println("Mode M 1 received: Use Red");
            currentOneColor = picoRed;
            runOneColor = true;
        } // End "M 1"
        
        else if (localInt1 == 2){
          Serial.println("Mode M 2 received: Use Yellow");
            currentOneColor = picoYellow;
            runOneColor = true;
        } // End "M 2"
        
        else if (localInt1 == 3){
          Serial.println("Mode M 3 received: Use Green");
            currentOneColor = picoGreen;
            runOneColor = true;
        } // End "M 3"

        else if (localInt1 == 5){
          Serial.println("Mode M 5 received: Use Orange");
            currentOneColor = picoOrange;
            runOneColor = true;
        } // End "M 5"

        else if (localInt1 == 6){
          Serial.println("Mode M 6 received: Use Purple");
            currentOneColor = picoPurple;
            runOneColor = true;
        } // End "M 6"

        else if (localInt1 == 11){
          Serial.println("Mode M 11 received: Use Blue Flash");
          currentTwoColorOn = picoBlue;
          currentTwoColorOff = picoBlack;
          runTwoColor = true;          
        } // End "M 11"
        else {
          Serial.printf("Unknown command received: %d\r\n", localInt1);
         }
        } // end m-command received
     else if (buff.startsWith("p ")) {
        Serial.println("p-command received");
        buff.drop(2); // Drops the "p_"; Ready to read the integers
        int localInt2 = buff.getNumber();
        digitalWrite(LED_BUILTIN, HIGH);
        delay(veryShortTimeout);  
        digitalWrite(LED_BUILTIN, LOW);
        delay(veryShortTimeout);
        
        switch (localInt2) {
          case 0:
            Serial.println("Mode P 0 received: Start *****************");
            Serial.printf("Running Time is %u secs\n\r",int(millis()/1000));
            break;

          case 1:
            Serial.println("Mode P 1 received: Use Climber1 Led Strip");
            ledStripUsed = 1;
            break;

          case 2:
            Serial.println("Mode P 2 received: Use Climber2 Led Strip");
            ledStripUsed = 2;
            break;

          case 3:
            Serial.println("Mode P 3 received: Use Trap Led Strip");
            ledStripUsed = 3;
            break;

          case 4:
            Serial.println("Mode P 4 received: Use Speaker Led Strip");
            ledStripUsed = 4;
            break;

          case 11:
            Serial.println("Mode P 11 received: Use low brightness");
            currentBrightness = lowBright;
            break;

          case 12:
            Serial.println("Mode P 12 received: Use mid brightness");
            currentBrightness = midBright;
            break;

          case 13:
            Serial.println("Mode P 13 received: Use high brightness");
            currentBrightness = highBright;
            break;

          case 21:
            Serial.println("Mode P 21 received: Use slow flash rate");
            currentFlashRate = slowRate;
            break;

          case 22:
            Serial.println("Mode P 22 received: Use mid flash rate");
            currentFlashRate = midRate;
            break;

          case 23:
            Serial.println("Mode P 23 received: Use high flash rate");
            currentFlashRate = fastRate;
            break;

          case 31:
            Serial.println("Mode P 31 received: Use short time-out");
            currentTimeout = shortTimeout;
            break;

          case 32:
            Serial.println("Mode P 32 received: Use mid time-out");
            currentTimeout = midTimeout;
            break;

          case 33:
            Serial.println("Mode P 33 received: Use long time-out");
            currentTimeout = longTimeout;
            break;

        } // End switch
     } // end p-command received
     else {
       //buff.drop(1);
     } // end else
     } // end while has-message is true
    } // end if char-in is true
} // End checkInput()
*/
/////////////////////////////////////////////////////////////////

void setup() {
    Serial.begin(115200);
    delay(3000);
    ledBase.begin();
    ledBase.clear();
    ledBase.setBrightness(45);
    pinMode(LED_BUILTIN, OUTPUT);
    
    /*ledClimber1.begin();
    ledClimber1.clear();
    ledClimber1.setBrightness(45);

    ledTrap.begin();
    ledTrap.clear();
    ledTrap.setBrightness(45);

    ledSpeaker.begin();
    ledSpeaker.clear();
    ledSpeaker.setBrightness(45);
    */
    delay(1000);
} // End setup()

//////////////////////////////////////////////////////////////////////
void loop() {    
  oneColor(ledStripUsed, currentOneColor, currentTimeout);
  delay(100);
  twoColor(ledStripUsed, currentTwoColorOn, currentTwoColorOff, currentFlashRate, currentFlashRate, currentTimeout);
  delay(100);
} // End loop()
///////////////////////////////////////////////////////////////////////////////

// Core 1 will receive commands from the RoboRio

volatile bool recvBuffReady = false;
//char recvBuff[42] = "";
int recvIdx = 0;
void recvCallback(uint8_t *data, size_t len) {
  /*memcpy(recvBuff + recvIdx, data, len);
  recvIdx += len;
  if (recvIdx == sizeof(recvBuff)) {
    recvBuffReady = true;
    recvIdx = 0;
    */
   int i;
   for (i=0; i<len; i++){
    recvBuff.put(data[i]);
    }
   recvBuffReady = true;   
}

char sendBuff[10];
void sentCallback() {
  memset(sendBuff, 0, sizeof(sendBuff));
  sprintf(sendBuff,"Nothing");
  SPISlave1.setData((uint8_t*)sendBuff, sizeof(sendBuff));
}

void setup1() {
  SPISlave1.setRX(8);   // Pin 15
  SPISlave1.setCS(9);   // Pin 12
  SPISlave1.setSCK(10); // Pin 14
  SPISlave1.setTX(11);  // Pin 11
  sentCallback();
  // Hook our callbacks into the Pico
  SPISlave1.onDataRecv(recvCallback);
  SPISlave1.onDataSent(sentCallback);
  SPISlave1.begin(spiSettings);
  delay(3000);
  Serial.begin();
  //Serial.println("Pico-Info: SPISlave started");
}

void loop1() {
  if (recvBuffReady) {
    if (recvBuff.startsWith("m ")) {
        Serial.println("m-command received");
        blinkLed();
        //clearAll();
        recvBuff.drop(2); // Drops the "m_"; Ready to read the integers
        int localInt = recvBuff.getNumber();
        if (localInt == 1){
          Serial.println("Mode M 1 received: Use Red");
            currentOneColor = picoRed;
            runOneColor = true;
        } // End "M 1"
        else if (localInt == 2){
          Serial.println("Mode M 2 received: Use Yellow");
            currentOneColor = picoYellow;
            runOneColor = true;
        } // End "M 2"
        else if (localInt == 3){
          Serial.println("Mode M 3 received: Use Green");
            currentOneColor = picoGreen;
            runOneColor = true;
        } // End "M 3"
    }
    /*
    Serial.printf("*** Pico-Receiving: '%s'\n", recvBuff);
    if (recvBuff == "m 1"){
      Serial.printf("M1 command received'\n");
    }
    */
    recvBuffReady = false;
  }
}

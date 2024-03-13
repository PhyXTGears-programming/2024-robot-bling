
#include <string>
#include "RingBuffer.h"
#include <Adafruit_NeoPixel.h>

CassiusRingBuffer buff;

/////////////////////////////////////////////////////////////////
// Data Constants
#define numLedClimber 35    // # of Climber Leds
#define numLedTrap 36       // # of Trap Leds
#define numLedSpeaker 40    // # of Speaker Leds

#define ledPinClimber 16    // Climber ouput pin
#define ledPinTrap 18       // Trap ouput pin
#define ledPinSpeaker 20    // Speaker ouput pin

#define veryShortTimeout 200
#define shortTimeout 60000
#define midTimeout 60000
#define longTimeout 60000

#define fastRate 150
#define midRate 250
#define slowRate 350

#define lowBright 125
#define midBright  170
#define highBright 255

/////////////////////////////////////////////////////////////////

Adafruit_NeoPixel ledTrap(numLedTrap, ledPinTrap, NEO_GRB + NEO_KHZ800); 
Adafruit_NeoPixel ledClimber(numLedClimber, ledPinClimber, NEO_GRB + NEO_KHZ800); 
Adafruit_NeoPixel ledSpeaker(numLedSpeaker, ledPinSpeaker, NEO_GRB + NEO_KHZ800); 

#define picoRed ledClimber.Color(currentBrightness, 0, 0)
#define picoOrange ledClimber.Color(currentBrightness, int(0.27*currentBrightness), 0)
#define picoYellow ledClimber.Color(currentBrightness, int(0.65*currentBrightness), 0)
#define picoGreen ledClimber.Color(0, currentBrightness, 0)
#define picoBlue ledClimber.Color(0, 0, currentBrightness)
#define picoPurple ledClimber.Color(int(0.58*currentBrightness), int(0.11*currentBrightness), int(0.58*currentBrightness))
#define picoBlack ledClimber.Color(0, 0, 0)

/////////////////////////////////////////////////////////////////
// Global control parameters

int ledStripUsed = 1;
// #1 is Climber
// #2 is Trap
// #3 is Speaker

int currentTimeout = midTimeout;
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

void clearAll(){
  Serial.println("Clear All");
  runOneColor = false;
  runTwoColor = false;
  ledClimber.clear();
  delay(100);
  ledClimber.show();
  ledTrap.clear();
  delay(100);
  ledTrap.show();
  ledSpeaker.clear();
  delay(100);
  ledSpeaker.show();
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
      ledClimber.fill(newColor,0,numLedClimber);
      ledClimber.show();
    } // End if ledStripUsed is 1
    else if (ledStripUsed == 2) {
      ledTrap.fill(newColor,0,numLedTrap);
      ledTrap.show();
    } // End if ledStripUsed is 2
    else if (ledStripUsed == 3) {
      ledSpeaker.fill(newColor,0,numLedTrap);
      ledSpeaker.show();
    } // End if ledStripUsed is 3
    //delay(150);
  } // End while < newTime 
  //Serial.printf("Ending Time for One-Color is %u secs, \n\r",int(millis()/1000));
  if (ledStripUsed == 1) {
    ledClimber.clear();
    ledClimber.show();
    } // End if ledStripUsed is 1
    else if (ledStripUsed == 2) {
      ledTrap.clear();
      ledTrap.show();
    }  
    else if (ledStripUsed == 3) {
      ledSpeaker.clear();
      ledSpeaker.show();
    } 
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
      ledClimber.fill(newOnColor,0,numLedClimber);
      ledClimber.show();
    } // End if ledStripUsed is 1
    else if (ledStripUsed == 2) {
      ledTrap.fill(newOnColor,0,numLedTrap);
      ledTrap.show();
    } // End if ledStripUsed is 2
    else if (ledStripUsed == 3) {
      ledSpeaker.fill(newOnColor,0,numLedTrap);
      ledSpeaker.show();
    } // End if ledStripUsed is 3
    nextTime = millis() + newOnTime; // End time for next on-time cycle
    while (millis() < nextTime){ // LED Strip is on
      //Serial.printf("Time while LED strip is on: %u, \n\r",millis());
      delay(150);
    } // End while on-time
    if (ledStripUsed == 1) {
      ledClimber.fill(newOffColor,0,numLedClimber);
      ledClimber.show();
    } // End if ledStripUsed is 1
    else if (ledStripUsed == 2) {
      ledTrap.fill(newOffColor,0,numLedTrap);
      ledTrap.show();
    } // End if ledStripUsed is 2
    else if (ledStripUsed == 3) {
      ledSpeaker.fill(newOffColor,0,numLedTrap);
      ledSpeaker.show();
    } // End if ledStripUsed is 3
    nextTime = millis() + newOffTime; // End time for next off-time cycle
    while (millis() < nextTime){ // LED Strip is oFF
      //Serial.printf("Time while LED strip is off: %u, \n\r",millis());
      delay(150);
    } // End while off-time
  //delay(100);
  } // End while <  End Time 
  //Serial.printf("Ending Time for Two-Color is %u secs, \n\r",int(millis()/1000));
  if (ledStripUsed == 1) {
    ledClimber.clear();
    ledClimber.show();
   } // End if ledStripUsed is 1
   else if (ledStripUsed == 2) {
      ledTrap.clear();
      ledTrap.show();
    } // End if ledStripUsed is 2
   else if (ledStripUsed == 3) {
      ledSpeaker.clear();
      ledSpeaker.show();
    } // End if ledStripUsed is 3
  //Serial.println("Ending twoColor() ");
    runTwoColor = false;
} // End twoColor

/////////////////////////////////////////////////////////////////

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
            Serial.println("Mode P 1 received: Use Climber Led Strip");
            ledStripUsed = 1;
            break;

          case 2:
            Serial.println("Mode P 2 received: Use Trap Led Strip");
            ledStripUsed = 2;
            break;

          case 3:
            Serial.println("Mode P 3 received: Use Speaker Led Strip");
            ledStripUsed = 3;
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
/////////////////////////////////////////////////////////////////



void setup() {
    Serial.begin(115200);
    delay(3000);
    ledClimber.begin();
    ledClimber.clear();
    ledClimber.setBrightness(45);

    ledTrap.begin();
    ledTrap.clear();
    ledTrap.setBrightness(45);

    ledSpeaker.begin();
    ledSpeaker.clear();
    ledSpeaker.setBrightness(45);

    delay(1000);
} // End setup()

//////////////////////////////////////////////////////////////////////
void loop() {    
  
  oneColor(ledStripUsed, currentOneColor, currentTimeout);
  delay(500);
  twoColor(ledStripUsed, currentTwoColorOn, currentTwoColorOff, currentFlashRate, currentFlashRate, currentTimeout);
  delay(500);
} // End loop()
///////////////////////////////////////////////////////////////////////////////


void setup1() {
  //delay(5000);//////////////////////////////////////ERASE THIS AFTER TESTING
  pinMode(LED_BUILTIN, OUTPUT);
  Wire.setSDA(8);
  Wire.setSCL(9);
  Wire.onReceive(recv);
  Wire.begin(0x30);
  Serial.begin(115200);
  Serial.println("setup1: I2C Scanning for input..");
}

void loop1() {
  checkInput();
}//end of loop1()


// Called when the I2C responder gets written to
void recv(int len) {
    int i;
    for (i=0; i<len; i++) buff.put(Wire.read());

    //buff.put(/*the byte we got over I2C*/);
    char_in =  true;
} // end of recv()
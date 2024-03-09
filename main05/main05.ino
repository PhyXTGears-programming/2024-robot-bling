
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
#define shortTimeout 5000
#define midTimeout 10000
#define longTimeout 15000

#define fastRate 150
#define midRate 250
#define slowRate 350

#define lowBright 125
#define midBright  170
#define highBright 255

#define picoRed ledClimber.Color(currentBrightness, 0, 0)
#define picoOrange ledClimber.Color(currentBrightness, int(0.27*currentBrightness), 0)
#define picoYellow ledClimber.Color(currentBrightness, int(0.65*currentBrightness), 0)
#define picoGreen ledClimber.Color(0, currentBrightness, 0)
#define picoBlue ledClimber.Color(0, 0, currentBrightness)
#define picoPurple ledClimber.Color(int(0.58*currentBrightness), int(0.11*currentBrightness), int(0.58*currentBrightness))
#define picoBlack ledClimber.Color(0, 0, 0)

/////////////////////////////////////////////////////////////////
// Global control parameters

int ledStripsUsed = 1;
// #1 is Climber
// #2 is Trap
// #3 is Speaker

int currentTimeout = midTimeout;
// Short Timeout; Mid Timeout; Long Timeout

int currentFlashRate = midRate;
// Slow Rate; Mid Rate; Fast Rate

int currentBrightness = midBright;
// Low Bright; Mid Bright; High Bright

bool char_in = false;

/////////////////////////////////////////////////////////////////

Adafruit_NeoPixel ledTrap(numLedTrap, ledPinTrap, NEO_GRB + NEO_KHZ800); 
Adafruit_NeoPixel ledClimber(numLedClimber, ledPinClimber, NEO_GRB + NEO_KHZ800); 
Adafruit_NeoPixel ledSpeaker(numLedSpeaker, ledPinSpeaker, NEO_GRB + NEO_KHZ800); 

/////////////////////////////////////////////////////////////////

void oneColor(int newLedStrip, int newColor, long newDuration) {
  //Serial.println("Starting oneColor() ");
  long endTime = millis() + newDuration;
  //Serial.printf("End Time is: %u, \n\r",endTime);
  //Serial.printf("Current Time is %u, \n\r",millis());
  while (millis() < endTime){
    //Serial.println("In while < endtime");
    //Serial.printf("Current Time is %u, \n\r",millis());
    if (ledStripsUsed == 1) {
      ledClimber.fill(newColor,0,numLedClimber);
      ledClimber.show();
    } // End if ledStripsUsed is 1
    else if (ledStripsUsed == 2) {
      ledTrap.fill(newColor,0,numLedTrap);
      ledTrap.show();
    } // End if ledStripsUsed is 2
    else if (ledStripsUsed == 3) {
      ledSpeaker.fill(newColor,0,numLedTrap);
      ledSpeaker.show();
    } // End if ledStripsUsed is 3
    //delay(150);
  } // End while < newTime 
  //Serial.printf("Ending Time for One-Color is %u secs, \n\r",int(millis()/1000));
  if (ledStripsUsed == 1) {
    ledClimber.clear();
    ledClimber.show();
    } // End if ledStripsUsed is 1
    else if (ledStripsUsed == 2) {
      ledTrap.clear();
      ledTrap.show();
    }  
    else if (ledStripsUsed == 3) {
      ledSpeaker.clear();
      ledSpeaker.show();
    } 
  //Serial.println("Ending oneColor() ");
} // End oneColor

/////////////////////////////////////////////////////////////////

void twoColor(int newLedStrip, uint32_t newOnColor, uint32_t newOffColor, long newOnTime, long newOffTime, long newDuration ) {
  //Serial.println("Starting twoColor() ");
  long endTime = millis() + newDuration;
  long currentTime = millis();
  long nextTime;
  //Serial.printf("End Time is: %u, \n\r",endTime);
  while (millis() < endTime){
    //Serial.println("In while < endtime");
    //Serial.printf("Current Time is %u, \n\r",millis());
    if (ledStripsUsed == 1) {
      ledClimber.fill(newOnColor,0,numLedClimber);
      ledClimber.show();
    } // End if ledStripsUsed is 1
    else if (ledStripsUsed == 2) {
      ledTrap.fill(newOnColor,0,numLedTrap);
      ledTrap.show();
    } // End if ledStripsUsed is 2
    else if (ledStripsUsed == 3) {
      ledSpeaker.fill(newOnColor,0,numLedTrap);
      ledSpeaker.show();
    } // End if ledStripsUsed is 3
    nextTime = millis() + newOnTime; // End time for next on-time cycle
    while (millis() < nextTime){ // LED Strip is on
      //Serial.printf("Time while LED strip is on: %u, \n\r",millis());
      delay(150);
    } // End while on-time
    if (ledStripsUsed == 1) {
      ledClimber.fill(newOffColor,0,numLedClimber);
      ledClimber.show();
    } // End if ledStripsUsed is 1
    else if (ledStripsUsed == 2) {
      ledTrap.fill(newOffColor,0,numLedTrap);
      ledTrap.show();
    } // End if ledStripsUsed is 2
    else if (ledStripsUsed == 3) {
      ledSpeaker.fill(newOffColor,0,numLedTrap);
      ledSpeaker.show();
    } // End if ledStripsUsed is 3
    nextTime = millis() + newOffTime; // End time for next off-time cycle
    while (millis() < nextTime){ // LED Strip is oFF
      //Serial.printf("Time while LED strip is off: %u, \n\r",millis());
      delay(150);
    } // End while off-time
  //delay(100);
  } // End while <  End Time 
  //Serial.printf("Ending Time for Two-Color is %u secs, \n\r",int(millis()/1000));
  if (ledStripsUsed == 1) {
    ledClimber.clear();
    ledClimber.show();
   } // End if ledStripsUsed is 1
   else if (ledStripsUsed == 2) {
      ledTrap.clear();
      ledTrap.show();
    } // End if ledStripsUsed is 2
   else if (ledStripsUsed == 3) {
      ledSpeaker.clear();
      ledSpeaker.show();
    } // End if ledStripsUsed is 3
  //Serial.println("Ending twoColor() ");
} // End twoColor

/////////////////////////////////////////////////////////////////

void checkInput() {
  delay(1000);
  Serial.println("Waiting for input");  

  if (char_in == true){
     //Serial.println("Char-in true");
     while (buff.hasMessage()) {
      //Serial.printf("Buff: !empty %d\r\n", buff.size());
      if (bool localStatus = buff.startsWith("m ")) {
      Serial.println("m-command received");
        buff.drop(2); // Drops the "m_"; Ready to read the integers
        int localInt1 = buff.getNumber();
        digitalWrite(LED_BUILTIN, HIGH);
        delay(veryShortTimeout);  
        digitalWrite(LED_BUILTIN, LOW);
        delay(veryShortTimeout); 
        if (localInt1 == 1){
          Serial.println("Mode M 1 received: Use Red");
          if (ledStripsUsed == 1) {
            oneColor(1,picoRed,currentTimeout);
          } // End Led Strips Used is 1
          else if (ledStripsUsed == 2){
            oneColor(2,picoRed,currentTimeout);
          } // End Led Strips Used is 2
          else if (ledStripsUsed == 3){
            oneColor(3,picoRed,currentTimeout);
          } // End Led Strips Used is 3
        } // End "M 1"
        
        else if (localInt1 == 2){
          Serial.println("Mode M 2 received: Use Yellow");
          if (ledStripsUsed == 1) {
            oneColor(1,picoYellow,currentTimeout);
          } // End Led Strips Used is 1
          else if (ledStripsUsed == 2){
            oneColor(2,picoYellow,currentTimeout);
          } // End Led Strips Used is 2
          else if (ledStripsUsed == 3){
            oneColor(3,picoYellow,currentTimeout);
          } // End Led Strips Used is 3
        } // End "M 2"
        
        else if (localInt1 == 3){
          Serial.println("Mode M 3 received: Use Green");
          if (ledStripsUsed == 1) {
            oneColor(1,picoGreen,currentTimeout);
          } // End Led Strips Used is 1
          else if (ledStripsUsed == 2){
            oneColor(2,picoGreen,currentTimeout);
          } // End Led Strips Used is 2
          else if (ledStripsUsed == 3){
            oneColor(3,picoGreen,currentTimeout);
          } // End Led Strips Used is 3
        } // End "M 3"

        else if (localInt1 == 5){
          Serial.println("Mode M 5 received: Use Orange");
          if (ledStripsUsed == 1) {
            oneColor(1,picoOrange,currentTimeout);
          } // End Led Strips Used is 1
          else if (ledStripsUsed == 2){
            oneColor(2,picoOrange,currentTimeout);
          } // End Led Strips Used is 2
          else if (ledStripsUsed == 3){
            oneColor(3,picoOrange,currentTimeout);
          } // End Led Strips Used is 3
        } // End "M 5"

        else if (localInt1 == 6){
          Serial.println("Mode M 6 received: Use Purple");
          if (ledStripsUsed == 1) {
            oneColor(1,picoPurple,currentTimeout);
          } // End Led Strips Used is 1
          else if (ledStripsUsed == 2){
            oneColor(2,picoPurple,currentTimeout);
          } // End Led Strips Used is 2
          else if (ledStripsUsed == 3){
            oneColor(3,picoPurple,currentTimeout);
          } // End Led Strips Used is 3
        } // End "M 6"

        else if (localInt1 == 11){
          Serial.println("Mode M 11 received: Use Blue Flash");
          if (ledStripsUsed == 1) {
            twoColor(1,picoBlue,picoBlack, currentFlashRate, currentFlashRate, currentTimeout);
          } // End Led Strips Used is 1
          else if (ledStripsUsed == 2){
            twoColor(2,picoBlue,picoBlack, currentFlashRate, currentFlashRate, currentTimeout);
          } // End Led Strips Used is 2
          else if (ledStripsUsed == 3){
            twoColor(3,picoBlue,picoBlack, currentFlashRate, currentFlashRate, currentTimeout);
          } // End Led Strips Used is 3
        } // End "M 11"
        else {
          Serial.printf("Unknown command received: %d\r\n", localInt1);
         }
        } // end m-command received
     else if (bool localStatus = buff.startsWith("p ")) {
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
            ledStripsUsed = 1;
            break;

          case 2:
            Serial.println("Mode P 2 received: Use Trap Led Strip");
            ledStripsUsed = 2;
            break;

          case 3:
            Serial.println("Mode P 3 received: Use Speaker Led Strip");
            ledStripsUsed = 3;
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

        } // End Case
     } // end m-command received
     else {
       //buff.drop(1);
     } // end else
     } // end while has-message is true
    } // end if char-in is true
} // End checkInput()
/////////////////////////////////////////////////////////////////



void setup() {
    //Serial.begin(115200);
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

} // End setup()

//////////////////////////////////////////////////////////////////////
void loop() {    
  checkInput();
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
  Serial.println("I2C Scanning for input..");
}

void loop1() {

}//end of loop1()


// Called when the I2C responder gets written to
void recv(int len) {
    int i;
    for (i=0; i<len; i++) buff.put(Wire.read());

    //buff.put(/*the byte we got over I2C*/);
    char_in =  true;
} // end of recv()

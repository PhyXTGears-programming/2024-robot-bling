
#include <string>
#include "RingBuffer.h"
#include <Adafruit_NeoPixel.h>

CassiusRingBuffer buff;

/////////////////////////////////////////////////////////////////
// Data Constants
#define numledClimber1 35    // Climber #1
#define numledClimber2 20    // Climber #2
#define numledTrap 36        // Trap
#define numledSpeaker 40     // Speaker

#define ledPinClimber1 16     // Climber #1 ouput pin
#define ledPinClimber2 17     // Climber #2 ouput pin
#define ledPinTrap 18         // Trap ouput pin
#define ledPinSpeaker 19      // Speaker ouput pin

#define shortTimeout 2000
#define midTimeout 3500
#define longTimeout 5000

#define fastRate 150
#define midRate 250
#define slowRate 350

#define lowBright 125
#define midBright  170
#define highBright 255

#define picoRed ledClimber1.Color(currentBrightness, 0, 0)
#define picoOrange ledClimber1.Color(currentBrightness, int(0.27*currentBrightness), 0)
#define picoYellow ledClimber1.Color(currentBrightness, int(0.65*currentBrightness), 0)
#define picoGreen ledClimber1.Color(0, currentBrightness, 0)
#define picoBlue ledClimber1.Color(0, 0, currentBrightness)
#define picoPurple ledClimber1.Color(int(0.58*currentBrightness), int(0.11*currentBrightness), int(0.58*currentBrightness))
#define picoBlack ledClimber1.Color(0, 0, 0)

/////////////////////////////////////////////////////////////////
// Global control parameters

int ledStripsUsed = 1;
// #1 is Climber1 & 2
// #2 is Trap
// #3 is Speaker

int currentTimeout = midTimeout;
// Short Timeout; Mid Timeout; Long Timeout

int currentFlashRate = midRate;
// Slow Rate; Mid Rate; Fast Rate

int currentBrightness = midBright;
// Low Bright; Mid Bright; High Bright

/////////////////////////////////////////////////////////////////

Adafruit_NeoPixel ledClimber1(numledClimber1, ledPinClimber1, NEO_GRB + NEO_KHZ800); 
Adafruit_NeoPixel ledClimber2(numledClimber2, ledPinClimber2, NEO_GRB + NEO_KHZ800); 
Adafruit_NeoPixel ledTrap(numledTrap, ledPinTrap, NEO_GRB + NEO_KHZ800); 
Adafruit_NeoPixel ledSpeaker(numledSpeaker, ledPinSpeaker, NEO_GRB + NEO_KHZ800); 

/////////////////////////////////////////////////////////////////

void oneColor(Adafruit_NeoPixel newLedStrip, int newColor, long newDuration) {
  long endTime = millis() + newDuration;
  //Serial.printf("End Time is: %u, \n\r",endTime);
  newLedStrip.fill(newColor);
  newLedStrip.show();
  while (millis() < endTime){
    //Serial.printf("Current Time is %u, \n\r",millis());
    delay(100);
  } // End while < newTime 
  newLedStrip.clear();
  newLedStrip.show();
} // End oneColor

/////////////////////////////////////////////////////////////////

void twoColor(Adafruit_NeoPixel newLedStrip, int newOnColor, int newOffColor, long newOnTime, long newOffTime, long newDuration ) {
  long endTime = millis() + newDuration;
  long currentTime = millis();
  long nextTime;
  //Serial.printf("End Time is: %u, \n\r",endTime);
  //newLedStrip.fill(newOnColor);
  //newLedStrip.show();
  while (millis() < endTime){
    newLedStrip.fill(newOnColor);
    newLedStrip.show();
    nextTime = millis() + newOnTime;
    while (millis() < nextTime){ // LED Strip is on
      //Serial.printf("Time while LED strip is on: %u, \n\r",millis());
      //delay(100);
    } // End while on-time
    newLedStrip.fill(newOffColor);
    newLedStrip.show();
    nextTime = millis() + newOffTime;
    while (millis() < nextTime){ // LED Strip is oFF
      //Serial.printf("Time while LED strip is off: %u, \n\r",millis());
      //delay(100);
    } // End while off-time
  //delay(100);
  } // End while <  End Time 
  //Serial.printf("Ending Time is %u, \n\r",millis());
  newLedStrip.clear();
  newLedStrip.show();
} // End twoColor

/////////////////////////////////////////////////////////////////

void setup() {
    Serial.begin(115200);
    delay(3000);
    ledClimber1.begin();
    ledClimber1.clear();
    //ledClimber1.setBrightness(35);

    ledClimber2.begin();
    ledClimber2.clear();
    //ledClimber2.setBrightness(35);
    
    ledTrap.begin();
    ledTrap.clear();
    //ledTrap.setBrightness(35);
    
    ledSpeaker.begin();
    ledSpeaker.clear();
    //ledSpeaker.setBrightness(35);

} // End setup()

//////////////////////////////////////////////////////////////////////
void loop() {    

delay(20);
} // End loop()
///////////////////////////////////////////////////////////////////////////////


void setup1() {
  //delay(5000);//////////////////////////////////////ERASE THIS AFTER TESTING
  Wire.setSDA(8);
  Wire.setSCL(9);
  Wire.setClock(100000);
  Wire.onReceive(recv);
  Wire.begin(0x30);
  Serial.begin(115200);
  Serial.println("I2C Scanning for input..");
}

bool char_in = false;
void loop1() {
  delay(1000);
  Serial.println("Waiting for input");  
  //char data = ((char)buff.get()); 

  // Print out string from controller
    
  if (char_in == true){
    Serial.println("char_in is true");
    while (!buff.isEmpty() && !buff.isFull()) {
      //Serial.print((char)buff.get());
      //Serial.printf("Buff: %c \r\n", (char)buff.get());
      //Serial.print("\r\n");
      if (bool localStatus = buff.startsWith("m ")) {
        //Serial.println("m_xx found");
        buff.drop(2);
        int localInt1 = buff.getNumber();
        if (localInt1 == 1){
          Serial.println("Mode M 1 received");
          if (ledStripsUsed == 1) {
            oneColor(ledClimber1,picoRed,currentTimeout);
          } // End Led Strips Used is 1
          else if (ledStripsUsed == 2){
            oneColor(ledTrap,picoRed,currentTimeout);
          } // End Led Strips Used is 2
          else if (ledStripsUsed == 3){
            oneColor(ledSpeaker,picoRed,currentTimeout);
          } // End Led Strips Used is 3
        } // End "M 1"
        
        else if (localInt1 == 2){
          Serial.println("Mode M 2 received");
          if (ledStripsUsed == 1) {
            oneColor(ledClimber1,picoYellow,currentTimeout);
          } // End Led Strips Used is 1
          else if (ledStripsUsed == 2){
            oneColor(ledTrap,picoYellow,currentTimeout);
          } // End Led Strips Used is 2
          else if (ledStripsUsed == 3){
            oneColor(ledSpeaker,picoYellow,currentTimeout);
          } // End Led Strips Used is 3
        } // End "M 2"
        
        else if (localInt1 == 3){
          Serial.println("Mode M 3 received");
          if (ledStripsUsed == 1) {
            oneColor(ledClimber1,picoGreen,currentTimeout);
          } // End Led Strips Used is 1
          else if (ledStripsUsed == 2){
            oneColor(ledTrap,picoGreen,currentTimeout);
          } // End Led Strips Used is 2
          else if (ledStripsUsed == 3){
            oneColor(ledSpeaker,picoGreen,currentTimeout);
          } // End Led Strips Used is 3
        } // End "M 3"

        else if (localInt1 == 5){
          Serial.println("Mode M 5 received");
          if (ledStripsUsed == 1) {
            oneColor(ledClimber1,picoOrange,currentTimeout);
          } // End Led Strips Used is 1
          else if (ledStripsUsed == 2){
            oneColor(ledTrap,picoOrange,currentTimeout);
          } // End Led Strips Used is 2
          else if (ledStripsUsed == 3){
            oneColor(ledSpeaker,picoOrange,currentTimeout);
          } // End Led Strips Used is 3
        } // End "M 5"


        else if (localInt1 == 6){
          Serial.println("Mode M 6 received");
          if (ledStripsUsed == 1) {
            oneColor(ledClimber1,picoPurple,currentTimeout);
          } // End Led Strips Used is 1
          else if (ledStripsUsed == 2){
            oneColor(ledTrap,picoPurple,currentTimeout);
          } // End Led Strips Used is 2
          else if (ledStripsUsed == 3){
            oneColor(ledSpeaker,picoPurple,currentTimeout);
          } // End Led Strips Used is 3
        } // End "M 6"
        
        else if (localInt1 == 11){
          Serial.println("Mode M 11 received");
          if (ledStripsUsed == 1) {
            twoColor(ledClimber1,picoBlue,picoBlack, currentFlashRate, currentFlashRate, currentTimeout);
          } // End Led Strips Used is 1
          else if (ledStripsUsed == 2){
            twoColor(ledTrap,picoBlue,picoBlack, currentFlashRate, currentFlashRate, currentTimeout);
          } // End Led Strips Used is 2
          else if (ledStripsUsed == 3){
            twoColor(ledSpeaker,picoBlue,picoBlack, currentFlashRate, currentFlashRate, currentTimeout);
          } // End Led Strips Used is 3
        } // End "M 11"
        } // end if "m_xx found"
     else if (bool localStatus = buff.startsWith("p ")) {
        //Serial.println("p_xx found");
        buff.drop(2);
        int localInt2 = buff.getNumber();
        if (localInt2 == 31){
          Serial.println("Mode P 31 received");
          currentTimeout = shortTimeout;
        } // End "P 31"
        else if (localInt2 == 32){
          Serial.println("Mode P 32 received");
          currentTimeout = midTimeout;
        } // End "P 32"
        else if (localInt2 == 33){
          Serial.println("Mode P 33 received");
          currentTimeout = longTimeout;
        } // End "P 33"
        else if (localInt2 == 21){
          Serial.println("Mode P 21 received");
          currentFlashRate = slowRate;
        } // End "P 21"
        else if (localInt2 == 22){
          Serial.println("Mode P 22 received");
          currentFlashRate = midRate;
        } // End "P 22"
        else if (localInt2 == 23){
          Serial.println("Mode P 23 received");
          currentFlashRate = fastRate;
        } // End "P 23"
        else if (localInt2 == 11){
          Serial.println("Mode P 11 received");
          currentBrightness = lowBright;
        } // End "P 11"
        else if (localInt2 == 12){
          Serial.println("Mode P 12 received");
          currentBrightness = midBright;
        } // End "P 12"
        else if (localInt2 == 13){
          Serial.println("Mode P 13 received");
          currentBrightness = highBright;
        } // End "P 13"

        
     } // end if "p_xx found"
     else {
        buff.drop(2);
     }
     } // end if buff not empty
    }// end of if char_in = true
    }//end of loop1()


// Called when the I2C responder gets written to
void recv(int len) {
    int i;
    for (i=0; i<len; i++) {
      delay(10);
      buff.put(Wire.read());
    }
    char_in =  true;

} // end of recv()

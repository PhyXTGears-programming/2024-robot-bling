#include <string>
#include "RingBuffer.h"
#include <Adafruit_NeoPixel.h>

CassiusRingBuffer buff;

/////////////////////////////////
// Data Constants
#define numLedClimber 35    // # of Climber Leds
#define numLedTrap 36       // # of Trap Leds
#define numLedSpeaker 40    // # of Speaker Leds

#define ledPinClimber 16    // Climber ouput pin
#define ledPinTrap 20       // Trap ouput pin
#define ledPinSpeaker 19    // Speaker ouput pin

#define shortTimeout 6000
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

/////////////////////////////////
// Global control parameters

int ledStripsUsed = 1;
// #1 is Climber
// #2 is Trap
// #3 is Speaker

int currentTimeout = midTimeout;
// Short TimeOut; Mid TimeOut; Long TimeOut

int currentFlashRate = midRate;
// Slow Rate; Mid Rate; Fast Rate

int currentBrightness = midBright;
// Low Bright; Mid Bright; High Bright

/////////////////////////////////

Adafruit_NeoPixel ledTrap = Adafruit_NeoPixel(numLedTrap, ledPinTrap, NEO_GRB + NEO_KHZ800); 

Adafruit_NeoPixel ledClimber = Adafruit_NeoPixel(numLedClimber, ledPinClimber, NEO_GRB + NEO_KHZ800); 

Adafruit_NeoPixel ledSpeaker = Adafruit_NeoPixel(numLedSpeaker, ledPinSpeaker, NEO_GRB + NEO_KHZ800); 

/////////////////////////////////

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
    }
    else if (ledStripsUsed == 2) {
      ledTrap.fill(newColor,0,numLedTrap);
      ledTrap.show();
    }    
    delay(150);
  } // End while < newTime 
  Serial.printf("Ending Time for One-Color is %u secs, \n\r",int(millis()/1000));
  if (ledStripsUsed == 1) {
    ledClimber.clear();
    ledClimber.show();
    }
    else if (ledStripsUsed == 2) {
      ledTrap.clear();
      ledTrap.show();
    }  
  //Serial.println("Ending oneColor() ");
} // End oneColor

/////////////////////////////////

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
    }
    else if (ledStripsUsed == 2) {
      ledTrap.fill(newOnColor,0,numLedTrap);
      ledTrap.show();
    }
    nextTime = millis() + newOnTime;
    while (millis() < nextTime){ // LED Strip is on
      //Serial.printf("Time while LED strip is on: %u, \n\r",millis());
      delay(150);
    } // End while on-time
    if (ledStripsUsed == 1) {
      ledClimber.fill(newOffColor,0,numLedClimber);
      ledClimber.show();
    }
    else if (ledStripsUsed == 2) {
      ledTrap.fill(newOffColor,0,numLedTrap);
      ledTrap.show();
    }
    nextTime = millis() + newOffTime;
    while (millis() < nextTime){ // LED Strip is oFF
      //Serial.printf("Time while LED strip is off: %u, \n\r",millis());
      delay(150);
    } // End while off-time
  //delay(100);
  } // End while <  End Time 
  Serial.printf("Ending Time for Two-Color is %u secs, \n\r",int(millis()/1000));
  if (ledStripsUsed == 1) {
    ledClimber.clear();
    ledClimber.show();
   }
   else if (ledStripsUsed == 2) {
      ledTrap.clear();
      ledTrap.show();
    }     
  //Serial.println("Ending twoColor() ");
} // End twoColor

/////////////////////////////////

void setup() {

    //Serial.begin(115200);
    delay(3000);
    ledClimber.begin();
    ledClimber.clear();
    ledClimber.setBrightness(35);

    ledTrap.begin();
    ledTrap.clear();
    ledTrap.setBrightness(35);
    
    ledSpeaker.begin();
    ledSpeaker.clear();
    ledSpeaker.setBrightness(35);

} // End setup()

////////////////////////////////////
void loop() {    

delay(20);
} // End loop()
/////////////////////////////////////////


void setup1() {
  //delay(5000);////////////////////ERASE THIS AFTER TESTING
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
  //Serial.println("Waiting for input");  
  //char data = ((char)buff.get()); 

  // Print out string from controller
    
  if (char_in == true){
    //Serial.println("char_in is true");
    while (!buff.isEmpty() && !buff.isFull()) {
      //Serial.print((char)buff.get());
      //Serial.printf("Buff: %c \r\n", (char)buff.get());
      //Serial.print("\r\n");
      if (bool localStatus = buff.startsWith("m ")) {
        //Serial.println("m_xx found");
        buff.drop(2);
        int localInt1 = buff.getNumber();
        //buff.drop(2);
        if (localInt1 == 1){
          //Serial.println("Mode M 1 received: Red");
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
          //Serial.println("Mode M 2 received: Yellow");
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
          //Serial.println("Mode M 3 received: Green");
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
          //Serial.println("Mode M 5 received: Orange");
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
          //Serial.println("Mode M 6 received: Purple");
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
          //Serial.println("Mode M 11 received: Flashing Blue");
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
        } // end if "m_xx found"
        
     else if (bool localStatus = buff.startsWith("p ")) {
        //Serial.println("p_xx found");
        buff.drop(2);
        int localInt2 = buff.getNumber();
        if (localInt2 == 31){
          //Serial.println("Mode P 31 received: Short Timeout");
          currentTimeout = shortTimeout;
        } // End "P 31"
        else if (localInt2 == 32){
          //Serial.println("Mode P 32 received: Mid Timeout");
          currentTimeout = midTimeout;
        } // End "P 32"
        else if (localInt2 == 33){
          //Serial.println("Mode P 33 received: Long Timeout");
          currentTimeout = longTimeout;
        } // End "P 33"
        else if (localInt2 == 21){
          //Serial.println("Mode P 21 received: Slow Flash Rate");
          currentFlashRate = slowRate;
        } // End "P 21"
        else if (localInt2 == 22){
          //Serial.println("Mode P 22 received: Mid Flash Rate");
          currentFlashRate = midRate;
        } // End "P 22"
        else if (localInt2 == 23){
          //Serial.println("Mode P 23 received: Fast Flash Rate");
          currentFlashRate = fastRate;
        } // End "P 23"
        else if (localInt2 == 11){
          //Serial.println("Mode P 11 received: Low Brightness");
          currentBrightness = lowBright;
          } // End "P 11"
        else if (localInt2 == 12){
          //Serial.println("Mode P 12 received: Mid Brightness");
          currentBrightness = midBright;
          } // End "P 12"
        else if (localInt2 == 13){
          //Serial.println("Mode P 13 received: High Brightness");
          currentBrightness = highBright;
        } // End "P 13"
        else if (localInt2 == 1){
          //Serial.println("Mode P 1 received: Climber Led Strip");
          ledStripsUsed = 1;
        } // End "P 1"
        else if (localInt2 == 2){
          //Serial.println("Mode P 2 received: Trap Led Strip");
          ledStripsUsed = 2;
        } // End "P 2"
        else if (localInt2 == 3){
          //Serial.println("Mode P 1 received: Climber Led Strip");
          ledStripsUsed = 3;
        } // End "P 3"
     } // end if "p_xx found"
     else {
        //buff.drop(3);
     } // End else
     } // End if buff not empty
    } // End of if char_in = true
    } //end of loop1()


// Called when the I2C responder gets written to
void recv(int len) {
    int i;
    for (i=0; i<len; i++) {
      buff.put(Wire.read());
      } // End for
    
    char_in =  true;

} // end of recv()


#include <string>
#include <Adafruit_NeoPixel.h>



/////////////////////////////////////////////////////////////////
// Data Constants
#define numLedBase 45    // # of Base Leds
#define numLedFront 10    // # of Front Leds
#define numLedRear 10    // # of Rear Leds

#define ledPinFront 16    // Front output pin
#define ledPinRear 18    // Rear output pin
#define ledPinBase 20    // Base output pin
#define controlPin 21    // Base output pin
#define HeartbeatPin 28 // Heartbeat output pin

#define veryShortTimeout 200
#define shortTimeout 500
#define midTimeout 1000
#define longTimeout 5000

#define fastRate 150
#define midRate 250
#define slowRate 350

#define lowBright 125
#define midBright  170
#define highBright 255

/////////////////////////////////////////////////////////////////
Adafruit_NeoPixel ledBase(numLedBase, ledPinBase, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel ledFront(numLedFront, ledPinFront, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel ledRear(numLedRear, ledPinRear, NEO_GRB + NEO_KHZ800);

#define picoRed ledBase.Color(currentBrightness, 0, 0)
#define picoOrange ledBase.Color(currentBrightness, int(0.27*currentBrightness), 0)
#define picoYellow ledBase.Color(currentBrightness, int(0.65*currentBrightness), 0)
#define picoGreen ledBase.Color(0, currentBrightness, 0)
#define picoBlue ledBase.Color(0, 0, currentBrightness)
#define picoPurple ledBase.Color(int(0.58*currentBrightness), int(0.11*currentBrightness), int(0.58*currentBrightness))
#define picoWhite ledBase.Color(int(1.0*currentBrightness), int(1.0*currentBrightness), int(1.0*currentBrightness))
#define picoBlack ledBase.Color(0, 0, 0)

/////////////////////////////////////////////////////////////////
// Global control parameters

int ledStripUsed = 1;
// #1 is Base

int currentTimeout = midTimeout;
// Short Timeout; Mid Timeout; Long Timeout

int currentFlashRate = midRate;
// Slow Rate; Mid Rate; Fast Rate

int currentBrightness = highBright;
// Low Bright; Mid Bright; High Bright

int currentOneColor = picoRed;
int currentTwoColorOn = picoGreen;
int currentTwoColorOff = picoBlack;

bool runOneColor = false; // Controls running of OneColor()
bool runTwoColor = false; // Controls running of TwoColor()
bool flashControl = false; // Controls flashing of base

/////////////////////////////////////////////////////////////////

void blinkLed() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(200);
  digitalWrite(LED_BUILTIN, LOW);
}

void heartBeat() {
  digitalWrite(HeartbeatPin, LOW);
  delay(50); 
  digitalWrite(HeartbeatPin, HIGH); 
  delay(500); 
}
void clearAll(){
  //Serial.println("Clear All");
  runOneColor = false;
  runTwoColor = false;
  ledBase.clear();
  delay(100);
  ledBase.show();
}
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
    nextTime = millis() + newOnTime; // End time for next on-time cycle
    while (millis() < nextTime){ // LED Strip is on
      //Serial.printf("Time while LED strip is on: %u, \n\r",millis());
      delay(150);
    } // End while on-time
    if (ledStripUsed == 1) {
      ledBase.fill(newOffColor,0,numLedBase);
      ledBase.show();
    } // End if ledStripUsed is 1
    nextTime = millis() + newOffTime; // End time for next off-time cycle
    while (millis() < nextTime){ // LED Strip is oFF
      //Serial.printf("Time while LED strip is off: %u, \n\r",millis());
      delay(150);
    } // End while off-time
  } // End while <  End Time 
  //Serial.printf("Ending Time for Two-Color is %u secs, \n\r",int(millis()/1000));
  if (ledStripUsed == 1) {
    ledBase.clear();
    ledBase.show();
   } // End if ledStripUsed is 1
  //Serial.println("Ending twoColor() ");
    runTwoColor = false;
} // End twoColor

/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////

void setup() {
    Serial.begin(115200);
    delay(3000);
    ledBase.begin();
    ledBase.clear();
    ledBase.setBrightness(45);

    ledFront.begin();
    ledFront.clear();
    ledFront.setBrightness(65);
    ledFront.fill(picoWhite,0,numLedFront);
    ledFront.show();

    ledRear.begin();
    ledRear.clear();
    ledRear.setBrightness(65);
    ledRear.fill(picoRed,0,numLedRear);
    ledRear.show();

    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(HeartbeatPin, OUTPUT);
    pinMode(controlPin, INPUT_PULLUP);
    delay(500);
} // End setup()

//////////////////////////////////////////////////////////////////////
void loop() {    
  twoColor(ledStripUsed, currentTwoColorOn, currentTwoColorOff, currentFlashRate, currentFlashRate, currentTimeout);
  delay(100);
  heartBeat();
  checkControl();
  
} // End loop()
///////////////////////////////////////////////////////////////////////////////

void checkControl(){
  bool inputState = digitalRead(controlPin);
  if (inputState == LOW){
    delay(100);
    inputState = digitalRead(controlPin);
    if (inputState == LOW){
          runTwoColor = true;
          Serial.println("Flash Base Command Received");
    } // End input low confirmed
    else {
      // Do nothing; input low not confiremd
    }
  } // End if input low
  else{
    runTwoColor = false;
  } // //End input is high
} // End check control
          

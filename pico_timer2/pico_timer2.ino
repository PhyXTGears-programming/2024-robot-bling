
#include <iostream>
#include "FastLED.h"

#define COLOR_ORDER GRB      // make the order RGB
#define NUM_LEDS 30          //30 LEDs on the strip
#define BRIGHTNESS 50        //LED brightness
#define ledPin1 16          // Led Strip 1 ouput pin
#define ledPin2 17          // Led Strip 2 ouput pin
#define ledPin3 18          // Led Strip 3 ouput pin
#define ledPin4 19          // Led Strip 4 ouput pin
#define LED_TYPE WS2811  


//#########################################################################
class LedTimer {
  // Class Member Variables
  // These filled at init
  public:
  String timerLabel;  // Name of timer for use print statements
  bool timerStatus;   // State used to enable timer
    
  // These are initialized in Setup()
  bool timerRepeat;   // Set True if timer repeats
  long onTime;     // milliseconds of on-time
  long offTime;    // milliseconds of off-time

  // These maintain the current state
  unsigned long previousMillis; // will store last time change was made
  bool timerOnOff;              // True when timer is in on-time
  

  // Constructor - creates a LedTimer and initializes some member variables and state
  public:
  /*
  LedTimer(bool startStatus, String newLabel){
    timerStatus = startStatus;
    timerLabel = newLabel;
  */
  LedTimer(){
  }

  void timerSetup(bool newStatus, bool newRepeat, int newOnTime, int newOffTime){
    previousMillis = millis();
    onTime = newOnTime;
    offTime = newOffTime;
    timerStatus = newStatus;
    timerRepeat = newRepeat;
    Serial.begin(115200);
    delay(3000);
    Serial.printf("Status: %s, On time: %d ms, Off time: %d ms \n", timerStatus, onTime,offTime);
  } // End of Setup() function
  
  void timerUpdate(bool remoteUpdate) {
    // check to see if it's time to make a change
    unsigned long currentMillis = millis();
     
    //Check if timer on-time is expired
    if((timerStatus == true) && (timerOnOff == true) && (currentMillis - previousMillis >= onTime))
    {
      if (timerRepeat == true){
        previousMillis = currentMillis;  // Remember the time
        timerOnOff = false;
        remoteUpdate = timerOnOff;
        Serial.printf("Finished on-time \n");
      }
      else {
        timerStatus = false;
      }
    } // End Timer On

    //Check if timer off-time is expired
    else if ((timerStatus == true) && (timerOnOff == false) && (currentMillis - previousMillis >= offTime))
    {
      timerOnOff = true;
      remoteUpdate = timerOnOff;
      Serial.printf("Finished off-time \n");
    } 
  } // End of Update() function
}; //End of LedTimer Class

//#########################################################################

class LedStrip: public CLEDController {
  // Class Member Variables
  // These filled at init
  int ledPin;          // Pin where LED strip connects
  int stringLength;    // Length of LED strip
        
  // These are initialized in stripSetup()
  public:
  CRGB onColor;
  CRGB offColor;

  // Other
  int onTime;
  int offTime;
  //bool timerOnOff;

  // Constructor - creates a ledStrip and initializes some member variables
  public:
  LedStrip(int LedPin, int StringLength){
    ledPin = LedPin;
    stringLength = StringLength;
    init();
  }

  void stripSetup(CRGB color1, CRGB color2){
    onColor = color1;
    offColor = color2;
   }

  void stripUpdate(bool stripOnOff){
    if (stripOnOff == true){
      showColor(offColor,NUM_LEDS,BRIGHTNESS);
    }
    else{
      showColor(onColor,NUM_LEDS,BRIGHTNESS);
    }
  }

}; // End ledStrip Class

//#########################################################################

bool ledStripOnOff1 = true;
LedStrip ledStrip1(ledPin1, NUM_LEDS);
ledStrip1.addLeds<LED_TYPE, ledPin1, COLOR_ORDER> (new CRGB[10], NUM_LEDS).setCorrection(TypicalLEDStrip);
ledStrip1.stripSetup(CRGB::Red, CRGB::Blue);
//#########################################################################
LedTimer ledTimer1(false,"LED 1 String");
ledTimer1.timerSetup(true, true, 500, 750):
//#########################################################################

//CLEDController& controller1 = FastLED.addLeds<LED_TYPE, ledPin1, COLOR_ORDER> (new CRGB[10], NUM_LEDS).setCorrection(TypicalLEDStrip);

void setup()
{
    //Serial.begin(115200);
    //Serial.println(controller.size());


}
//led1.Setup(true,true,10000,10000);


void loop()
{
  ledTimer1.timerUpdate(ledStripOnOff1);
  ledStrip1.stripUpdate(ledStripOnOff1);  
}


#include "FastLED.h"
volatile String robotCommand;
#define COLOR_ORDER GRB             // make the order RGB
#define NUM_LEDS_STRIP_1 30          // 30 LEDs on strip 1
#define NUM_LEDS_STRIP_2 30          // 30 LEDs on strip 2
#define BRIGHTNESS 75               // LED brightness
#define LED_PIN_STRIP_1 16           // LED strip 1 output pin
#define LED_TYPE   WS2811

class ledTimer {
  // Class Member Variables
  // These filled at init
  String timerLabel;  // Name of timer for use print statements
  bool timerStatus;   // State used to enable timer
    
  // These are initialized in Setup()
  bool timerRepeat;   // Set True if timer repeats
  long OnTime;     // milliseconds of on-time
  long OffTime;    // milliseconds of off-time

  // These maintain the current state
  unsigned long previousMillis; // will store last time change was made
  bool timerOnOff;              // True when timer is in on-time
  
  // Constructor - creates a ledTimer and initializes some member variables
  public:
  //ledTimer(bool startStatus, String newLabel){
  ledTimer(){
    //timerStatus = false;
    //timerLabel = newLabel;
  }

  void Setup(bool newStatus, bool newRepeat, int newOnTime, int newOffTime){
    previousMillis = millis();
    OnTime = newOnTime;
    OffTime = newOffTime;
    timerStatus = newStatus;
    timerRepeat = newRepeat;
    Serial.begin(115200);
    delay(3000);
    Serial.printf("Status: %s, On time: %d ms, Off time: %d ms \n", timerStatus, OnTime,OffTime);
  } // End of Setup() function
  
  void Update() {
    // check to see if it's time to make a change
    unsigned long currentMillis = millis();
     
    //Check if timer on-time is expired
    if((timerStatus == true) && (timerOnOff == true) && (currentMillis - previousMillis >= OnTime))
    {
      if (timerRepeat == true){
        previousMillis = currentMillis;  // Remember the time
        timerOnOff = false;
        Serial.printf("Finished on-time \n");
      }
      else {
        timerStatus = false;
      }
    } // End Timer On

    //Check if timer off-time is expired
    else if ((timerStatus == true) && (timerOnOff == false) && (currentMillis - previousMillis >= OffTime))
    {
      timerOnOff = true;
      Serial.printf("Finished off-time \n");
    }
  } // End of Update() function
}; //End of ledTimer Class

class ledStrip: CLEDController, ledTimer {
//class ledStrip: CFastLED, ledTimer {
  // Class Member Variables
  // These filled at init
  int ledPin;         // Hardware pin for the LED strip
  int stripLength;    // Number of LEDs in the strip
  CRGB ledColor;         // RGB color used in LED Strip
  

  // Constructor - creates a ledStrip and initializes some member variables
  public:
  ledStrip(int LedPin, int StripLength){
    ledPin = LedPin;
    stripLength = StripLength;
    //ledTimer::ledTimer(true,true,1000,1000);
  }

  void Setup(CRGB *LedColor, int Brightness, int OnTime, int OffTime){
  //ledColor = LedColor;
//  CFastLED::setLeds(ledColor, 30, 0);
  CLEDController::setLeds(LedColor, 30);
  //CLEDController::setBrightness (Brightness);
  CFastLED::setBrightness (Brightness);
  //ledTimer
  }
  
  
};

void checkCommand (){
  // switch statements
  switch (robotCommand) {
  case 'c 0':
    Serial.printf("Command C0 recevied\n");
    // Set LED1 to green
    break;
  case 'c 1':
    Serial.printf("Command C1 recevied\n");
    // Set LED1 to flash green on/off 1 times per second
     break;
  case 'c 2':
    Serial.printf("Command C1 recevied\n");
    // Set LED1 to flash red/green 1 times per second
     break;
  } // End switch 
} // End checkCommand()


ledStrip(LED_PIN_STRIP_1, NUM_LEDS_STRIP_1);
//ledTimer ledtimer1(false,"LED 1 String");

void setup()
{

ledtimer1.Setup(true,true,10000,10000);
}

void loop()
{
  ledtimer1.Update();
}

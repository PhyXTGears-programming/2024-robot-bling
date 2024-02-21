
//#include <iostream>
#include <FastLED.h>
//#include <functional>
#include <array>

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
    
  // These are initialized in Setup()
  long onTime;     // milliseconds of on-time
  long offTime;    // milliseconds of off-time
  long endTime;   // elapsed time when timer will stop

  // These maintain the current state
  unsigned long previousTime; // will store last time change was made
  unsigned long currentTime; // will store current time
  bool timerOnOff;            // True when timer is in on-time (Repeat mode)
  bool timerStatus = false;   // State used to enable timer  

  // Constructor - creates an LedTimer and initializes some member variables
  public:
  LedTimer(String newLabel){
    timerLabel = newLabel;
  } // End Create Timer
  void timerRepeatSetup(int newOnTime, int newOffTime, int newRunTime){
    onTime = newOnTime;
    offTime = newOffTime;
    timerStatus = true;
    previousTime = millis();
    endTime = previousTime + newRunTime;
  } // End of timerRepeatSetup()

  bool timerRepeatUpdate() {
    // check to see if it's time to make a change
    currentTime = millis();
    if ((currentTime <= endTime) && (timerStatus == true) ){
	  //Check if timer on-time is expired    
	  if((timerOnOff == true) && (currentTime - previousTime >= onTime)) {
        previousTime = currentTime;  // Remember the time
        timerOnOff = false;
        Serial.printf("Finished on-time (timerRepeatUpdate) \n");
     } // End check on-time
      //Check if timer off-time is expired
      currentTime = millis();
     if ((timerStatus == true) && (timerOnOff == false) && (currentTime - previousTime >= offTime)) {
        previousTime = currentTime;  // Remember the time
        timerOnOff = true;
        Serial.printf("Finished off-time (timerRepeatUpdate) \n");
     } // End check off-time
      return timerOnOff;
    } // End if <= End time
    else {
      timerStatus = false;
      return false;
    } // End Else
  } // End of Update() function

  void timerOnceSetup(int newRunTime){
    previousTime = millis();
    endTime = previousTime + newRunTime;
	timerStatus = true;
  } // End of timerOnceSetup()

  bool timerOnceUpdate(){
    currentTime = millis();
    if ((currentTime <= endTime) && (timerStatus == true)) {
      Serial.printf("In on-time (timerOnceUpdate) \n");
      delay(500);
      return true;
	  } // End if
    else {
      timerStatus = false;
  	  Serial.printf("Finish time (timerOnceUpdate) \n");
  	  return false;
    } // End Else
  } // End of timerOnceUpdate()

}; //End of LedTimer Class


LedTimer ledTimer1("LED 1 String");
CLEDController& controller1 = FastLED.addLeds<LED_TYPE, ledPin1, COLOR_ORDER> (new CRGB[10], NUM_LEDS).setCorrection(TypicalLEDStrip);


void setupLeds(int newMode){
  bool runTimer = true;
  bool ledStripOnOff1 = true;
  controller1.showColor(CRGB::Black, 30, 45);
  if (newMode == 4){
      ledTimer1.timerOnceSetup(15000);
      Serial.println("ledStripOnOff1 is: True (setupLeds)");
      controller1.showColor(CRGB::Blue, 8, 45);
      while (runTimer == true){
        ledStripOnOff1 = ledTimer1.timerOnceUpdate();
        if (ledStripOnOff1 == false){
          Serial.println("ledStripOnOff1 is: False (setupLeds)");
          runTimer = false;
          controller1.showColor(CRGB::Blue, 8, 0);
        } // End if
      } // End while loop
    delay(100);
  } // End mode 4
  if (newMode == 5){
    ledTimer1.timerRepeatSetup(450, 450, 15000);
    while (runTimer == true){
      ledStripOnOff1 = ledTimer1.timerRepeatUpdate();
      if (ledStripOnOff1 == false){
        Serial.println("ledStripOnOff1 is: False (setupLeds)");
        controller1.showColor(CRGB::Blue, 8, 0);
      }
      else {
        Serial.println("ledStripOnOff1 is: True (SetupLEDS)");
        controller1.showColor(CRGB::Blue, 8, 45);    
      }
    delay(100);
    } // End While loop
  } // End mode 5
} // End setupLeds

void setup() {
    Serial.begin(115200);
    //controller1.showColor(CRGB::Black, 30, 45);
    //ledTimer1.timerRepeatSetup(true, true, 427, 427);

}

void loop()
{
 /*
  ledStripOnOff1 = ledTimer1.timerUpdate();
  if (ledStripOnOff1 == true){
    Serial.println("ledStripOnOff1 is: True");
    controller1.showColor(CRGB::Blue, 8, 45);
  }
  else {
    Serial.println("ledStripOnOff1 is: False");
    controller1.showColor(CRGB::Red, 8, 45);    
  }
  delay(100);
  */
  //setupLeds(5);
  //delay(5000);
  setupLeds(4);
}

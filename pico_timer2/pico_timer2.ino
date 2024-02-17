
#include <iostream>
#include "FastLED.h"

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
  
  // Constructor - creates a ledTimer and initializes some member variables and state
  public:
  ledTimer(bool startStatus, String newLabel){
    timerStatus = startStatus;
    timerLabel = newLabel;
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



ledTimer led1(false,"LED 1 String");

void setup()
{
led1.Setup(true,true,10000,10000);
}

void loop()
{
  led1.Update();
}

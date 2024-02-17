
#include "FastLED.h"

class ledStrip(CRGB)
{
  // Class Member Variables
  // These are initialized in Setup()
  int ledPin;      // the number of the LED pin
  long OnTime;     // milliseconds of on-time
  long OffTime;    // milliseconds of off-time

  // These maintain the current state
  bool timerStatus;               // State used to enable timer
  int ledState;                 // ledState used to set the LED
  unsigned long previousMillis;   // will store last time change was made
  
  // Constructor - creates a Flasher and initializes the member variables and state
  public:
  ledStrip(bool startStatus, int pin) {
    timerStatus = startStatus;
    ledPin = pin;
    pinMode(ledPin, OUTPUT);
  }

  void Setup(bool newStatus, int newOnTime, int newOffTime){
    previousMillis = millis();
    OnTime = newOnTime;
    OffTime = newOffTime;
    timerStatus = newStatus;
    Serial.begin(115200);
    Serial.printf("Status: %s, On time: %d ms, Off time: %d ms \n", timerStatus, OnTime,OffTime);
  } // End of Setup() function
  
  /*
  void Update() {
    // check to see if it's time to change the state of the LED
    unsigned long currentMillis = millis();
     
    if((timerStatus == true) && (ledState == HIGH) && (currentMillis - previousMillis >= OnTime))
    {
      // Turn it off
      ledState = LOW;  // Turn it off
      previousMillis = currentMillis;  // Remember the time
      digitalWrite(ledPin, ledState);  // Update the actual LED
      Serial.printf("Turn off the LED \n");
    }
    else if ((timerStatus == true) && (ledState == LOW) && (currentMillis - previousMillis >= OffTime))
    {
      // turn it on
      ledState = HIGH;  // Turn it off
      previousMillis = currentMillis;   // Remember the time
      digitalWrite(ledPin, ledState);   // Update the actual LED
      Serial.printf("Turn on the LED \n");
    }
  } // End of Update() function
*/

}; //End of ledStrip Class



ledStrip led1(false,LED_BUILTIN);

void setup()
{
led1.Setup(true,1000,2000);
}

void loop()
{
  led1.Update();
}

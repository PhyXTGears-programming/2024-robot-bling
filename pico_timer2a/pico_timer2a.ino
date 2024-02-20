
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
#define ARRAY_LED1 101
#define ARRAY_LED2 102
#define ARRAY_LED3 103
#define ARRAY_LED4 104

#define ARRAY_RED   111
#define ARRAY_GREEN 112
#define ARRAY_BLUE  113
#define ARRAY_YELLOW 114

#define ARRAY_ON 121
#define ARRAY_OFF 122

std::array<int,4> array1{ARRAY_LED1, ARRAY_RED, ARRAY_ON, 0};
std::array<int,4> array2{ARRAY_LED1, ARRAY_GREEN, ARRAY_ON, 0};
std::array<int,4> array3{ARRAY_LED1, ARRAY_BLUE, ARRAY_ON, 0};
std::array<int,4> array4{ARRAY_LED1, ARRAY_YELLOW, ARRAY_ON, 0};
std::array<int,4> array5{ARRAY_LED1, ARRAY_RED, 450, 450};


//#########################################################################
class LedTimer {
  // Class Member Variables
  // These filled at init
  public:
  String timerLabel;  // Name of timer for use print statements
    
  // These are initialized in Setup()
  bool timerRepeat;   // Set True if timer repeats
  long onTime;     // milliseconds of on-time
  long offTime;    // milliseconds of off-time
  long endTime;   // eleapsed time when timer will stop

  // These maintain the current state
  unsigned long previousTime; // will store last time change was made
  bool timerOnOff;            // True when timer is in on-time
  bool timerStatus = false;   // State used to enable timer  

  // Constructor - creates a LedTimer and initializes some member variables and state
  public:
  LedTimer(String newLabel){
    timerLabel = newLabel;
  }
  void timerRepeatSetup(bool newStatus, int newOnTime, int newOffTime, int newRunTime){
    onTime = newOnTime;
    offTime = newOffTime;
    timerStatus = newStatus;
    previousTime = millis();
    endTime = previousTime + newRunTime;
  } // End of timerRepeatSetup()

  void timerOnceSetup(int newRunTime){
    previousTime = millis();
    endTime = previousTime + newRunTime;
  } // End of timerOnceSetup()

  bool timerOnceUpdate(){
    unsigned long currentTime;
    currentTime = millis();
    if ((currentTime >= endTime)) {
      return true;
    } // End if
    else
      return false;
  } // End of timerOnceUpdate()
  
  bool timerRepeatUpdate() {
    // check to see if it's time to make a change
    unsigned long currentTime;
    currentTime = millis();
    //Check if timer on-time is expired
    if (currentTime <= endTime){
     if((timerStatus == true) && (timerOnOff == true) && (currentTime - previousTime >= onTime)) {
        previousTime = currentTime;  // Remember the time
        timerOnOff = false;
        //remoteUpdate = timerOnOff;
        Serial.printf("Finished on-time \n");
     } // End check on-time
      //Check if timer off-time is expired
      currentTime = millis();
     if ((timerStatus == true) && (timerOnOff == false) && (currentTime - previousTime >= offTime)) {
        previousTime = currentTime;  // Remember the time
        timerOnOff = true;
        //remoteUpdate = timerOnOff;
        Serial.printf("Finished off-time \n");
     } // End check off-time
      return timerOnOff;
    } // End if <= End time
    else  
      return false;
  } // End of Update() function

}; //End of LedTimer Class


LedTimer ledTimer1("LED 1 String");
CLEDController& controller1 = FastLED.addLeds<LED_TYPE, ledPin1, COLOR_ORDER> (new CRGB[10], NUM_LEDS).setCorrection(TypicalLEDStrip);



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
  delay(5000);
  setupLeds(4);
}

void setupLeds(int newMode){
  bool runLoop = true;
  bool ledStripOnOff1 = true;
  controller1.showColor(CRGB::Black, 30, 45);
  if (newMode == 4){
      controller1.showColor(CRGB::Green, 8, 45);
      ledTimer1.timerOnceSetup(15000);
      while (runLoop == true){
        ledStripOnOff1 = ledTimer1.timerOnceUpdate();
        if (ledStripOnOff1 == false){
          Serial.println("ledStripOnOff1 is: False");
          controller1.showColor(CRGB::Yellow, 8, 0);
        } // End if
      } // End while loop
    delay(100);
  } // End mode 4
  if (newMode == 5){
    ledTimer1.timerRepeatSetup(true, 450, 450, 15000);
    while (runLoop == true){
      ledStripOnOff1 = ledTimer1.timerRepeatUpdate();
      if (ledStripOnOff1 == false){
        Serial.println("ledStripOnOff1 is: False");
        controller1.showColor(CRGB::Blue, 8, 0);
      }
      else {
        Serial.println("ledStripOnOff1 is: True");
        controller1.showColor(CRGB::Blue, 8, 45);    
      }
    delay(100);
    } // End While loop
  } // End mode 5
  
} // End setupLeds

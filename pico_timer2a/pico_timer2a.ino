
#include <FastLED.h>
//#include <string>

#define COLOR_ORDER GRB      // make the order RGB
#define numLeds 30          //30 LEDs on the strip
#define BRIGHTNESS 50        //LED brightness
#define ledPin1 16          // Led Strip 1 ouput pin
#define ledPin2 17          // Led Strip 2 ouput pin
#define ledPin3 1numLeds          // Led Strip 3 ouput pin
#define ledPin4 19          // Led Strip 4 ouput pin
#define LED_TYPE WS2811  

//#########################################################################
class LedTimer {
  // Class Member Variables
  // These filled at init
  public:
  String timerLabel;  // Name of timer used in print statements
    
  // These are initialized in Setup()
  long onTime;     // milliseconds of on-time in repeat mode
  long offTime;    // milliseconds of off-time in repeat mode
  long endTime;   // calculated time when timer will stop

  // These maintain the current state
  unsigned long previousTime; // will store last time change was made
  unsigned long currentTime;  // will store current time
  bool timerOnOff;            // True when timer is in on-time (Repeat mode)
  bool timerStatus = false;   // State used to enable timer  
  String modeLabel;      // Used in print statements

  // Constructor - creates an LedTimer and initializes some member variables
  public:
  LedTimer(String newLabel){
    modeLabel = newLabel;
  } // End Create Timer
  
  // Used to initialize repeat mode.
  void repeatSetup(int newOnTime, int newOffTime, int newRunTime, String newModeLabel){
    onTime = newOnTime;
    offTime = newOffTime;
    timerStatus = true;
    previousTime = millis(); //Time now. Timer has started
    endTime = previousTime + newRunTime;
    modeLabel = newModeLabel;
  } // End of repeatSetup()

  bool repeatUpdate() {
    // check to see if it's time to make a change
    currentTime = millis();
    if ((currentTime <= endTime) && (timerStatus == true) ){
	  //Check if timer on-time is expired    
	  if((timerOnOff == true) && (currentTime - previousTime >= onTime)) {
        // on-time is finished
        previousTime = currentTime;  // Remember the time
        timerOnOff = false; // Ready to start off-time
        String outString ("Finished on-time for " + timerLabel + " in " + modeLabel);
        Serial.println(outString);
     } // End check on-time
      //Check if timer off-time is expired
      currentTime = millis();
     if ((timerStatus == true) && (timerOnOff == false) && (currentTime - previousTime >= offTime)) {
        // off-time is finished
        previousTime = currentTime;  // Remember the time
        timerOnOff = true; // Ready to start on-time
        String outString ("Finished off-time for " + timerLabel + " in " + modeLabel);
        Serial.println(outString);
     } // End check off-time
    return timerOnOff;
    } // End if <= End time
    else { // Reached end time
        timerStatus = false;
        String outString ("Reached end time for " + timerLabel + " in " + modeLabel);
        Serial.println(outString);
        return false;
    } // End else
  } // End of Update() function

  void onceSetup(int newRunTime, String newModeLabel){
    previousTime = millis();
    endTime = previousTime + newRunTime;
	  timerStatus = true;
    modeLabel = newModeLabel;   
  } // End of onceSetup()

  bool onceUpdate(){
    currentTime = millis();
    if ((currentTime <= endTime) && (timerStatus == true)) {
      //Serial.printf("In on-time (onceUpdate) \n");
      delay(500);
      return true;
	  } // End if
    else {
      timerStatus = false;
      String outString ("Reached end time for " + timerLabel + " in " + modeLabel);
      Serial.println(outString);
      timerStatus = false;
  	  return false;
    } // End Else
  } // End of onceUpdate()

}; //End of LedTimer Class


LedTimer ledTimer1("LED 1 Strip");
CLEDController& controller1 = FastLED.addLeds<LED_TYPE, ledPin1, COLOR_ORDER> (new CRGB[10], numLeds).setCorrection(TypicalLEDStrip);
bool firstRun = true;
bool runTimer = true;
bool stripStatus1 = true;

void setupLeds(int newMode){
  controller1.clearLedData();
  //controller1.showColor(CRGB::White, 30, 50);
  //delay(200);
  //controller1.showColor(CRGB::White, 30, 0);
  delay(200);
  if (newMode == 4){ // Run once
    
    if (firstRun == true){
        runTimer = true;
        stripStatus1 = true;
        ledTimer1.onceSetup(15000, "Mode-4");
        controller1.showColor(CRGB::Blue, numLeds, 45);
        firstRun = false;
    } // End if firstRun is true
      if (runTimer == true){
        stripStatus1 = ledTimer1.onceUpdate();
        if (stripStatus1 == false){
          Serial.println("Mode 4 - stripStatus1 is: False (setupLeds)");
          runTimer = false; //Run once since mode = 4
          controller1.showColor(CRGB::Blue, numLeds, 0);
        } // End if stripStatus is false
      } // End if runTimer is true
    delay(100);
  } // End mode 4
  
  if (newMode == 5){ // Flash 
    if (firstRun == true){
        runTimer = true;
        stripStatus1 = true;
        ledTimer1.repeatSetup(450, 450, 15000, "Mode-5");
        firstRun = false;
    }    
    if (runTimer == true){
      stripStatus1 = ledTimer1.repeatUpdate();
      if (stripStatus1 == false){
        controller1.showColor(CRGB::Blue, numLeds, 0);
      } // End if runTimer is true
    else {
        controller1.showColor(CRGB::Blue, numLeds, 45);    
    } // End else
    delay(100);
    } // End if runTimer is true
  } // End mode 5
} // End setupLeds

void setup() {
    Serial.begin(115200);
}

void loop()
{
 /*
  stripStatus1 = ledTimer1.timerUpdate();
  if (stripStatus1 == true){
    Serial.println("stripStatus1 is: True");
    controller1.showColor(CRGB::Blue, numLeds, 45);
  }
  else {
    Serial.println("stripStatus1 is: False");
    controller1.showColor(CRGB::Red, numLeds, 45);    
  }
  delay(100);
  */
  //setupLeds(5); //Flash Blue
  setupLeds(4); //One time Green
/*
controller1.clearLeds(numLeds);
delay(5000);
controller1.showColor(CRGB::Green, numLeds, 45);
delay(2000);
controller1.showColor(CRGB::Blue, numLeds, 45);
delay(2000);
controller1.showColor(CRGB::Red, numLeds, 45);
delay(2000);
controller1.showColor(CRGB::Red, numLeds, 0);
*/ 
  
  
  
  
}

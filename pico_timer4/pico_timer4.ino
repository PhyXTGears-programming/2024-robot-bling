
#include <FastLED.h>
#include <Adafruit_NeoPixel.h>

/////////////////////////////////////////////////////////////////
// Data Constants
#define colorOrder GRB     // make the order RGB
#define numLeds1 30         //30 LEDs on the strip
#define numLeds2 10         //30 LEDs on the strip
#define numLeds3 10         //30 LEDs on the strip
#define numLeds4 10         //30 LEDs on the strip
#define bright1 45          //brightness level 1
#define bright2 55          //brightness level 2
#define bright3 65          //brightness level 3
#define bright4 75          //brightness level 4
#define ledPin1 16          // Led Strip 1 ouput pin
#define ledPin2 17          // Led Strip 2 ouput pin
#define ledPin3 18         // Led Strip 3 ouput pin
#define ledPin4 00          // Led Strip 4 ouput pin
#define ledType WS2811  
#define statusOff 10        // Used by stripStatus
#define statusOn 11         // Used by stripStatus
#define statusRepeatOn 12   // Used by stripStatus
#define statusRepeatOff 13  // Used by stripStatus
#define statusOnceOn 14     // Used by stripStatus
#define statusOnceOff 15    // Used by stripStatus
#define repeatOnTime 21
#define repeatOffTime 22

/////////////////////////////////////////////////////////////////
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
  int timerOnOff;            // Used in timer Repeat mode

  // Constructor - creates an LedTimer and initializes some member variables
  public:
  LedTimer(String newLabel){
    timerLabel = newLabel;
  } // End Create Timer
  
  // Used to initialize repeat mode.
  void repeatSetup(int newOnTime, int newOffTime, int newRunTime){
    onTime = newOnTime;
    offTime = newOffTime;
    previousTime = millis(); //Time now. Timer has started
    endTime = previousTime + newRunTime;
    timerOnOff = repeatOnTime; //Start in on-time
  } // End of repeatSetup()

  int repeatUpdate() {
    int localStatus; // Used in return statements
    String localString; // Used in print statements
    // check to see if it's time to make a change
    currentTime = millis();
    if (currentTime <= endTime) {
    //Check if timer is in on-time
    currentTime = millis();
    if((timerOnOff == repeatOnTime) && (currentTime - previousTime < onTime)) {
        localString = ("Running in on-time for " + timerLabel);
        Serial.println(localString);
        localString = ("");
        localStatus = statusRepeatOn; // Still in on-time
     } // End check on-time
	  //Check if timer on-time is expired  
    currentTime = millis();
	  if((timerOnOff == repeatOnTime) && (currentTime - previousTime >= onTime)) {
        previousTime = currentTime;  // Remember the time
        timerOnOff = repeatOffTime; // Ready to start off-time
        localString = ("Finished on-time for " + timerLabel);
        Serial.println(localString);
        localString = ("");
        localStatus = statusRepeatOff; // Now in Off-time
     } // End check on-time
    //Check if timer is in off-time
    currentTime = millis();
    if((timerOnOff == repeatOnTime) && (currentTime - previousTime < offTime)) {
        localString = ("Running in off-time for " + timerLabel);
        Serial.println(localString);
        localString = ("");
        localStatus = statusRepeatOff; // Still in off-time
     } // End check off-time
    //Check if timer off-time is expired
    currentTime = millis();
    if ((timerOnOff == repeatOffTime) && (currentTime - previousTime >= offTime)) {
        previousTime = currentTime;  // Remember the time
        timerOnOff = repeatOnTime;   // Ready to start on-time
        localString = ("Finished off-time for " + timerLabel);
        Serial.println(localString);
        localString = ("");
        localStatus = statusRepeatOn; // Now in On-time
    } // End check off-time
    } // End if <= End time
    // Check if End-time is reached
    currentTime = millis();
    if (currentTime > endTime){ // Reached end time
        localString = ("Reached end time for " + timerLabel);
        Serial.println(localString);
        localString = ("");
        localStatus =  statusOff; // On/Off cycle is over
    } // End if reached end-time
    return localStatus;
  } // End of repeatUpdate()

  void onceSetup(int newRunTime){
    previousTime = millis(); // Timer is running
    endTime = previousTime + newRunTime;
    } // End onceSetup()

  int onceUpdate(){
    int localStatus; // Used in return statements
    String localString; // Used in print statements
    currentTime = millis();
    if (currentTime < endTime) {
      localStatus =  statusOnceOn; // Still in On-time
      localString = ("Still in on-time for " + timerLabel);
      Serial.println(localString);
    } // End if
    else {
      localStatus =  statusOnceOff; // On-time is over
      localString = ("Reached end time for " + timerLabel);
      Serial.println(localString);
  	} // End Else
    return localStatus;
  } // End of onceUpdate()

}; //End of LedTimer Class

/////////////////////////////////////////////////////////////////

// Global parameters
bool firstRun1 = true;
bool firstRun3 = false;
bool runTimer = true;
int currentStatus;
int count1 = 0;
int stripStatus1 = statusOff;
int stripStatus3 = statusOff;
#define picoGreen   CRGB(0   , 150 , 0  )
CRGB picoYellow     = CRGB(255 , 208 , 0  );
CRGB picoPurple     = CRGB(196 , 0   , 255);
CRGB picoBlue       = CRGB(0   , 0   , 224);
#define picoRed        CRGB(150 , 0   , 0  )
CRGB picoLightBlue  = CRGB(0   , 255 , 251);
CRGB picoWhite      = CRGB(255 , 225 , 225);
CRGB picoBrown      = CRGB(89  , 73  , 41 );
CRGB picoPink       = CRGB(237 , 0   , 205);
CRGB picoBlack      = CRGB(0   , 0   , 0  ); 


/////////////////////////////////////////////////////////////////
LedTimer ledTimer1("LED 1 Strip");
LedTimer ledTimer3("LED 3 Strip");
Adafruit_NeoPixel ledStrip1(numLeds1, ledPin1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel ledStrip3(numLeds3, ledPin3, NEO_GRB + NEO_KHZ800);

/////////////////////////////////////////////////////////////////

void setup() {
    Serial.begin(115200);
    delay(3000);
    //FastLED.addLeds<ledType, ledPin1>(ledStrip1, numLeds1);    
    //FastLED.addLeds< ledType, ledPin1, colorOrder> (CRGB & ledStrip1, numLeds1).setCorrection(TypicalLEDStrip);
    //FastLED.addLeds< ledType, ledPin3, colorOrder> (ledStrip3, numLeds3).setCorrection(TypicalLEDStrip);
    ledStrip1.begin(); // INITIALIZE NeoPixel strip object
    ledStrip1.fill(ledStrip1.Color(0, 0, 0),0,numLeds1); //RGB
    ledStrip1.show(); // Set all pixel colors to 'off'
    ledStrip3.begin(); // INITIALIZE NeoPixel strip object
    ledStrip3.fill(ledStrip1.Color(0, 0, 0),0,numLeds1); //RGB
    ledStrip3.show(); // Set all pixel colors to 'off'
    uint32_t magenta = ledStrip1.Color(255, 0, 255);
}

void loop() {

// Repeat mode
    if (firstRun1 == true) {
    Serial.println("Start Repeat Mode");
    //ledStrip1.fill(ledStrip1.Color(0, 100, 0),count1,numLeds1/2); //RGB
    // Start color 
    //ledStrip1.show(); 
    delay(2000); // wait a moment before timer starts
    ledTimer1.repeatSetup(350, 350, 6500);
    // (On-Time, Off-Time, End-Time, Label)
    //ledStrip1.fill(ledStrip1.Color(50, 0, 0),count1,numLeds1/2); //RGB
    //ledStrip1.show(); 
    // On-color
    //delay(500);
    firstRun1 = false;
  } // End First Run is true
  currentStatus = ledTimer1.repeatUpdate();
  if (currentStatus == statusRepeatOn) {
    Serial.println("Current Status: Repeat On");
    ledStrip1.fill(ledStrip1.Color(50, 0, 0),count1,numLeds1/2); //RGB
    // On color
    ledStrip1.show(); 
    delay(200);
  }
  else if (currentStatus == statusRepeatOff) {
    Serial.println("Current Status: Repeat Off");
    ledStrip1.fill(ledStrip1.Color(0, 0, 50),count1,numLeds1/2); //RGB
    // Off color
    ledStrip1.show();
    delay(200);
  }
  else if (currentStatus == statusOff) {
    Serial.println("Current Status: Off; End time reached");
    ledStrip1.fill(ledStrip1.Color(0, 0, 0),0,numLeds1); //RGB
    ledStrip1.show();
    //count1 = count1 +1;
    firstRun1 = true;
    delay(2000);
    firstRun3 = true;
    ledStrip1.clear();
  }

//////////////////////////////////////////////////////////

// One-time mode
    if (firstRun3 == true) {
    Serial.println("Start one-time");
    ledStrip1.fill(ledStrip1.Color(50, 25, 5),count1,numLeds1/2); //RGB
    ledStrip1.show(); 
    ledTimer3.onceSetup(5000);
    firstRun3 = false;
  } // End First Run
  currentStatus = ledTimer3.onceUpdate();
  if (currentStatus == statusOnceOn) {
    Serial.println("Current Status: On");
  }
  else if (currentStatus == statusOnceOff) {
    Serial.println("Current Status: Off");
    ledStrip1.fill(ledStrip1.Color(0, 0, 0),0,numLeds1); //RGB
    //ledStrip1.clear(); // Set all pixel colors to 'off'  
    ledStrip1.show();
    //count1 = count1 +1;
    firstRun3 = true;
    delay(3000);
  }
  
}

/**
  void Setup() {


    //ledTimer(stripLabel);
    //controller = FastLED.addLeds<LED_TYPE, stripPin, COLOR_ORDER> (new CRGB[10], stripLength).setCorrection(TypicalLEDStrip);
    controller.clearLedData();
    runTimer = true;
    firstRun = true;
    stripStatus = true;
  } // End Setup
  
  void stripRunOnce(int brightness, CRGB newColor) {
    if (newMode == 4){ // Run once
      if (firstRun == true){
        onceSetup(15000, "Mode-4");
        controller.showColor(newColor, stripLength, brightness);
        firstRun = false;
      } // End if firstRun is true
      if (runTimer == true){
        //stripStatus = ledTimer.onceUpdate();
        stripStatus = onceUpdate();
        if (stripStatus == false){
          Serial.println("Mode 4 - stripStatus is: False (Setup)");
          runTimer = false; //Run once since mode = 4
          controller.showColor(newColor, stripLength, 0);
        } // End if Status is false
      } // End if runTimer is true
      } // End mode is 4
  } // End stripRunOnce
}; //  LedStrip Class
 
*/

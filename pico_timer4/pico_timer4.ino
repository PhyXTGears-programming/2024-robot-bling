
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
  int timerOnOff;            // True when timer is in on-time (Repeat mode)
  bool timerStatus = false;   // State used to enable timer  
  String modeLabel;           // Used in print statements

  // Constructor - creates an LedTimer and initializes some member variables
  public:
  LedTimer(String newLabel){
    timerLabel = newLabel;
  } // End Create Timer
  
  // Used to initialize repeat mode.
  void repeatSetup(int newOnTime, int newOffTime, int newRunTime, String newModeLabel){
    onTime = newOnTime;
    offTime = newOffTime;
    timerStatus = true;      // Start in On-Time
    previousTime = millis(); //Time now. Timer has started
    endTime = previousTime + newRunTime;
    modeLabel = newModeLabel;
  } // End of repeatSetup()

  int repeatUpdate() {
    int localStatus;
    String localString;
    // check to see if it's time to make a change
    currentTime = millis();
    if ((currentTime <= endTime) && (timerStatus == true) ){
	  //Check if timer on-time is expired    
	  if((timerOnOff == repeatOnTime) && (currentTime - previousTime >= onTime)) {
        previousTime = currentTime;  // Remember the time
        timerOnOff = repeatOffTime; // Ready to start off-time
        localString = ("Finished on-time for " + timerLabel);
        Serial.println(localString);
        localString = ("");
        localStatus = statusRepeatOff; // Now in Off-time
     } // End check on-time
      //Check if timer off-time is expired
      currentTime = millis();
     if ((timerOnOff == repeatOffTime) && (currentTime - previousTime >= offTime)) {
        previousTime = currentTime;  // Remember the time
        timerOnOff = repeatOnTime; // Ready to start on-time
        localString = ("Finished off-time for " + timerLabel);
        Serial.println(localString);
        localString = ("");
        localStatus = statusRepeatOn; // Now in On-time
     } // End check off-time
    } // End if <= End time
    currentTime = millis();
    if (currentTime > endTime){ // Reached end time
        timerStatus = false;
        localString = ("Reached end time for " + timerLabel);
        Serial.println(localString);
        localString = ("");
        localStatus =  statusOff;
    } // End if reached end-time
    return localStatus;
  } // End of repeatUpdate()

  void onceSetup(int newRunTime, String newModeLabel){
    previousTime = millis();
    endTime = previousTime + newRunTime;
	  timerStatus = true;
    modeLabel = newModeLabel;   
  } // End of onceSetup()

  int onceUpdate(){
    String localString;
    currentTime = millis();
    if ((currentTime <= endTime) && (timerStatus == true)) {
      Serial.printf("In on-time (onceUpdate) \n");
      delay(5);
      return statusOn;
	  } // End if
    else {
      timerStatus = false;
      localString = ("Reached end time for " + timerLabel);
      Serial.println(localString);
  	  return statusOff;
    } // End Else
  } // End of onceUpdate()

}; //End of LedTimer Class

/////////////////////////////////////////////////////////////////

// Global parameters
bool firstRun1 = true;
bool firstRun3 = true;
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
//CRGB ledStrip1[numLeds1];
//CRGB ledStrip3[numLeds3];

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
/**	if (firstRun1 == true) {
    Serial.println("Start");
    ledStrip1.fill(ledStrip1.Color(50, 25, 5),count1,numLeds1/2); //RGB
    ledStrip1.show(); 
    ledTimer1.onceSetup(3000, "Strip 1");
    firstRun1 = false;
	} // End First Run
	currentStatus = ledTimer1.onceUpdate();
  if (currentStatus == statusOn) {
    Serial.println("Current Status True");
  }
  else if (currentStatus == statusOff) {
    Serial.println("Current Status False");
    ledStrip1.fill(ledStrip1.Color(0, 0, 0),0,numLeds1); //RGB
    //ledStrip1.clear(); // Set all pixel colors to 'off'  
    ledStrip1.show();
    count1 = count1 +1;
    firstRun1 = true;
  }
**/  
  delay(100);
    if (firstRun1 == true) {
    Serial.println("Start");
    ledStrip1.fill(ledStrip1.Color(0, 100, 0),count1,numLeds1/2); //RGB
    ledStrip1.show(); 
    delay(2000);
    ledTimer1.repeatSetup(1000, 1000, 4500, "Strip 1");
    // (On-Time, Off-Time, End-Time, Label)
    firstRun1 = false;
  } // End First Run is true
  currentStatus = ledTimer1.repeatUpdate();
  if (currentStatus == statusRepeatOn) {
    Serial.println("Current Status: Repeat On");
    ledStrip1.fill(ledStrip1.Color(50, 0, 0),count1,numLeds1/2); //RGB
    ledStrip1.show(); 
  }
  else if (currentStatus == statusRepeatOff) {
    Serial.println("Current Status: Repeat Off");
    ledStrip1.fill(ledStrip1.Color(0, 0, 50),count1,numLeds1/2); //RGB
    ledStrip1.show(); 
  }
  else if (currentStatus == statusOff) {
    Serial.println("Current Status: Off; End time reached");
    ledStrip1.fill(ledStrip1.Color(0, 0, 0),0,numLeds1); //RGB
    ledStrip1.show();
    //count1 = count1 +1;
    firstRun1 = true;
    delay(2000);
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
  
  void stripRunOnce(int newMode, int brightness, CRGB newColor) {
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


//#include <FastLED.h>
#include <Adafruit_NeoPixel.h>

/////////////////////////////////////////////////////////////////
// Data Constants
#define numLeds1 30         // Number LEDs on the strip
#define numLeds2 30         // Number LEDs on the strip
#define numLeds3 30         // Number LEDs on the strip
#define numLeds4 30         // Number LEDs on the strip
#define ledPin1 16          // Led Strip 1 ouput pin
#define ledPin2 17          // Led Strip 2 ouput pin
#define ledPin3 18          // Led Strip 3 ouput pin
#define ledPin4 19          // Led Strip 4 ouput pin
#define statusOff 10        // Used by stripStatus
#define statusOn 11         // Used by stripStatus
#define statusRepeatOn 12   // Used by stripStatus
#define statusRepeatOff 13  // Used by stripStatus
#define statusOnceOn 14     // Used by stripStatus
#define statusOnceOff 15    // Used by stripStatus
#define repeatOnTime 21
#define repeatOffTime 22

// Needed here before Class ledEffects
Adafruit_NeoPixel ledStrip1(numLeds1, ledPin1, NEO_GRB + NEO_KHZ800); 
Adafruit_NeoPixel ledStrip2(numLeds2, ledPin2, NEO_GRB + NEO_KHZ800); 
Adafruit_NeoPixel ledStrip3(numLeds3, ledPin3, NEO_GRB + NEO_KHZ800); 
Adafruit_NeoPixel ledStrip4(numLeds4, ledPin4, NEO_GRB + NEO_KHZ800); 

/////////////////////////////////////////////////////////////////
class LedTimer {
  // Works in two modes: One-time and Repeat.
  // Class Member Variables 
  public:
  String timerLabel;  // Name of timer used in print statements
    
  // These are initialized in Setup()
  long onTime;     // milliseconds of on-time in repeat mode
  long offTime;    // milliseconds of off-time in repeat mode
  long endTime;   // calculated time when timer will stop

  // These maintain the current state
  unsigned long previousTime; // will store last time change was made
  unsigned long currentTime;  // will store current time
  int timerOnOff;             // Used to track on/off cycles in repeat mode

  // Constructor - creates an LedTimer and initializes some member variables
  public:
  LedTimer(String newLabel){
    timerLabel = newLabel; // Used in print statements
    } // End Create Timer
  
  // Used to initialize repeat mode.
  void repeatSetup(int newOnTime, int newOffTime, int newRunTime){
    onTime = newOnTime;
    offTime = newOffTime;
    previousTime = millis(); // Timer has started
    endTime = previousTime + newRunTime;
    timerOnOff = repeatOnTime; //Start in on-time
  } // End of repeatSetup()

  int repeatUpdate() {
    String localString; // Used in print statements
    int localStatus; // Used in return statements
    // Repeat Mode Status
    // statusRepeatOn - current time is < onTime; still in on-time
    // statusRepeatOff - current time is < offTime; still in off-time
    // statusOff - currrent time is > endTime; repeat mode is complete
    
    // Is it time to make a change?
    currentTime = millis();
    if ((timerOnOff == repeatOnTime) && (currentTime - previousTime < onTime) && (currentTime <= endTime)) {
        localString = ("repeatUpdate: In on-time for " + timerLabel);
        Serial.println(localString);
        localString = ("");
        localStatus = statusRepeatOn; // Returning: "In on-time"
     } // End check on-time
    //Check if timer on-time is expired
    else if ((timerOnOff == repeatOnTime) && (currentTime - previousTime >= onTime) && (currentTime <= endTime)) {
        previousTime = currentTime;  // Remember the start of off-time
        timerOnOff = repeatOffTime; // Ready to start off-time
        localString = ("repeatUpdate: Finished on-time for " + timerLabel);
        Serial.println(localString);
        localString = ("");
        localStatus = statusRepeatOff; // Returning: "In off-time"
     } // End check on-time
    //Check if timer is in off-time
    else if ((timerOnOff == repeatOffTime) && (currentTime - previousTime < offTime) && (currentTime <= endTime)) {
        localString = ("repeatUpdate: In off-time for " + timerLabel);
        Serial.println(localString);
        localString = ("");
        localStatus = statusRepeatOff; // Returning: "In off-time"
     } // End check off-time
    //Check if timer off-time is expired
    else if ((timerOnOff == repeatOffTime) && (currentTime - previousTime >= offTime) && (currentTime <= endTime)) {
        previousTime = currentTime;  // Remember the time
        timerOnOff = repeatOnTime;   // Ready to start on-time
        localString = ("Finished off-time (repeatUpdate) for " + timerLabel);
        Serial.println(localString);
        localString = ("");
        localStatus = statusRepeatOn; // Returning: "In on-time"
    } // End check off-time
    // Check if End-time is reached
    currentTime = millis();
    if ((currentTime > endTime)){ // Reached end time for repeat mode
        localString = ("repeatUpdate: Reached end time for " + timerLabel);
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
      localString = ("onceUpdate: In on-time for " + timerLabel);
      Serial.println(localString);
    } // End if
    else if (currentTime >= endTime) {
      localStatus =  statusOnceOff; // On-time is over
      localString = ("onceUpdate: Reached end time for " + timerLabel);
      Serial.println(localString);
    } // End Else
    return localStatus;
  } // End of onceUpdate()

}; //End of LedTimer Class

/////////////////////////////////////////////////////////////////
// Global parameters
bool firstRun1 = false;
bool firstRun2 = false;
bool firstRun3 = false;
bool firstRun4 = false;
int count1 = 0;
int count2 = 0;
int count3 = 0;
int count4 = 0;
int count11 = 0;
int stripStatus1 = statusOff;
int stripStatus2 = statusOff;
int stripStatus3 = statusOff;
int stripStatus4 = statusOff;

/////////////////////////////////////////////////////////////////
LedTimer ledTimer1("Timer1");
LedTimer ledTimer2("Timer2");
LedTimer ledTimer3("Timer3");
LedTimer ledTimer4("Timer4");
/////////////////////////////////////////////////////////////////

void setup() {
    Serial.begin(115200);
    delay(3000);
    ledStrip1.begin(); // INITIALIZE NeoPixel strip object
    ledStrip1.fill(ledStrip1.Color(0, 0, 0),0,30); //RGB
    ledStrip1.show(); // Set all pixel colors to 'off'
    ledStrip1.setBrightness(65);
    ledStrip1.clear();
    ledStrip1.show();
    ledStrip3.begin(); // INITIALIZE NeoPixel strip object
    ledStrip3.show();
    ledStrip3.setBrightness(65);

    firstRun1 = true;
    firstRun2 = true;
    firstRun3 = true;
    firstRun4 = true;
    //uint32_t magenta = ledStrip1.Color(255, 0, 255);
} // End setup()

int n = 50;
void loop() {    
  int localStatus1;
  int localStatus3;

	// Repeat mode using LED strip 3 and Timer 3
  // Repeat Mode Status:
  // statusRepeatOn - current time is < onTime; still in on-time
  // statusRepeatOff - current time is < offTime; still in off-time
  // statusOff - currrent time is > endTime; repeat mode is complete
  if (firstRun3 == true) { // Start of the repeat cycle
      Serial.println("In loop() - Start Repeat Mode");
      // xxx.fill(color, first, count);
      ledStrip3.fill(ledStrip3.Color(15, 85, 15),1,30); //RGB
      // Start color 
      ledStrip3.show(); 
      delay(1000); // wait a moment before timer starts
      ledTimer3.repeatSetup(300, 300, 3700);
      delay(100);                                                              
      firstRun3 = false; // Run once per repeat cycle
    } // End First Run is true
  localStatus3 = ledTimer3.repeatUpdate(); // Checking on timer status
  if (localStatus3 == statusRepeatOn) {
      Serial.println("Current Status in loop(): Repeat On");
      ledStrip3.fill(ledStrip3.Color(50, 0, 0),1,30); //RGB
      // On color red
      ledStrip3.show(); 
      delay(100);
  } // End if statusRepeatOn
  else if (localStatus3 == statusRepeatOff) {
    Serial.println("Current Status in loop(): Repeat Off");
    ledStrip3.fill(ledStrip3.Color(0, 0, 50),1,30); //RGB
    // Off color blue
    ledStrip3.show();
    delay(100);
  } // End else if statusRepeatOff
  else if (localStatus3 == statusOff) {
    firstRun3 = true; // Ready of next repeat cycle
    Serial.println("Current Status in loop(): Off; End time reached");
    ledStrip3.fill(ledStrip3.Color(0, 0, 0),0,30); //RGB
    ledStrip3.show();
    delay(1000);
    }// End else if statusOff

} // End loop()

void oneTimeLedSetup(int newLedStrip, uint32_t newOnColor, int newTimeOut) {
  if (newLedStrip == 1) {
    if (firstRun1 == true) {
    // One-time Status:
    // statusOnceOn - Still in On-time
    // statusOnceOff - On-time is over
    Serial.println("Starting One-Time mode for ledStip1");
    ledStrip1.fill(newOnColor,0,numLeds1); // On-Color
    ledStrip1.show(); 
    ledTimer1.onceSetup(newTimeOut);
    firstRun1 = false;
  } // End FirstRun1 
  } // End ledStrip1

} // End oneTimeLedSetup()

int oneTimeLedUpdate(int newLedStrip, uint32_t localBlack){
  int localStatus;
  if (newLedStrip == 1) {
  localStatus = ledTimer1.onceUpdate();
  if (localStatus == statusOnceOn) {
    Serial.println("One-Time Mode is ON for ledStrip1");
    delay(100);
  } // End if statusOnceOn
  else if (localStatus == statusOnceOff) {
    Serial.println("One-Time is ON for ledStrip1");
    ledStrip1.fill(localBlack,0,numLeds1); // Off-Color
    ledStrip1.show();
    firstRun1 = true;
  } // end else if statusOnceOff
  } // End ledStrip1
  return 0;
} // End oneTimeLedUpdate()


void repeatLedSetup(int newLedStrip, uint32_t newOffColor, int newOnTime, int newOffTime, int newRunTime) {
  if (newLedStrip == 1) {
    if (firstRun1 == true) { // Start of the repeat cycle
    // Repeat Mode Status:
    // statusRepeatOn - current time is < onTime; still in on-time
    // statusRepeatOff - current time is < offTime; still in off-time
    // statusOff - currrent time is > endTime; repeat mode is complete
      Serial.println("Starting Repeat mode for ledStip1");
      // xxx.fill(color, first, count);
      ledStrip1.fill(newOffColor,0,numLeds1); // Off-Color
      ledStrip1.show(); 
      delay(100); // wait a moment before timer starts
      ledTimer1.repeatSetup(newOnTime, newOffTime, newRunTime);
      delay(100);                                                              
      firstRun1 = false; // Run once per repeat cycle    
    } // End FirstRun1 
  } // End ledStrip1

} // End repeatLedSetup()

int repeatLedUpdate(int newLedStrip, uint32_t newOnColor, uint32_t newOffColor, uint32_t localBlack) {
  int localStatus;
  if (newLedStrip == 1) {
  localStatus = ledTimer1.repeatUpdate(); // Checking on timer status
  if (localStatus == statusRepeatOn) {
      Serial.println("Current Status in loop(): Repeat On");
      ledStrip1.fill(newOnColor,0,numLeds1); // On-Color
      ledStrip1.show(); 
      delay(100);
  } // End if statusRepeatOn
  else if (localStatus == statusRepeatOff) {
    Serial.println("Current Status in loop(): Repeat Off");
    ledStrip1.fill(newOffColor,0,numLeds1); // Off-Color
    ledStrip1.show();
    delay(100);
  } // End else if statusRepeatOff
  else if (localStatus == statusOff) {
    firstRun1 = true; // Ready of next repeat cycle
    Serial.println("Current Status in loop(): Off; End time reached");
    ledStrip1.fill(localBlack,0,numLeds1);
    ledStrip1.show();
    delay(100);
    }// End else if statusOff
  } // End ledStrip1
  return 0;    
} // End repeatLedUpdate()

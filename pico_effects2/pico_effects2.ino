
//#include <FastLED.h>
#include <Adafruit_NeoPixel.h>

/////////////////////////////////////////////////////////////////
// Data Constants
#define numLeds1 30         //30 LEDs on the strip
#define numLeds2 30         //30 LEDs on the strip
#define numLeds3 30        //30 LEDs on the strip
#define numLeds4 30         //30 LEDs on the strip
#define ledPin1 16         // Led Strip 1 ouput pin
#define ledPin2           // Led Strip 2 ouput pin
#define ledPin3 18         // Led Strip 3 ouput pin
#define ledPin4 19          // Led Strip 4 ouput pin
#define statusOff 10        // Used by stripStatus
#define statusOn 11         // Used by stripStatus
#define statusRepeatOn 12   // Used by stripStatus
#define statusRepeatOff 13  // Used by stripStatus
#define statusOnceOn 14     // Used by stripStatus
#define statusOnceOff 15    // Used by stripStatus
#define repeatOnTime 21
#define repeatOffTime 22

bool DEBUG = false;
// Needed here before Class ledEffects
Adafruit_NeoPixel ledStrip1(numLeds1, ledPin1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel ledStrip3(numLeds3, ledPin3, NEO_GRB + NEO_KHZ800);

/////////////////////////////////////////////////////////////////
class LedTimer {
  // Works in two modes: One0time and Repeat.
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
    if (currentTime > endTime){ // Reached end time for repeat mode
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
class LedEffects {
  //Class Member variables
  public: 
  int stripNum;
  int wipeCount1 ;
  int wipeCount3 ;
  bool localStatus;
  // Constructor
  public:
  LedEffects(int newStripNum){
    stripNum = newStripNum;
    wipeCount1 = 0;
    wipeCount3 = 0;
    localStatus = false;
  } // End create LedEffects()

  bool colorWipe(uint32_t color, int wait) {
    if (stripNum == 1){ // For LED Strip 1
      if (wipeCount1 < ledStrip1.numPixels()){
        ledStrip1.setPixelColor(wipeCount1, color);// Set one pixel's color
        ledStrip1.show();                         // Update strip to match
        localStatus = false;                      // Used by return
        wipeCount1 = wipeCount1 + 1;                // Ready for next pixel
        delay(wait);                           //  Pause for a moment   
      } // End if wipeCount1
      else if (wipeCount1 >= ledStrip1.numPixels()){
        localStatus = true;     // Used by return
        wipeCount1 = 0;          // Ready for next Color Wipe 
      } // end else if wipeCount1
    } // End if stripNum is 1
    else if (stripNum == 3) { // For LED Strip 3
      if (wipeCount3 <= ledStrip3.numPixels()){
        ledStrip3.setPixelColor(wipeCount3, color);//  Set one pixel's color
        ledStrip3.show();                         //  Update strip to match
        localStatus = false;                      // Used by return
        wipeCount3 = wipeCount3 + 1;                // Ready for next pixel
        delay(wait);                           //  Pause for a moment    
    } // End if wipeCount3
    else if (wipeCount3 >= ledStrip3.numPixels()){
      localStatus = true;     // Used by return
      wipeCount3 = 0;          // Ready for next Color Wipe
    } // end if wipeCount3
  } // End else if stripNum is 3   
  return localStatus;
  } // End colorWipe()

  // Rainbow cycle along whole strip. Pass delay time (in ms) between frames.
  void rainbow(int wait) {
  // Hue of first pixel runs 5 complete loops through the color wheel.
  // Color wheel has a range of 65536 but it's OK if we roll over, so
  // just count from 0 to 5*65536. Adding 256 to firstPixelHue each time
  // means we'll make 5*65536/256 = 1280 passes through this loop:
    for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {
    // strip.rainbow() can take a single argument (first pixel hue) or
    // optionally a few extras: number of rainbow repetitions (default 1),
    // saturation and value (brightness) (both 0-255, similar to the
    // ColorHSV() function, default 255), and a true/false flag for whether
    // to apply gamma correction to provide 'truer' colors (default true).
    if (stripNum == 1){ // For LED Strip 1
		ledStrip1.rainbow(firstPixelHue);
		// Above line is equivalent to:
		// strip.rainbow(firstPixelHue, 1, 255, 255, true);
		ledStrip1.show(); // Update strip with new contents  
    } //End if 
    else if (stripNum == 3){ // For LED Strip 1
		ledStrip3.rainbow(firstPixelHue);
		// Above line is equivalent to:
		// strip.rainbow(firstPixelHue, 1, 255, 255, true);
		ledStrip3.show(); // Update strip with new contents  
    } //End if 
    delay(wait);  // Pause for a moment
    } // End for loop
  } // End rainbow()

}; // End ledEffects Class

/////////////////////////////////////////////////////////////////
// Global parameters
bool firstRun1 = false;
bool firstRun3 = false;
bool firstRun9 = false;
bool runTimer = true;
int currentStatus;
int count1 = 0;
int count3 = 0;
int count11 = 0;
int stripStatus1 = statusOff;
int stripStatus3 = statusOff;
int effectsStatus1 = statusOff;

/////////////////////////////////////////////////////////////////
LedTimer ledTimer1("Timer1 - Once Mode");
LedTimer ledTimer3("Timer3 - Repeat Mode");
LedTimer ledTimer9("Timer9 - Effects Mode");
LedEffects mystrip1(1);
LedEffects mystrip3(3);
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
    ledStrip3.fill(ledStrip3.Color(0, 0, 0),0,30); //RGB
    ledStrip3.show(); // Set all pixel colors to 'off'
    ledStrip3.setBrightness(65);
    ledStrip3.clear();
    ledStrip3.show();
    firstRun1 = true;
    firstRun3 = true;
    uint32_t magenta = ledStrip1.Color(255, 0, 255);
}
int n = 50;
void loop() {    
  int localStatus1;
  bool localStatus3;
  int effectsStatus;

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
      ledTimer3.repeatSetup(300, 300, 3500);
      delay(50);                                                              
      firstRun3 = false; // Run once per repeat cycle
    } // End First Run is true
  localStatus3 = ledTimer3.repeatUpdate(); // Checking on timer status
  if (localStatus3 == statusRepeatOn) {
      Serial.println("Current Status in loop(): Repeat On");
      ledStrip3.fill(ledStrip3.Color(50, 0, 0),1,30); //RGB
      // On color red
      ledStrip3.show(); 
      delay(20);
  } // End if statusRepeatOn
  else if (localStatus3 == statusRepeatOff) {
    Serial.println("Current Status in loop(): Repeat Off");
    ledStrip3.fill(ledStrip3.Color(0, 0, 50),1,30); //RGB
    // Off color blue
    ledStrip3.show();
    delay(20);
  } // End else if statusRepeatOff
  else if (localStatus3 == statusOff) {
    firstRun3 = true; // Ready of next repeat cycle
    Serial.println("Current Status in loop(): Off; End time reached");
    //ledStrip3.fill(ledStrip3.Color(0, 0, 0),0,30); //RGB
    //ledStrip3.show();
    }// End else if statusOff

  //mystrip3.colorWipe(ledStrip3.Color(255,   0,   0), 0); // Red
  //mystrip3.colorWipe(ledStrip3.Color(  0, 255,   0), 50); // Green
  //mystrip3.colorWipe(ledStrip3.Color(  0,   0, 255), 50); // Blue

//////////////////////////////////////////////////////////

// One-time mode
    if (firstRun1 == true) {
    // One-time Status:
    // statusOnceOn - Still in On-time
    // statusOnceOff - On-time is over
    Serial.println("In Loop() - Start one-time");
    ledStrip1.fill(ledStrip1.Color(n, 25, 5),1,30); //RGB
    ledStrip1.show(); 
    ledTimer1.onceSetup(3500);
    firstRun1 = false;
  } // End First Run1 
  localStatus1 = ledTimer1.onceUpdate();
  if (localStatus1 == statusOnceOn) {
    Serial.println("Current Status in loop(), One-time(): On");
  }
  else if (localStatus1 == statusOnceOff) {
    Serial.println("Current Status in loop(), One-time(): Off");
    //ledStrip1.fill(ledStrip1.Color(0, 0, 0),1,30); //RGB
    ledStrip1.clear(); // Set all pixel colors to 'off'  
    ledStrip1.show();
    n = n + 2;
    firstRun9 = true;
  } // end else if statusOnceOff

//////////////////////////////////////////////////////////

// Effects mode
    if (firstRun9 == true) {
      Serial.println("In loop() - Start Effects Mode");
      ledTimer9.repeatSetup(200, 200, 1200);
      firstRun9 == false;
    }
  effectsStatus = ledTimer9.repeatUpdate();
  if (effectsStatus == statusRepeatOn) {
      Serial.println("Current Status in loop(): Effects On");
      mystrip1.colorWipe(ledStrip3.Color(100,   100,   0), 1); // Yellow
       delay(20);
  } // End if statusRepeatOn
  else if (effectsStatus == statusRepeatOff) {
    Serial.println("Current Status in loop(): Repeat Off");
      mystrip1.colorWipe(ledStrip3.Color(100,   100,   0), 1); // Yellow
    delay(20);
  } // End else if statusRepeatOff
  else if (effectsStatus == statusOff) {
    firstRun1 = true; // Ready of next one-time mode
    }// End else if statusOff  
} // End loop()

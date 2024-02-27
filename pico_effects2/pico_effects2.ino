
//#include <FastLED.h>
#include <Adafruit_NeoPixel.h>

/////////////////////////////////////////////////////////////////
// Data Constants
#define colorOrder GRB     // make the order RGB
#define numLeds1 30         //30 LEDs on the strip
#define numLeds2 30         //30 LEDs on the strip
#define numLeds3 30        //30 LEDs on the strip
#define numLeds4 30         //30 LEDs on the strip
#define ledPin1 16         // Led Strip 1 ouput pin
#define ledPin2           // Led Strip 2 ouput pin
#define ledPin3 18         // Led Strip 3 ouput pin
#define ledPin4 19          // Led Strip 4 ouput pin
//#define ledType WS2811   
#define statusOff 10        // Used by stripStatus
#define statusOn 11         // Used by stripStatus
#define statusRepeatOn 12   // Used by stripStatus
#define statusRepeatOff 13  // Used by stripStatus
#define statusOnceOn 14     // Used by stripStatus
#define statusOnceOff 15    // Used by stripStatus
#define repeatOnTime 21
#define repeatOffTime 22

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
  int timerOnOff;     
  bool enableTimer; // True when timer can run        
  // Used in timer Repeat mode

  // Constructor - creates an LedTimer and initializes some member variables
  public:
  LedTimer(String newLabel){
    timerLabel = newLabel;
    enableTimer = true;
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
    int localStatus; // Used in return statements
    String localString; // Used in print statements
    // check to see if it's time to make a change
    currentTime = millis();
    if ((enableTimer == true) && (currentTime <= endTime)) {
    //Check if timer is in on-time
    currentTime = millis();
    if((timerOnOff == repeatOnTime) && (currentTime - previousTime < onTime)) {
        localString = ("Running in on-time (repeatUpdate) for " + timerLabel);
        Serial.println(localString);
        localString = ("");
        localStatus = statusRepeatOn; // Still in on-time
     } // End check on-time
    //Check if timer on-time is expired  
    currentTime = millis();
    if((timerOnOff == repeatOnTime) && (currentTime - previousTime >= onTime)) {
        previousTime = currentTime;  // Remember the time
        timerOnOff = repeatOffTime; // Ready to start off-time
        localString = ("Finished on-time (repeatUpdate) for " + timerLabel);
        Serial.println(localString);
        localString = ("");
        localStatus = statusRepeatOff; // Now in Off-time
     } // End check on-time
    //Check if timer is in off-time
    currentTime = millis();
    if((timerOnOff == repeatOnTime) && (currentTime - previousTime < offTime)) {
        localString = ("Running in off-time (repeatUpdate) for " + timerLabel);
        Serial.println(localString);
        localString = ("");
        localStatus = statusRepeatOff; // Still in off-time
     } // End check off-time
    //Check if timer off-time is expired
    currentTime = millis();
    if ((timerOnOff == repeatOffTime) && (currentTime - previousTime >= offTime)) {
        previousTime = currentTime;  // Remember the time
        timerOnOff = repeatOnTime;   // Ready to start on-time
        localString = ("Finished off-time (repeatUpdate) for " + timerLabel);
        Serial.println(localString);
        localString = ("");
        localStatus = statusRepeatOn; // Now in On-time
    } // End check off-time
    } // End if <= End time
    // Check if End-time is reached
    currentTime = millis();
    if ((currentTime > endTime)){ // Reached end time for repeat mode
        localString = ("Reached end time (repeatUpdate) for " + timerLabel);
        Serial.println(localString);
        localString = ("");
        localStatus =  statusOff; // On/Off cycle is over
        enableTimer == false; // Timer will not run
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
      } // End if wipeCount1
      delay(wait);                           //  Pause for a moment   
      if (wipeCount1 >= ledStrip1.numPixels()){
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
    } // End if wipeCount3
      delay(wait);                           //  Pause for a moment    
    if (wipeCount3 >= ledStrip3.numPixels()){
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
bool firstRun1 = true;
bool firstRun3 = true;
bool runTimer = true;
int currentStatus;
int count1 = 0;
int count3 = 0;
int stripStatus1 = statusOff;
int stripStatus3 = statusOff;
/**
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
**/

/////////////////////////////////////////////////////////////////
LedTimer ledTimer1("LED 1 Strip");
LedTimer ledTimer3("LED 3 Strip");
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
    uint32_t magenta = ledStrip1.Color(255, 0, 255);
}
int n = 50;
void loop() {      
  bool localStatus;
  bool localStatus2;  
// Repeat mode using LED strip 3 and Timer 3
    if (firstRun3 == true) { // Start of the repeat cycle
      Serial.println("Start Repeat Mode");
      // xxx.fill(color, first, count);
      //ledStrip3.fill(ledStrip3.Color(15, 85, 15),1,30); //RGB
      // Start color 
      //ledStrip3.show(); 
      delay(200); // wait a moment before timer starts
      ledTimer3.repeatSetup(300, 300, 6500);
      delay(50);                                                              
      firstRun3 = false; // Run once per repeat cycle
    } // End First Run is true
  localStatus = ledTimer3.repeatUpdate();
  if (localStatus == statusRepeatOn) {
      Serial.println("Current Status in loop(): Repeat On");
      ledStrip3.fill(ledStrip3.Color(50, 0, 0),1,30); //RGB
      // On color
      ledStrip3.show(); 
      delay(20);
  } // End if
  else if (localStatus == statusRepeatOff) {
    Serial.println("Current Status in loop(): Repeat Off");
    ledStrip3.fill(ledStrip3.Color(0, 0, 50),1,30); //RGB
    // Off color
    ledStrip3.show();
    delay(20);
  } // End else if
  else if (localStatus == statusOff) {
    ledTimer3.enableTimer = false; //Turn of timer
    Serial.println("Current Status in loop(): Off; End time reached");
    //ledStrip3.fill(ledStrip3.Color(0, 0, 0),0,30); //RGB
    //ledStrip3.show();
    localStatus2 = mystrip3.colorWipe(ledStrip3.Color(255,   0,   0), 0); // Red
    //mystrip3.colorWipe(ledStrip3.Color(  0, 255,   0), 50); // Green
    //mystrip3.colorWipe(ledStrip3.Color(  0,   0, 255), 50); // Blue
    if (localStatus2 == false){
    }
    else if (localStatus2 == true){
      firstRun3 = true;  
      ledStrip3.clear();
      ledStrip3.show();
      count3 += 1;
    } // End else if localStatus
    delay(30);
    ledTimer3.enableTimer = true; //Ready for next repeat cycle
  }// End else if 

//////////////////////////////////////////////////////////

// One-time mode
    if (firstRun1 == true) {
    Serial.println("Start one-time");
    ledStrip1.fill(ledStrip1.Color(n, 25, 5),1,30); //RGB
    ledStrip1.show(); 
    ledTimer1.onceSetup(6500);
    firstRun1 = false;
  } // End First Run
  currentStatus = ledTimer1.onceUpdate();
  if (currentStatus == statusOnceOn) {
    Serial.println("Current Status in loop(), One-time): On");
  }
  else if (currentStatus == statusOnceOff) {
    Serial.println("Current Status (on-time): Off");
    ledStrip1.fill(ledStrip1.Color(0, 0, 0),1,30); //RGB
    //ledStrip1.clear(); // Set all pixel colors to 'off'  
    ledStrip1.show();
    //mystrip3.colorWipe(ledStrip3.Color(255,   0,   0), 50); // Red
    bool localStstus = mystrip3.colorWipe(ledStrip3.Color(  0, 255,   0), 50); // Green
    //mystrip3.colorWipe(ledStrip3.Color(  0,   0, 255), 50); // Blue
    if (localStstus == true){
      firstRun1 = true;  
      n = n + 5;
    } // End if localStstus    
    delay(30);
  }
}


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

#define picoRed ledStrip1.Color(255, 0, 0)
#define picoOrange ledStrip1.Color(255, 69, 0)
#define picoYellow ledStrip1.Color(255, 165, 0)
#define picoGreen ledStrip1.Color(0, 255, 0)
#define picoBlue ledStrip1.Color(0, 0, 255)
#define picoPurple ledStrip1.Color(147, 29, 147)
#define picoBlack ledStrip1.Color(0, 0, 0)

#define p_0 100
#define p_1 101
#define p_2 102
#define p_3 103
#define p_4 104
#define p_10 110
#define p_11 111
#define p_12 112
#define p_13 113
#define p_14 114
#define p_21 121
#define p_22 122
#define p_23 123
#define p_31 131
#define p_32 132
#define p_33 133

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
bool firstRun1 = true;
bool firstRun2 = true;
bool firstRun3 = true;
bool firstRun4 = true;

bool m0Status = false;
bool m1Status = false;
bool m2Status = true;
bool m3Status = false;
bool m4Status = false;
bool m11Status = false;
bool m12Status = false;

int stripStatus1 = statusOff;
int stripStatus2 = statusOff;
int stripStatus3 = statusOff;
int stripStatus4 = statusOff;

int timeOut1 = 3500;
int timeOut2 = timeOut1;
int timeOut3 = timeOut1;
int timeOut4 = timeOut1;

int onTime1 = 350;
int onTime2 = onTime1;
int onTime3 = onTime1;
int onTime4 = onTime1;

int offTime1 = onTime1;
int offTime2 = offTime1;
int offTime3 = offTime1;
int offTime4 = offTime1;

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

} // End setup()

//////////////////////////////////////////////////////////////////////
void loop() {    
  m0();
  m1();
  m2();
  m3();
  m4();
  m11();
  m12();
  //oneTimeLed(1, picoPurple, picoYellow, timeOut1);
  //repeatLed(1, picoRed, picoGreen, picoBlue, onTime1, offTime1, timeOut1);
} // End loop()
///////////////////////////////////////////////////////////////////////////////

int oneTimeLed(int newLedStrip, uint32_t newOnColor, uint32_t newOffColor, int newTimeOut){
  int localStatus;
  if (newLedStrip == 1) {
    if (firstRun1 == true) {
    // One-time Status:
    // statusOnceOn - Still in On-time
    // statusOnceOff - On-time is over
    Serial.println("Starting One-Time mode for ledStip1");
    ledStrip1.fill(newOnColor,0,numLeds1); // On-Color
    //ledStrip1.show(); 
    ledTimer1.onceSetup(newTimeOut);
    firstRun1 = false;
  } // End FirstRun1 
  localStatus = ledTimer1.onceUpdate();
  if (localStatus == statusOnceOn) {
    Serial.println("One-Time Mode is ON for ledStrip1");
    //delay(100);                                              //Updated
  } // End if statusOnceOn
  else if (localStatus == statusOnceOff) {
    Serial.println("One-Time is OFF for ledStrip1");
    ledStrip1.fill(newOffColor,0,numLeds1); // Off-Color
    //ledStrip1.show();
  } // end else if statusOnceOff
  } // End Led Strip is 1

////////////////////////////////////////////////////////////////////
  else if (newLedStrip == 2) {
    if (firstRun2 == true) {
    // One-time Status:
    // statusOnceOn - Still in On-time
    // statusOnceOff - On-time is over
    Serial.println("Starting One-Time mode for ledStip2");
    ledStrip2.fill(newOnColor,0,numLeds2); // On-Color
    //ledStrip2.show(); 
    ledTimer2.onceSetup(newTimeOut);
    firstRun2 = false;
  } // End FirstRun2 
  localStatus = ledTimer2.onceUpdate();
  if (localStatus == statusOnceOn) {
    Serial.println("One-Time Mode is ON for ledStrip2");
    //delay(100);                                              //Updated
  } // End if statusOnceOn
  else if (localStatus == statusOnceOff) {
    Serial.println("One-Time is OFF for ledStrip2");
    ledStrip2.fill(newOffColor,0,numLeds2); // Off-Color
    //ledStrip2.show();
  } // end else if statusOnceOff
  } // End Led Strip is 2

////////////////////////////////////////////////////////////////////
  else if (newLedStrip == 3) {
    if (firstRun3 == true) {
    // One-time Status:
    // statusOnceOn - Still in On-time
    // statusOnceOff - On-time is over
    Serial.println("Starting One-Time mode for ledStip3");
    ledStrip3.fill(newOnColor,0,numLeds3); // On-Color
    //ledStrip3.show(); 
    ledTimer3.onceSetup(newTimeOut);
    firstRun3 = false;
  } // End FirstRun3 
  localStatus = ledTimer3.onceUpdate();
  if (localStatus == statusOnceOn) {
    Serial.println("One-Time Mode is ON for ledStrip3");
    //delay(100);                                              //Updated
  } // End if statusOnceOn
  else if (localStatus == statusOnceOff) {
    Serial.println("One-Time is OFF for ledStrip3");
    ledStrip3.fill(newOffColor,0,numLeds3); // Off-Color
    //ledStrip3.show();
  } // end else if statusOnceOff
  } // End Led Strip is 3

////////////////////////////////////////////////////////////////////
  else if (newLedStrip == 4) {
     if (firstRun4 == true) {
    // One-time Status:
    // statusOnceOn - Still in On-time
    // statusOnceOff - On-time is over
    Serial.println("Starting One-Time mode for ledStip4");
    ledStrip4.fill(newOnColor,0,numLeds4); // On-Color
    //ledStrip4.show(); 
    ledTimer4.onceSetup(newTimeOut);
    firstRun4 = false;
  } // End FirstRun4 
  localStatus = ledTimer4.onceUpdate();
  if (localStatus == statusOnceOn) {
    Serial.println("One-Time Mode is ON for ledStrip4");
    //delay(100);                                              //Updated
  } // End if statusOnceOn
  else if (localStatus == statusOnceOff) {
    Serial.println("One-Time is OFF for ledStrip4");
    ledStrip4.fill(newOffColor,0,numLeds4); // Off-Color
    //ledStrip4.show();
  } // end else if statusOnceOff
  } // End Led Strip is 4  
  return localStatus;
} // End oneTimeLed()

////////////////////////////////////////////////////////////////////

int repeatLed(int newLedStrip, uint32_t newOnColor, uint32_t newOffColor, uint32_t localBlack, int newOnTime, int newOffTime, int newRunTime) {
  int localStatus;
  if (newLedStrip == 1) {
    if (firstRun1 == true) { // Start of the repeat cycle
    // Repeat Mode Status:
    // statusRepeatOn - current time is < onTime; still in on-time
    // statusRepeatOff - current time is < offTime; still in off-time
    // statusOff - currrent time is > endTime; repeat mode is complete
      Serial.println("Starting Repeat mode for ledStip1");
      //delay(100); // wait a moment before timer starts                    //Updated
      ledTimer1.repeatSetup(newOnTime, newOffTime, newRunTime);
      firstRun1 = false; // Run once per repeat cycle    
    } // End FirstRun1 
  localStatus = ledTimer1.repeatUpdate(); // Checking on timer status
  if (localStatus == statusRepeatOn) {
      Serial.println("Current Status in loop(): Repeat On for ledstrip1");   //Updated
      // xxx.fill(color, first, count);
      ledStrip1.fill(newOnColor,0,numLeds1); // On-Color
      //ledStrip1.show(); 
      //delay(100);                                                          //Updated
  } // End if statusRepeatOn
  else if (localStatus == statusRepeatOff) {
      Serial.println("Current Status in loop(): Repeat Off for ledstrip1");   //Updated
    ledStrip1.fill(newOffColor,0,numLeds1); // Off-Color
    //ledStrip1.show();
    //delay(100);                                                                //Updated
  } // End else if statusRepeatOff
  else if (localStatus == statusOff) {
    //firstRun1 = true; // Ready of next repeat cycle
    Serial.println("Current Status in loop(): Off; End time reached for ledstrip1"); //Updated
    ledStrip1.fill(localBlack,0,numLeds1);
    //ledStrip1.show();
    //delay(100);                                                               //Updated
    }// End else if statusOff
  } // End ledStrip1
////////////////////////////////////////////////////////////////////
  if (newLedStrip == 2) {
    if (firstRun2 == true) { // Start of the repeat cycle
    // Repeat Mode Status:
    // statusRepeatOn - current time is < onTime; still in on-time
    // statusRepeatOff - current time is < offTime; still in off-time
    // statusOff - currrent time is > endTime; repeat mode is complete
      Serial.println("Starting Repeat mode for ledStip2");
      // xxx.fill(color, first, count);
      //delay(100); // wait a moment before timer starts                      //Updated
      ledTimer2.repeatSetup(newOnTime, newOffTime, newRunTime);
      firstRun2 = false; // Run once per repeat cycle    
    } // End FirstRun2 
  localStatus = ledTimer2.repeatUpdate(); // Checking on timer status
  if (localStatus == statusRepeatOn) {
      Serial.println("Current Status in loop(): Repeat On for ledstrip2");   //Updated
      ledStrip2.fill(newOnColor,0,numLeds2); // On-Color
      //ledStrip2.show(); 
      //delay(100);                                                          //Updated
  } // End if statusRepeatOn
  else if (localStatus == statusRepeatOff) {
      Serial.println("Current Status in loop(): Repeat Off for ledstrip2");   //Updated
    ledStrip2.fill(newOffColor,0,numLeds2); // Off-Color
    //ledStrip2.show();
    //delay(100);                                                             //Updated
  } // End else if statusRepeatOff
  else if (localStatus == statusOff) {
    //firstRun2 = true; // Ready of next repeat cycle
    Serial.println("Current Status in loop(): Off; End time reached for ledstrip2"); //Updated
    ledStrip2.fill(localBlack,0,numLeds2);
    //ledStrip2.show();
    //delay(100);                                                            //Updated
    }// End else if statusOff
  } // End ledStrip2

////////////////////////////////////////////////////////////////////
  if (newLedStrip == 3) {
    if (firstRun3 == true) { // Start of the repeat cycle
    // Repeat Mode Status:
    // statusRepeatOn - current time is < onTime; still in on-time
    // statusRepeatOff - current time is < offTime; still in off-time
    // statusOff - currrent time is > endTime; repeat mode is complete
      Serial.println("Starting Repeat mode for ledStip3");
      // xxx.fill(color, first, count);
      //delay(100); // wait a moment before timer starts                      //Updated
      ledTimer3.repeatSetup(newOnTime, newOffTime, newRunTime);
      firstRun3 = false; // Run once per repeat cycle    
    } // End FirstRun3 
  localStatus = ledTimer3.repeatUpdate(); // Checking on timer status
  if (localStatus == statusRepeatOn) {
      Serial.println("Current Status in loop(): Repeat On for ledstrip3");   //Updated
      ledStrip3.fill(newOnColor,0,numLeds3); // On-Color
      //ledStrip3.show(); 
    //delay(100);                                                             //Updated
  } // End if statusRepeatOn
  else if (localStatus == statusRepeatOff) {
          Serial.println("Current Status in loop(): Repeat Off for ledstrip3");   //Updated
    ledStrip3.fill(newOffColor,0,numLeds3); // Off-Color
    //ledStrip3.show();
    //delay(100);                                                                 //Updated
  } // End else if statusRepeatOff
  else if (localStatus == statusOff) {
    //firstRun3 = true; // Ready of next repeat cycle
    Serial.println("Current Status in loop(): Off; End time reached for ledstrip3"); //Updated
    ledStrip3.fill(localBlack,0,numLeds3);
    //ledStrip3.show();
    //delay(100);                                                             //Updated
    }// End else if statusOff
  } // End ledStrip3

////////////////////////////////////////////////////////////////////
  if (newLedStrip == 4) {
    if (firstRun4 == true) { // Start of the repeat cycle
    // Repeat Mode Status:
    // statusRepeatOn - current time is < onTime; still in on-time
    // statusRepeatOff - current time is < offTime; still in off-time
    // statusOff - currrent time is > endTime; repeat mode is complete
      Serial.println("Starting Repeat mode for ledStip4");
      // xxx.fill(color, first, count);
      //delay(100); // wait a moment before timer starts                        //Updated
      ledTimer4.repeatSetup(newOnTime, newOffTime, newRunTime);
      firstRun4 = false; // Run once per repeat cycle    
    } // End FirstRun4 
  localStatus = ledTimer4.repeatUpdate(); // Checking on timer status
  if (localStatus == statusRepeatOn) {
      Serial.println("Current Status in loop(): Repeat On for ledstrip4");   //Updated
      ledStrip4.fill(newOnColor,0,numLeds4); // On-Color
      //ledStrip4.show(); 
    //delay(100);                                                             //Updated
  } // End if statusRepeatOn
  else if (localStatus == statusRepeatOff) {
      Serial.println("Current Status in loop(): Repeat Off for ledstrip4");   //Updated
    ledStrip4.fill(newOffColor,0,numLeds4); // Off-Color
    //ledStrip4.show();
    //delay(100);                                                             //Updated
  } // End else if statusRepeatOff
  else if (localStatus == statusOff) {
    //firstRun4 = true; // Ready of next repeat cycle
    Serial.println("Current Status in loop(): Off; End time reached for ledstrip4"); //Updated
    ledStrip4.fill(localBlack,0,numLeds4);
    //ledStrip4.show();
    //delay(100);                                                             //Updated
    }// End else if statusOff
  } // End ledStrip4
  return localStatus;    
} // End repeatLedUpdate()

void m0(){
  if (m0Status == true){
    oneTimeLed(1, picoBlack, picoBlack, timeOut1);
    oneTimeLed(2, picoBlack, picoBlack, timeOut2);
    oneTimeLed(3, picoBlack, picoBlack, timeOut3);
    oneTimeLed(4, picoBlack, picoBlack, timeOut4);
  } // End m0Status
} // End m0()

void m1(){
  if (m1Status == true){
    int localStatus = 0;
    oneTimeLed(1, picoRed, picoBlack, timeOut1);
    oneTimeLed(2, picoRed, picoBlack, timeOut2);
    oneTimeLed(3, picoRed, picoBlack, timeOut3);
    localStatus = oneTimeLed(4, picoRed, picoBlack, timeOut4);
    if (localStatus == statusOnceOff) {
      Serial.println("statusOnceOff");
      m1Status = false;  
    } // End if statusOnceOff
  } // End m1Status
  
} // End m1()

void m2(){
  if (m2Status == true){
    int localStatus = 0;
    oneTimeLed(1, picoYellow, picoBlack, timeOut1);
    oneTimeLed(2, picoYellow, picoBlack, timeOut2);
    oneTimeLed(3, picoYellow, picoBlack, timeOut3);
    localStatus = oneTimeLed(4, picoYellow, picoBlack, timeOut4);
    if (localStatus == statusOnceOff) {
      Serial.println("statusOnceOff");
      m2Status = false;  
    } // End if statusOnceOff
  } // End m2Status
  updateAll();
} // End m2()

void m3(){
  if (m3Status == true){
    int localStatus = 0;
    oneTimeLed(1, picoGreen, picoBlack, timeOut1);
    oneTimeLed(2, picoGreen, picoBlack, timeOut2);
    oneTimeLed(3, picoGreen, picoBlack, timeOut3);
    localStatus = oneTimeLed(4, picoGreen, picoBlack, timeOut4);
    if (localStatus == statusOnceOff) {
      Serial.println("statusOff");
      m3Status = false;  
    } // End if statusOnceOff    
  } // End m3Status
  updateAll();
} // End m3()

void m4(){
  if (m4Status == true){
    int localStatus = 0;
    oneTimeLed(1, picoBlue, picoBlack, timeOut1);
    oneTimeLed(2, picoBlue, picoBlack, timeOut2);
    oneTimeLed(3, picoBlue, picoBlack, timeOut3);
    localStatus = oneTimeLed(4, picoBlue, picoBlack, timeOut4);
    if (localStatus == statusOnceOff) {
      Serial.println("statusOff");
      m4Status = false;  
    } // End if statusOnceOff   
  } // End m4Status
  updateAll();
} // End m4()

void m11(){
  if (m11Status == true){
  int localStatus = 0;
  repeatLed(1, picoBlue, picoBlack, picoBlack, onTime1, offTime1, timeOut1);
  repeatLed(2, picoBlue, picoBlack, picoBlack, onTime2, offTime2, timeOut2);
  repeatLed(3, picoBlue, picoBlack, picoBlack, onTime3, offTime3, timeOut3);
  localStatus = repeatLed(4, picoBlue, picoBlack, picoBlack, onTime4, offTime4, timeOut4);
  if (localStatus == statusOff) {
    Serial.println("statusOff");
    m11Status = false;  
    } // End if statusOnceOff   
  } // End m11Status
  updateAll();
} // End m11()

void m12(){
  if (m12Status == true){
  int localStatus = 0;
  repeatLed(1, picoRed, picoGreen, picoBlack, onTime1, offTime1, timeOut1);
  repeatLed(2, picoRed, picoGreen, picoBlack, onTime2, offTime2, timeOut2);
  repeatLed(3, picoRed, picoGreen, picoBlack, onTime3, offTime3, timeOut3);
  localStatus = repeatLed(4, picoRed, picoGreen, picoBlack, onTime4, offTime4, timeOut4);
  if (localStatus == statusOff) {
    Serial.println("statusOff");
    m12Status = false;  
    } // End if statusOnceOff   
  } // End m12Status
  updateAll();
} // End m12()

void updateAll(){
  ledStrip1.show();
  ledStrip2.show();
  ledStrip3.show();
  ledStrip4.show();
}

void parameters(int newParam){
  int localParam = newParam;
  switch(localParam) {
  case p_0:
    firstRun1 = true; firstRun2 = true; firstRun3 = true; firstRun4 = true;
    break;
  case p_1:
    firstRun1 = true; firstRun2 = false; firstRun3 = false; firstRun4 = false;
    break;
  case p_2:
    firstRun1 = false; firstRun2 = true; firstRun3 = false; firstRun4 = false;
    break;
  case p_3:
    firstRun1 = false; firstRun2 = false; firstRun3 = true; firstRun4 = false;
    break;
  case p_4:
    firstRun1 = false; firstRun2 = false; firstRun3 = false; firstRun4 = true;
    break;
  case p_10:
    firstRun1 = false; firstRun2 = false; firstRun3 = false; firstRun4 = false;
    break;
  case p_11:
    firstRun1 = false; firstRun2 = true; firstRun3 = true; firstRun4 = true;  
    break;
  case p_12:
    firstRun1 = true; firstRun2 = false; firstRun3 = true; firstRun4 = true;  
    break;
  case p_13:
    firstRun1 = true; firstRun2 = true; firstRun3 = false; firstRun4 = true;  
    break;
  case p_14:
    firstRun1 = true; firstRun2 = true; firstRun3 = true; firstRun4 = false;  
    break;
  case p_21:
    onTime1 = 750;
    break;
  case p_22:
    onTime1 = 350;
    break;
  case p_23:
    onTime1 = 175;
    break;
  case p_31:
    timeOut1 = 1750;
    break;
  case p_32:
    timeOut1 = 3500;
    break;
  case p_33:
    timeOut1 = 7000;
    break;
  default:
    break;
  } // End switch
} // End parameters()
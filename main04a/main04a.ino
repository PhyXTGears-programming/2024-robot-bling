
#include <string>
#include "RingBuffer.h"
#include <Adafruit_NeoPixel.h>

CassiusRingBuffer buff;

/////////////////////////////////////////////////////////////////
// Data Constants
#define numLedsClimber1 20    // Climber #1
#define numLedsClimber2 20    // Climber #2
#define numLedsTrap 36        // Trap
#define numLedsSpeaker 40     // Speaker

#define ledPinClimber1 16     // Climber #1 ouput pin
#define ledPinClimber2 17     // Climber #2 ouput pin
#define ledPinTrap 18         // Trap ouput pin
#define ledPinSpeaker 19      // Speaker ouput pin

// Used by stripStatus
#define statusOff 10        // Unit is off
#define statusOn 11         // Unit is on
#define statusRepeatOn 12   // Repeat mode is on
#define statusRepeatOff 13  // Repeat mode is off
#define statusOnceOn 14     // One-time mode is on
#define statusOnceOff 15    // One-time mode is off

#define shortTimeout 750
#define midTimeout 1500
#define intTimeout 2500

#define fastRate 250
#define midRate 350
#define slowRate 450

#define picoRed ledsClimber1.Color(255, 0, 0)
#define picoOrange ledsClimber1.Color(255, 69, 0)
#define picoYellow ledsClimber1.Color(255, 165, 0)
#define picoGreen ledsClimber1.Color(0, 255, 0)
#define picoBlue ledsClimber1.Color(0, 0, 255)
#define picoPurple ledsClimber1.Color(147, 29, 147)
#define picoBlack ledsClimber1.Color(0, 0, 0)

/////////////////////////////////////////////////////////////////
// Global control parameters
// Will enable/disable timers
bool startTimerClimber1 = false;
bool startTimerClimber2 = false;
bool startTimerTrap = false;
bool startTimerSpeaker = false;

// Status of each timer
int timerStatusClimber1 = statusOff;
int timerStatusClimber2 = statusOff;
int timerStatusTrap = statusOff;
int timerStatusSpeaker = statusOff;

long timeOut1 = 750;
long timeOut2 = timeOut1;
long timeOut3 = timeOut1;
long timeOut4 = timeOut1;

long onTime1 = midRate;
long onTime2 = onTime1;
long onTime3 = onTime1;
long onTime4 = onTime1;

long offTime1 = onTime1;
long offTime2 = offTime1;
long offTime3 = offTime1;
long offTime4 = offTime1;

// Will enable/disable modes
bool mode0Enable = false;
bool mode1Enable = false;
bool mode2Enable = false;
bool mode3Enable = false;
bool mode4Enable = false;
bool mode11Enable = false;
bool mode12Enable = false;

/////////////////////////////////////////////////////////////////

// Needed here before Class ledEffects
Adafruit_NeoPixel ledsClimber1(numLedsClimber1, ledPinClimber1, NEO_GRB + NEO_KHZ800); 
Adafruit_NeoPixel ledsClimber2(numLedsClimber2, ledPinClimber2, NEO_GRB + NEO_KHZ800); 
Adafruit_NeoPixel ledsTrap(numLedsTrap, ledPinTrap, NEO_GRB + NEO_KHZ800); 
Adafruit_NeoPixel ledsSpeaker(numLedsSpeaker, ledPinSpeaker, NEO_GRB + NEO_KHZ800); 

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
  long previousTime; // will store last time change was made
  long currentTime;  // will store current time
  //int timerOnOff;             // Used to track on/off cycles in repeat mode
  String localString; // Used in print statements
  int localStatus; // Used in return statements

  // Constructor - creates an LedTimer and initializes some member variables
  public:
  LedTimer(String newLabel){
    timerLabel = newLabel; // Used in print statements
    } // End Create Timer
  
  // Used to initialize repeat mode.
  void repeatSetup(long newOnTime, long newOffTime, long newRunTime){
    onTime = newOnTime;
    offTime = newOffTime;
    previousTime = millis(); // Timer has started
    endTime = previousTime + newRunTime;
    localStatus = statusRepeatOn; //Start in on-time
  } // End of repeatSetup()

  int repeatUpdate() {
    // Repeat Mode Status
    // statusRepeatOn - current time is < onTime; still in on-time
    // statusRepeatOff - current time is < offTime; still in off-time
    // statusOff - currrent time is >= endTime; repeat mode is complete
    
    // Is it time to make a change?
    currentTime = millis();
    if ((localStatus == statusRepeatOn) && (currentTime - previousTime < onTime) && (currentTime < endTime)) {
        localString = ("repeatUpdate: In on-time for " + timerLabel);
        Serial.println(localString);
        localString = ("");
        localStatus = statusRepeatOn; // Returning: "In on-time"
     } // End check on-time
    //Check if timer on-time is expired
    else if ((localStatus == statusRepeatOn) && (currentTime - previousTime >= onTime) && (currentTime < endTime)) {
        previousTime = currentTime;  // Remember the start of off-time
        localString = ("repeatUpdate: Finished on-time for " + timerLabel);
        Serial.println(localString);
        localString = ("");
        localStatus = statusRepeatOff; // Returning: "In off-time"
     } // End check on-time
    //Check if timer is in off-time
    else if ((localStatus == statusRepeatOff) && (currentTime - previousTime < offTime) && (currentTime < endTime)) {
        localString = ("repeatUpdate: In off-time for " + timerLabel);
        Serial.println(localString);
        localString = ("");
        localStatus = statusRepeatOff; // Returning: "In off-time"
     } // End check off-time
    //Check if timer off-time is expired
    else if ((localStatus == statusRepeatOff) && (currentTime - previousTime >= offTime) && (currentTime < endTime)) {
        previousTime = currentTime;  // Remember the time
        localString = ("Finished off-time (repeatUpdate) for " + timerLabel);
        Serial.println(localString);
        localString = ("");
        localStatus = statusRepeatOn; // Returning: "In on-time"
    } // End check off-time
    // Check if End-time is reached
    currentTime = millis();
    if ((currentTime >= endTime)){ // Reached end time for repeat mode
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
    Serial.printf("onceSetup: previousTime is: %u \r\n", previousTime);
    Serial.printf("onceSetup: endTime is: %u \r\n", endTime);
    } // End onceSetup()

  int onceUpdate(){
    currentTime = millis();
    if (currentTime < endTime) {
      Serial.printf("onceUpdate: currrentTime is: %u \r\n", currentTime);
      localStatus =  statusOnceOn; // Still in On-time
      localString = ("onceUpdate: In on-time for " + timerLabel);
      Serial.println(localString);
      delay(100);
    } // End if
    currentTime = millis();
    if (currentTime >= endTime) {
      Serial.printf("onceUpdate: currrentTime is: %u \r\n", currentTime);
      localStatus =  statusOnceOff; // On-time is over
      localString = ("onceUpdate: Reached end time for " + timerLabel);
      Serial.println(localString);
    } // End Else
    return localStatus;
  } // End of onceUpdate()

}; //End of LedTimer Class

////////////////////////////////////////////////////////////////
LedTimer timerClimber1("Timer-Climber1");
LedTimer timerClimber2("Timer-Climber2");
LedTimer timerTrap("Timer-Trap");
LedTimer timerSpeaker("Timer-Speaker");
/////////////////////////////////////////////////////////////////

void setup() {
    Serial.begin(115200);
    delay(3000);
    ledsClimber1.begin(); // INITIALIZE NeoPixel strip object
    ledsClimber1.fill(ledsClimber1.Color(0, 0, 0),0,30); //RGB
    ledsClimber1.show(); // Set all pixel colors to 'off'
    ledsClimber1.setBrightness(65);
    ledsClimber1.clear();
    ledsClimber1.show();
    ledsTrap.begin(); // INITIALIZE NeoPixel strip object
    ledsTrap.show();
    ledsTrap.setBrightness(65);

} // End setup()

//////////////////////////////////////////////////////////////////////
void loop() {    
  mode0();
  mode1();
  mode2();
  mode3();
  mode4();
  mode11();
  mode12();
} // End loop()
///////////////////////////////////////////////////////////////////////////////

int onceLed(int newLedStrip, uint32_t newOnColor, uint32_t newOffColor, long newTimeOut){
  int localStatus;
  if (newLedStrip == 1) {
    if (startTimerClimber1 == true) {
    // One-time Status:
    // statusOnceOn - Still in On-time
    // statusOnceOff - On-time is over
    Serial.println("onceLed: Starting One-Time mode for ledsClimber1");
    ledsClimber1.fill(newOnColor,0,numLedsClimber1); // On-Color
    ledsClimber1.show(); 
    timerClimber1.onceSetup(newTimeOut);
    startTimerClimber1 = false;
  } // End startTimerClimber1 
  localStatus = timerClimber1.onceUpdate();
  if (localStatus == statusOnceOn) {
    Serial.println("onceLed: One-Time Mode is ON for ledsClimber1");
    delay(100);
  } // End if statusOnceOn
  else if (localStatus == statusOnceOff) {
    Serial.println("onceLed: One-Time is OFF for ledsClimber1");
    ledsClimber1.fill(newOffColor,0,numLedsClimber1); // Off-Color
    ledsClimber1.show();
  } // end else if statusOnceOff
  } // End Led Strip is 1
////////////////////////////////////////////////////////////////////
  else if (newLedStrip == 2) {
    if (startTimerClimber2 == true) {
    Serial.println("onceLed: Starting One-Time mode for ledStip2");
    ledsClimber2.fill(newOnColor,0,numLedsClimber2); // On-Color
    ledsClimber2.show(); 
    timerClimber2.onceSetup(newTimeOut);
    startTimerClimber2 = false;
  } // End startTimerClimber2 
  localStatus = timerClimber2.onceUpdate();
  if (localStatus == statusOnceOn) {
    Serial.println("onceLed: One-Time Mode is ON for ledsClimber2");
    delay(100);
  } // End if statusOnceOn
  else if (localStatus == statusOnceOff) {
    Serial.println("onceLed: One-Time is OFF for ledsClimber2");
    ledsClimber2.fill(newOffColor,0,numLedsClimber2); // Off-Color
    ledsClimber2.show();
  } // end else if statusOnceOff
  } // End Led Strip is 2
////////////////////////////////////////////////////////////////////
  else if (newLedStrip == 3) {
    if (startTimerTrap == true) {
    Serial.println("onceLed: Starting One-Time mode for ledStip3");
    ledsTrap.fill(newOnColor,0,numLedsTrap); // On-Color
    ledsTrap.show(); 
    timerTrap.onceSetup(newTimeOut);
    startTimerTrap = false;
  } // End startTimerTrap 
  localStatus = timerTrap.onceUpdate();
  if (localStatus == statusOnceOn) {
    Serial.println("onceLed: One-Time Mode is ON for ledsTrap");
    delay(100);
  } // End if statusOnceOn
  else if (localStatus == statusOnceOff) {
    Serial.println("One-Time is OFF for ledsTrap");
    ledsTrap.fill(newOffColor,0,numLedsTrap); // Off-Color
    ledsTrap.show();
  } // end else if statusOnceOff
  } // End Led Strip is 3
////////////////////////////////////////////////////////////////////
  else if (newLedStrip == 4) {
     if (startTimerSpeaker == true) {
    Serial.println("onceLed: Starting One-Time mode for ledStip4");
    ledsSpeaker.fill(newOnColor,0,numLedsSpeaker); // On-Color
    ledsSpeaker.show(); 
    timerSpeaker.onceSetup(newTimeOut);
    startTimerSpeaker = false;
  } // End startTimerSpeaker 
  localStatus = timerSpeaker.onceUpdate();
  if (localStatus == statusOnceOn) {
    Serial.println("onceLed: One-Time Mode is ON for ledsSpeaker");
    delay(100);
  } // End if statusOnceOn
  else if (localStatus == statusOnceOff) {
    Serial.println("onceLed: One-Time is OFF for ledsSpeaker");
    ledsSpeaker.fill(newOffColor,0,numLedsSpeaker); // Off-Color
    ledsSpeaker.show();
  } // end else if statusOnceOff
  } // End Led Strip is 4  
  return localStatus;
} // End onceLed()
////////////////////////////////////////////////////////////////////

int repeatLed(int newLedStrip, uint32_t newOnColor, uint32_t newOffColor, uint32_t localBlack, long newOnTime, long newOffTime, long newRunTime) {
  int localStatus;
  if (newLedStrip == 1) {
    if (startTimerClimber1 == true) { // Start of the repeat cycle
    // Repeat Mode Status:
    // statusRepeatOn - current time is < onTime; still in on-time
    // statusRepeatOff - current time is < offTime; still in off-time
    // statusOff - currrent time is >= endTime; repeat mode is complete
    Serial.println("repeatLed: Starting Repeat mode for ledStip1");
      delay(100); // wait a moment before timer starts
      timerClimber1.repeatSetup(newOnTime, newOffTime, newRunTime);
      //delay(100);                                                              
      startTimerClimber1 = false; // Run once per repeat cycle    
    } // End startTimerClimber1 
  localStatus = timerClimber1.repeatUpdate(); // Checking on timer status
  if (localStatus == statusRepeatOn) {
      Serial.println("repeatLed: Current Status in loop(): Repeat On");
      // xxx.fill(color, first, count);
      ledsClimber1.fill(newOnColor,0,numLedsClimber1); // On-Color
      ledsClimber1.show(); 
      delay(100);
  } // End if statusRepeatOn
  else if (localStatus == statusRepeatOff) {
    Serial.println("repeatLed: Current Status in loop(): Repeat Off");
    ledsClimber1.fill(newOffColor,0,numLedsClimber1); // Off-Color
    ledsClimber1.show();
    delay(100);
  } // End else if statusRepeatOff
  else if (localStatus == statusOff) {
    //startTimerClimber1 = true; // Ready of next repeat cycle
    Serial.println("repeatLed: Current Status in loop(): Off; End time reached");
    ledsClimber1.fill(localBlack,0,numLedsClimber1);
    ledsClimber1.show();
    delay(100);
    }// End else if statusOff
  } // End ledsClimber1
////////////////////////////////////////////////////////////////////
  if (newLedStrip == 2) {
    if (startTimerClimber2 == true) { // Start of the repeat cycle
      Serial.println("repeatLed: Starting Repeat mode for ledStip2");
      // xxx.fill(color, first, count);
      ledsClimber2.fill(newOffColor,0,numLedsClimber2); // Off-Color
      ledsClimber2.show(); 
      delay(100); // wait a moment before timer starts
      timerClimber2.repeatSetup(newOnTime, newOffTime, newRunTime);
      delay(100);                                                              
      startTimerClimber2 = false; // Run once per repeat cycle    
    } // End startTimerClimber2 
  localStatus = timerClimber2.repeatUpdate(); // Checking on timer status
  if (localStatus == statusRepeatOn) {
      Serial.println("repeatLed: Current Status in loop(): Repeat On");
      ledsClimber2.fill(newOnColor,0,numLedsClimber2); // On-Color
      ledsClimber2.show(); 
      delay(100);
  } // End if statusRepeatOn
  else if (localStatus == statusRepeatOff) {
    Serial.println("repeatLed: Current Status in loop(): Repeat Off");
    ledsClimber2.fill(newOffColor,0,numLedsClimber2); // Off-Color
    ledsClimber2.show();
    delay(100);
  } // End else if statusRepeatOff
  else if (localStatus == statusOff) {
    //startTimerClimber2 = true; // Ready of next repeat cycle
    Serial.println("repeatLed: Current Status in loop(): Off; End time reached");
    ledsClimber2.fill(localBlack,0,numLedsClimber2);
    ledsClimber2.show();
    delay(100);
    }// End else if statusOff
  } // End ledsClimber2

////////////////////////////////////////////////////////////////////
  if (newLedStrip == 3) {
    if (startTimerTrap == true) { // Start of the repeat cycle
      Serial.println("repeatLed: Starting Repeat mode for ledStip3");
      // xxx.fill(color, first, count);
      ledsTrap.fill(newOffColor,0,numLedsTrap); // Off-Color
      ledsTrap.show(); 
      delay(100); // wait a moment before timer starts
      timerTrap.repeatSetup(newOnTime, newOffTime, newRunTime);
      delay(100);                                                              
      startTimerTrap = false; // Run once per repeat cycle    
    } // End startTimerTrap 
  localStatus = timerTrap.repeatUpdate(); // Checking on timer status
  if (localStatus == statusRepeatOn) {
      Serial.println("repeatLed: Current Status in loop(): Repeat On");
      ledsTrap.fill(newOnColor,0,numLedsTrap); // On-Color
      ledsTrap.show(); 
      delay(100);
  } // End if statusRepeatOn
  else if (localStatus == statusRepeatOff) {
    Serial.println("repeatLed: Current Status in loop(): Repeat Off");
    ledsTrap.fill(newOffColor,0,numLedsTrap); // Off-Color
    ledsTrap.show();
    delay(100);
  } // End else if statusRepeatOff
  else if (localStatus == statusOff) {
    //startTimerTrap = true; // Ready of next repeat cycle
    Serial.println("repeatLed: Current Status in loop(): Off; End time reached");
    ledsTrap.fill(localBlack,0,numLedsTrap);
    ledsTrap.show();
    delay(100);
    }// End else if statusOff
  } // End ledsTrap

////////////////////////////////////////////////////////////////////
  if (newLedStrip == 4) {
    if (startTimerSpeaker == true) { // Start of the repeat cycle
      Serial.println("repeatLed: Starting Repeat mode for ledStip4");
      // xxx.fill(color, first, count);
      ledsSpeaker.fill(newOffColor,0,numLedsSpeaker); // Off-Color
      ledsSpeaker.show(); 
      delay(100); // wait a moment before timer starts
      timerSpeaker.repeatSetup(newOnTime, newOffTime, newRunTime);
      delay(100);                                                              
      startTimerSpeaker = false; // Run once per repeat cycle    
    } // End startTimerSpeaker 
  localStatus = timerSpeaker.repeatUpdate(); // Checking on timer status
  if (localStatus == statusRepeatOn) {
      Serial.println("repeatLed: Current Status in loop(): Repeat On");
      ledsSpeaker.fill(newOnColor,0,numLedsSpeaker); // On-Color
      ledsSpeaker.show(); 
      delay(100);
  } // End if statusRepeatOn
  else if (localStatus == statusRepeatOff) {
    Serial.println("repeatLed: Current Status in loop(): Repeat Off");
    ledsSpeaker.fill(newOffColor,0,numLedsSpeaker); // Off-Color
    ledsSpeaker.show();
    delay(100);
  } // End else if statusRepeatOff
  else if (localStatus == statusOff) {
    //startTimerSpeaker = true; // Ready of next repeat cycle
    Serial.println("repeatLed: Current Status in loop(): Off; End time reached");
    ledsSpeaker.fill(localBlack,0,numLedsSpeaker);
    ledsSpeaker.show();
    delay(100);
    }// End else if statusOff
  } // End ledsSpeaker
  return localStatus;    
} // End repeatLedUpdate()

void mode0(){
  if (mode0Enable == true){
    onceLed(1, picoBlack, picoBlack, timeOut1);
    //onceLed(2, picoBlack, picoBlack, timeOut2);
    //onceLed(3, picoBlack, picoBlack, timeOut3);
    //onceLed(4, picoBlack, picoBlack, timeOut4);
  } // End mode0Enable
} // End mode0()

void mode1(){
  if (mode1Enable == true){
    int localStatus = 0;
    startTimerClimber1 = true;
    localStatus = onceLed(1, picoRed, picoBlack, timeOut1);
    if (localStatus == statusOnceOff) {
      Serial.println("Mode-1: M1 statusOnceOff");
      mode1Enable = false;
      startTimerClimber1 = false;
    } // End if statusOnceOff
    
    //onceLed(2, picoRed, picoBlack, timeOut2);
    //onceLed(3, picoRed, picoBlack, timeOut3);
    //onceLed(4, picoRed, picoBlack, timeOut4);
  } // End mode1Enable
} // End mode1()

void mode2(){
  if (mode2Enable == true){
    int localStatus = 0;
    startTimerClimber1 = true;
    onceLed(1, picoYellow, picoBlack, timeOut1);
    //onceLed(2, picoYellow, picoBlack, timeOut2);
    //onceLed(3, picoYellow, picoBlack, timeOut3);
    localStatus = onceLed(4, picoYellow, picoBlack, timeOut4);
    if (localStatus == statusOnceOff) {
      Serial.println("Mode-2: M2 statusOnceOff");
      mode2Enable = false;
      startTimerClimber1 = false;  
    } // End if statusOnceOff
  } // End mode2Enable
} // End mode2()

void mode3(){
  if (mode3Enable == true){
    int localStatus = 0;
    startTimerClimber1 = true;    
    onceLed(1, picoGreen, picoBlack, timeOut1);
    //onceLed(2, picoGreen, picoBlack, timeOut2);
    //onceLed(3, picoGreen, picoBlack, timeOut3);
    localStatus = onceLed(4, picoGreen, picoBlack, timeOut4);
    if (localStatus == statusOnceOff) {
      Serial.println("Mode-3: M3 statusOff");
      mode3Enable = false;  
      startTimerClimber1 = false;
    } // End if statusOnceOff    
  } // End mode3Enable
} // End mode3()

void mode4(){
  if (mode4Enable == true){
    int localStatus = 0;
    startTimerClimber1 = true;    
    onceLed(1, picoBlue, picoBlack, timeOut1);
    //onceLed(2, picoBlue, picoBlack, timeOut2);
    //onceLed(3, picoBlue, picoBlack, timeOut3);
    localStatus = onceLed(4, picoBlue, picoBlack, timeOut4);
    if (localStatus == statusOnceOff) {
      Serial.println("Mode-4: M4 statusOff");
      mode4Enable = false;  
      startTimerClimber1 = false;
    } // End if statusOnceOff   
  } // End mode4Enable
} // End mode4()

void mode11(){
  if (mode11Enable == true){
  int localStatus = 0;
  startTimerClimber1 = true;
  repeatLed(1, picoBlue, picoBlack, picoBlack, onTime1, offTime1, timeOut1);
  //repeatLed(2, picoBlue, picoBlack, picoBlack, onTime2, offTime2, timeOut2);
  //repeatLed(3, picoBlue, picoBlack, picoBlack, onTime3, offTime3, timeOut3);
  localStatus = repeatLed(4, picoBlue, picoBlack, picoBlack, onTime4, offTime4, timeOut4);
  if (localStatus == statusOff) {
    Serial.println("Mode-11:  M11 statusOff");
    mode11Enable = false;  
    startTimerClimber1 = false;
    } // End if statusOnceOff   
  } // End mode11Enable
} // End mode11()

void mode12(){
  if (mode12Enable == true){
  int localStatus = 0;
  startTimerClimber1 = true;
  repeatLed(1, picoRed, picoGreen, picoBlack, onTime1, offTime1, timeOut1);
  //repeatLed(2, picoRed, picoGreen, picoBlack, onTime2, offTime2, timeOut2);
  //repeatLed(3, picoRed, picoGreen, picoBlack, onTime3, offTime3, timeOut3);
  localStatus = repeatLed(4, picoRed, picoGreen, picoBlack, onTime4, offTime4, timeOut4);
  if (localStatus == statusOff) {
    Serial.println("Mode-12: M12 statusOff");
    mode12Enable = false;  
    startTimerClimber1 = false;
    } // End if statusOnceOff   
  } // End mode12Enable
} // End mode12()

////////////////////////////////////////////////////////////////////CORE 2 - I2C

//String buffValue;


void setup1() {
  delay(5000);//////////////////////////////////////ERASE THIS AFTER TESTING
  Wire.setSDA(8);
  Wire.setSCL(9);
  Wire.onReceive(recv);
  Wire.begin(0x30);
  Serial.begin(115200);
  Serial.println("I2C Scanning for input..");
}

bool char_in = false;
void loop1() {
  delay(1000);
  Serial.println("Waiting for input");  
  //char data = ((char)buff.get()); 

  // Print out string from controller
    
  if (char_in == true){
      
    //Serial.print("buff: "); 
      
     while (!buff.isEmpty()) {
      //Serial.print((char)buff.get());
      //Serial.printf("Buff: %c \r\n", (char)buff.get());
      //Serial.print("\r\n");
      if (bool localStatus = buff.startsWith("m ")) {
        //Serial.println("m_xx found");
        buff.drop(2);
        int localInt = buff.getNumber();
        if (localInt == 1){
          Serial.println("Mode M 1 received");
          mode1Enable = true;
          //startTimerClimber1 = true;
        }
        else if (localInt == 2){
          Serial.println("Mode M 2 received");
          mode2Enable = true;
          //startTimerClimber1 = true;
        }
        else if (localInt == 3){
          Serial.println("Mode M 3 received");
          mode3Enable = true;
          //startTimerClimber1 = true;
        }
        else if (localInt == 11){
          Serial.println("Mode M 11 received");
          mode11Enable = true;
          //startTimerClimber1 = true;
        }
        //Serial.printf("m_xx found with number %s \r\n", localInt);
        
        //Serial.println("m_xx found");
      } // end if
      
     } // end if buff not empty
     
      //Serial.print("\r\n");
    //char_in = false;
    }// end of if char_in = true

}//end of loop1()


// Called when the I2C responder gets written to
void recv(int len) {
    int i;
    for (i=0; i<len; i++) buff.put(Wire.read());

    //buff.put(/*the byte we got over I2C*/);
    char_in =  true;

} // end of recv()



//   /\     /\ 
//   \/-----\/
//    \◣  ◢/
//    ≈\ © /≈  
//      \‿/     
//     "rat"

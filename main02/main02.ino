/*
use this instead of delay(miliseconds);


bool isTimerDone = false;
void setup() {
  long int startingNum = millis();
  //  Serial.begin(9600);
  Serial.println("started timer");
  isTimerDone = true;
}

void loop() {
  if (isTimerDone && ((millis() - startingNum) >= 10000)){
    isTimerDone = true;
    //Serial.println("10 seconds ellapsed");
  }
  
}
*/

#include "FastLED.h"                                                   //LED strip lib
#include <Wire.h>                                                      //I2C lib
//#include <string.h> 
#include <C:\Users\Admin\Documents\frc\2024-robot-bling\colorPalette.h>// color palette header file

#define COLOR_ORDER GRB                                                // make the order RGB
#define NUM_LEDS 30
#define NUM_LEDS_STRIP1 30                                                    //30 LEDs on strip 1
#define NUM_LEDS_STRIP2 30                                                    //30 LEDs on strip 2
#define NUM_LEDS_STRIP3 30                                                    //30 LEDs on strip 3
#define BRIGHTNESS 75                                                  //LED brightness
#define DATA_PIN 16                                                    // Robot data ouput pin
#define LED_TYPE   WS2811                                              //i'm honestley not sure what this does

////////////////////////////////////////////////////////////////////////////

static char buff[10];                                                   // array of charicters for the buffer
bool char_in = false;                                                   //set to TRUE when receving communication from I2C
CRGB leds1[NUM_LEDS_STRIP1];                                                    // array of LEDs (length is NUM_LEDS)
CRGB leds2[NUM_LEDS_STRIP2];                                                    // array of LEDs (length is NUM_LEDS)
CRGB leds3[NUM_LEDS_STRIP3];                                                    // array of LEDs (length is NUM_LEDS)
bool runIdle = true;                                                    // is idle on?

////////////////////////////////////////////////////////////////////////////

void recv(int len) {                                                    // function to receve data via I2C
  int i;
  // Just stuff the sent bytes into a global that the main routine can pick up and use
  for (i = 0; i < len; i++) buff[i] = Wire.read();
  buff[i] = 0;
  char_in =  true;
}
//////////////////////////////////////////////////////////////////////////// 

void setPallete( uint8_t colorIndex)                                    //function to set the palette to whatever we want
{
    uint8_t brightness = 255;
    
    for( int i = 0; i < NUM_LEDS; ++i) {
        leds1[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
        colorIndex += 3;
    }
}

////////////////////////////////////////////////////////////////////////////
  int setOneColor(CRGB (stripColor), int onTime){
   for (int j = 0; j < NUM_LEDS; j++) {                                 // i is ALL of the leds
    leds1[j] = CRGB(stripColor);                                         // make all LEDs the specified color
  }                                                                     // end of for loop
  
  FastLED.show();                                                       // show LEDs
  FastLED.delay (onTime);                                               // WAIT for the specified ammount of time
  
  for (int j = 0; j < NUM_LEDS; j++) {                                  // J is all of the LEDs
   leds1[j] = CRGB(0,0,0);                                              // turn all LEDs off
  }                                                                     //end of for loop
  
  return(0);
  
  }//end of function

////////////////////////////////////////////////////////////////////////////
//what to do when not communicating with driver
int idle (){
    setPallete(0);
//    startIndex = startIndex + 5;                                      // motion speed
    FastLED.setBrightness(  BRIGHTNESS );                               // set the brightness to "brightness"
//    setPallete(startIndex);
    FastLED.show();                                                     // show LEDs
  return(0);
}
////////////////////////////////////////////////////////////////////////////
void setup() {
  idle();                                                               
  currentPalette = RainbowColors_p;       
  currentBlending = LINEARBLEND;          
  Wire.setSDA(8);
  Wire.setSCL(9);
  Wire.onReceive(recv);
  Wire.begin(0x30);
  delay(200);
  
  FastLED.addLeds< WS2811  , 16, COLOR_ORDER> (leds1, NUM_LEDS_STRIP1).setCorrection(TypicalLEDStrip);
  FastLED.addLeds< WS2811  , 18, COLOR_ORDER> (leds2, NUM_LEDS_STRIP2).setCorrection(TypicalLEDStrip);
  FastLED.addLeds< WS2811  , 20, COLOR_ORDER> (leds3, NUM_LEDS_STRIP3).setCorrection(TypicalLEDStrip);
  idle();
}

////////////////////////////////////////////////////////////////////////////
CRGB green      = CRGB(0   , 150 , 0  ); //    1
CRGB yellow     = CRGB(255 , 208 , 0  ); //    2
CRGB purple     = CRGB(196 , 0   , 255); //    3
CRGB blue       = CRGB(0   , 0   , 224); //    4
CRGB red        = CRGB(150 , 0   , 0  ); //    5
CRGB lightBlue  = CRGB(0   , 255 , 251); //    6
CRGB white      = CRGB(255 , 225 , 225); //    7
CRGB brown      = CRGB(89  , 73  , 41 ); //    8
CRGB pink       = CRGB(237 , 0   , 205); //    9

////////////////////////////////////////////////////////////////////////////


String stringInput = "";
static uint8_t startIndex = 0;


////////////////////////////////////////////////////////////////////////////
void loop() {
  
  if (runIdle == true){
  idle();
  }

  if (char_in == true){
     char_in = false;
     stringInput = buff;
     Serial.println(stringInput);

    if (stringInput == "aaa") {
     setOneColor(lightBlue, 100000);
   }//end of if statement
   
  if (stringInput == "bbb") {
      setOneColor(red, 1000);
  }//end of if statement

  if (stringInput == "ccc") {
      setOneColor(green, 1000); 
  }//end of if statement
  
  }//end of if char in = true
  Serial.printf("buff: '%s'\r\n", buff);
  Wire.requestFrom(0x30, 6);
  Serial.print("\nrecv: '");
  while (Wire.available()) {
  Serial.print((char)Wire.read());
  }




}//end of loop()

//#include "pixeltypes.h"
//#include "FastLED.h"
//#include <pico_relay.h>
#include <Wire.h>
#include <string.h>
#include <C:\Users\Admin\Documents\frc\2024-robot-bling\colorPalette.h>

#define COLOR_ORDER GRB
#define NUM_LEDS 30
#define BRIGHTNESS 75
#define DATA_PIN 16 // Robot data ouput pin
#define LED_TYPE   WS2811

static char buff[10];
bool char_in = false;

CRGB leds[NUM_LEDS];

void recv(int len) {
  int i;
  // Just stuff the sent bytes into a global that the main routine can pick up and use
  for (i = 0; i < len; i++) buff[i] = Wire.read();
  buff[i] = 0;
  char_in =  true;
}



void FillLEDsFromPaletteColors( uint8_t colorIndex)
{
    uint8_t brightness = 255;
    
    for( int i = 0; i < NUM_LEDS; ++i) {
        leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
        colorIndex += 3;
    }
}

void setup() {
  currentPalette = RainbowColors_p;
  currentBlending = LINEARBLEND;
  Wire.setSDA(8);
  Wire.setSCL(9);
  Wire.onReceive(recv);
  Wire.begin(0x30);
  delay(200);
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER> (leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

}




//CRGB purple     = CHSV( HUE_PURPLE, 255, 255);
//CRGB color[9] = {
// CRGB(0,150,0)        // green      0
//,CRGB(255,208,0)      // yellow     1
//,CRGB(196,0,255)      // purple     2
//,CRGB(28,0,224)       // blue       3
//,CRGB(0,255,251)      // lightBlue  4
//,CRGB(255 ,225 ,225); // white      5
//,CRGB(59  ,43  ,11 ); // brown      6
//,CRGB(227 ,0   ,255);//9
//};


CRGB green      = CRGB(0   , 150 , 0  ); //    1
CRGB yellow     = CRGB(255 , 208 , 0  ); //    2
CRGB purple     = CRGB(196 , 0   , 255); //    3
CRGB blue       = CRGB(0   , 0   , 224); //    4
CRGB red        = CRGB(150 , 0   , 0  ); //    5
CRGB lightBlue  = CRGB(0   , 255 , 251); //    6
CRGB white      = CRGB(255 , 225 , 225); //    7
CRGB brown      = CRGB(89  , 73  , 41 ); //    8
CRGB pink       = CRGB(237 , 0   , 205); //    9



String stringInput = "";
int color = 6;
static uint8_t startIndex = 0;

void loop() {
  
    startIndex = startIndex + 1; /* motion speed */
    FastLED.setBrightness(  BRIGHTNESS );
    FillLEDsFromPaletteColors( startIndex);
    
    FastLED.show();
    FastLED.delay(1000 / UPDATES_PER_SECOND);


  if (char_in == true){
     char_in = false;
     stringInput = buff;
     Serial.println(stringInput);
  }
    if (stringInput == "aaa") {
    color = 10;
  }
  
  if (stringInput == "bbb") {
    color = 1;
  }  
  if (stringInput == "ccc") {
    color = 4;
  }
  
  Serial.printf("buff: '%s'\r\n", buff);
  Wire.requestFrom(0x30, 6);
  Serial.print("\nrecv: '");
  while (Wire.available()) {
  Serial.print((char)Wire.read());
  }
  for (int i = 0; i < NUM_LEDS; i++) {
    if (color == 1) {
      leds[i] = CRGB(green);
    }//end of if

    if (color == 2) {
      leds[i] = CRGB(yellow);
    }//end of if

    if (color == 3) {
      leds[i] = CRGB(purple);
    }//end of if

    if (color == 4) {
      leds[i] = CRGB(blue);

    }//end of if

    if (color == 5) {
      leds[i] = CRGB(green);
    }//end of if

    if (color == 6) {
      leds[i] = CRGB(lightBlue);
    }//end of if

    if (color == 7) {
      leds[i] = CRGB(white);

    }//end of if

    if (color == 8) {
      leds[i] = CRGB(brown);
    }//end of if

    if (color == 9) {
      leds[i] = CRGB(pink);
    }//end of if

    if (color == 10) {
      leds[i] = CRGB(red);
    }//end of if

  //}end of for loop
  

//
  
  FastLED.show();
  //    delay(1000);

}//end of loop()

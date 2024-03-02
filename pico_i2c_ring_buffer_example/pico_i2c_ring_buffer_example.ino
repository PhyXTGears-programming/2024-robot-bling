#include <Wire.h>

#include "RingBuffer.h"
#include <string>

String buffValue;

CassiusRingBuffer buff;

void setup() {
  Wire.setSDA(8);
  Wire.setSCL(9);
  Wire.onReceive(recv);
  Wire.begin(0x30);
  Serial.begin(115200);
  delay(5000);
  Serial.println("I2C Scanning for input");
}

//static char buff[100];
bool char_in = false;

void loop() {

    // Print out string from controller
    delay(1000);
    Serial.println("Waiting for input");  
    if (char_in == true){
      
      Serial.print("buff: "); 
      
     while (!buff.isEmpty()) {
      Serial.print((char)buff.get()); 
     }
     
      Serial.print("\r\n");
/**
      int n = sizeof(buff);
      char chars[n+1];
      memcpy(chars, buff.get(), n);
      chars[n] = '\0';
      Serial.println("chars: ",chars);
**/
/**
      int n = sizeof(buff);
      std::string localString(buff.get(), n);
      Serial.printf("localString: '%s'\r\n",localString);
      //Serial.println (buff.get());
      char_in =  false;
**/
    }
    


}//end of loop()
// Called when the I2C responder gets written to
void recv(int len) {
    int i;
    for (i=0; i<len; i++) buff.put(Wire.read());

    //buff.put(/*the byte we got over I2C*/);
    char_in =  true;
}



//   /\     /\ 
//   \/-----\/
//    \ʘ   ʘ/
//    ≈\ © /≈
//      \‿/
//  "mouse" - 2/24/2024

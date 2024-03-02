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
        }
        else if (localInt == 2){
          Serial.println("Mode M 2 received");
        }
        else if (localInt == 3){
          Serial.println("Mode M 3 received");
        }
        else if (localInt == 11){
          Serial.println("Mode M 11 received");
        }
        //Serial.printf("m_xx found with number %s \r\n", localInt);
        
        //Serial.println("m_xx found");
      } // end if
      
     }
     
      //Serial.print("\r\n");
    char_in = false;
    }// end of if char_in = true
    


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

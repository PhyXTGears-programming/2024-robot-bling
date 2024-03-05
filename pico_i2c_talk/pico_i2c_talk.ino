
#include <Wire.h>

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Wire.setSDA(8);
  Wire.setSCL(9);
  Wire.begin();
  Serial.begin(115200);
  delay(5000);
  Serial.println("RoboRio");
}


void loop() {
    
    // Write a value over I2C from RoboRio to the responder
    char b[90];
    Wire.beginTransmission(0x30);
    Serial.println("Starting");
    Serial.println("Sending m 1");
    Wire.write("m 1");
    Wire.endTransmission();
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);  
    digitalWrite(LED_BUILTIN, LOW);
    delay(3500); 
    ////////////////////////////////////////////////////////////////////////////////
    Wire.beginTransmission(0x30);
    Serial.println("Sending m 2");
    Wire.write("m 2");
    Wire.endTransmission();
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);  
    digitalWrite(LED_BUILTIN, LOW);
    delay(3500); 
    ////////////////////////////////////////////////////////////////////////////////    
    Wire.beginTransmission(0x30);
    Serial.println("Sending m 3");
    Wire.write("m 3");
    Wire.endTransmission();
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);  
    digitalWrite(LED_BUILTIN, LOW);
    delay(3500); 
    ////////////////////////////////////////////////////////////////////////////////
    Wire.beginTransmission(0x30);
    Serial.println("Sending m 11");
    Wire.write("m 11");
    Wire.endTransmission();
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);  
    digitalWrite(LED_BUILTIN, LOW);
    delay(5500); 
    ////////////////////////////////////////////////////////////////////////////////
    Serial.println("Sending p 31");
    Wire.beginTransmission(0x30);
    Wire.write("p 31");
    Wire.endTransmission();
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);  
    digitalWrite(LED_BUILTIN, LOW);
    delay(500); 
    Serial.println("Sending m 1");
    Wire.beginTransmission(0x30);
    Wire.write("m 1");
    Wire.endTransmission();
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);  
    digitalWrite(LED_BUILTIN, LOW);
    delay(2500);
    ////////////////////////////////////////////////////////////////////////////////
    Serial.println("Sending p 32");
    Wire.beginTransmission(0x30);
    Wire.write("p 32");
    Wire.endTransmission();
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);  
    digitalWrite(LED_BUILTIN, LOW);
    delay(500); 
    Serial.println("Sending m 1");
    Wire.beginTransmission(0x30);
    Wire.write("m 1");
    Wire.endTransmission();
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);  
    digitalWrite(LED_BUILTIN, LOW);
    delay(2500);
    ////////////////////////////////////////////////////////////////////////////////        
    Serial.println("Sending p 33");
    Wire.beginTransmission(0x30);
    Wire.write("p 33");
    Wire.endTransmission();
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);  
    digitalWrite(LED_BUILTIN, LOW);
    delay(500); 
    Serial.println("Sending m 1");
    Wire.beginTransmission(0x30);
    Wire.write("m 1");
    Wire.endTransmission();
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);  
    digitalWrite(LED_BUILTIN, LOW);
    delay(2500); 
    Serial.println("Sending p 32");
    Wire.beginTransmission(0x30);
    Wire.write("p 32");
    Wire.endTransmission();
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);  
    digitalWrite(LED_BUILTIN, LOW);
    delay(500); 
    ////////////////////////////////////////////////////////////////////////////////
    Serial.println("Sending p 21");
    Wire.beginTransmission(0x30);
    Wire.write("p 21");
    Wire.endTransmission();
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);  
    digitalWrite(LED_BUILTIN, LOW);
    delay(500); 
    Serial.println("Sending m 11");
    Wire.beginTransmission(0x30);
    Wire.write("m 11");
    Wire.endTransmission();
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);  
    digitalWrite(LED_BUILTIN, LOW);
    delay(5500);
    ////////////////////////////////////////////////////////////////////////////////
    Serial.println("Sending p 22");
    Wire.beginTransmission(0x30);
    Wire.write("p 22");
    Wire.endTransmission();
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);  
    digitalWrite(LED_BUILTIN, LOW);
    delay(500); 
    Serial.println("Sending m 11");
    Wire.beginTransmission(0x30);
    Wire.write("m 11");
    Wire.endTransmission();
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);  
    digitalWrite(LED_BUILTIN, LOW);
    delay(5500);
    ////////////////////////////////////////////////////////////////////////////////        
    Serial.println("Sending p 23");
    Wire.beginTransmission(0x30);
    Wire.write("p 23");
    Wire.endTransmission();
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);  
    digitalWrite(LED_BUILTIN, LOW);
    delay(500); 
    Serial.println("Sending m 11");
    Wire.beginTransmission(0x30);
    Wire.write("m 11");
    Wire.endTransmission();
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);  
    digitalWrite(LED_BUILTIN, LOW);
    delay(2500); 
    Serial.println("Sending p 22");
    Wire.beginTransmission(0x30);
    Wire.write("p 22");
    Wire.endTransmission();
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);  
    digitalWrite(LED_BUILTIN, LOW);
    delay(500); 
    ////////////////////////////////////////////////////////////////////////////////
    Serial.println("Sending p 11");
    Wire.beginTransmission(0x30);
    Wire.write("p 11");
    Wire.endTransmission();
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);  
    digitalWrite(LED_BUILTIN, LOW);
    delay(500); 
    Serial.println("Sending m 5");
    Wire.beginTransmission(0x30);
    Wire.write("m 5");
    Wire.endTransmission();
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);  
    digitalWrite(LED_BUILTIN, LOW);
    delay(2500);
    ////////////////////////////////////////////////////////////////////////////////
    Serial.println("Sending p 12");
    Wire.beginTransmission(0x30);
    Wire.write("p 12");
    Wire.endTransmission();
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);  
    digitalWrite(LED_BUILTIN, LOW);
    delay(500); 
    Serial.println("Sending m 5");
    Wire.beginTransmission(0x30);
    Wire.write("m 5");
    Wire.endTransmission();
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);  
    digitalWrite(LED_BUILTIN, LOW);
    delay(2500);
    ////////////////////////////////////////////////////////////////////////////////        
    Serial.println("Sending p 13");
    Wire.beginTransmission(0x30);
    Wire.write("p 13");
    Wire.endTransmission();
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);  
    digitalWrite(LED_BUILTIN, LOW);
    delay(500); 
    Serial.println("Sending m 5");
    Wire.beginTransmission(0x30);
    Wire.write("m 5");
    Wire.endTransmission();
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);  
    digitalWrite(LED_BUILTIN, LOW);
    delay(2500); 
    Serial.println("Sending p 12");
    Wire.beginTransmission(0x30);
    Wire.write("p 12");
    Wire.endTransmission();
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);  
    digitalWrite(LED_BUILTIN, LOW);
    delay(500); 
   
    ////////////////////////////////////////////////////////////////////////////////

}

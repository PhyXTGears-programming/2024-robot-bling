
#include <Wire.h>

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Wire.setSDA(8);
  Wire.setSCL(9);
  Wire.begin();
  Serial.begin(115200);
  delay(3000);
  Serial.println("RoboRio");
}


void loop() {
    
    // Write a value over I2C from RoboRio to the responder
    char b[90];
    Wire.beginTransmission(0x30);
    Serial.println("Sending m 1");
    Wire.write("m 1");
    Wire.endTransmission();
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);                       // wait for a second
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    delay(5500); 
    Wire.beginTransmission(0x30);
    Serial.println("Sending m 2");
    Wire.write("m 2");
    Wire.endTransmission();
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);                       // wait for a second
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    delay(7500); 
    Wire.beginTransmission(0x30);
    Serial.println("Sending m 3");
    Wire.write("m 3");
    Wire.endTransmission();
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);                       // wait for a second
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    delay(7500); 
    Wire.beginTransmission(0x30);
    Serial.println("Sending m 11");
    Wire.write("m 11");
    Wire.endTransmission();
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);                       // wait for a second
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    delay(7500); 


}

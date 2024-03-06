
#include <Wire.h>

// RoboRio Test Script

#define shortTimeout 2000
#define midTimeout 3500
#define longTimeout 5000
 
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Wire.setSDA(8);
  Wire.setSCL(9);
  Wire.begin();
  Wire.setClock(100000);
  Serial.begin(115200);
  delay(5000);
  Serial.println(" Starting RoboRio");
}


void loop() {
    
    // Write a value over I2C from RoboRio to the responder
    char b[90];
    Wire.beginTransmission(0x30);
    Serial.println("Starting");
    Serial.println("Sending m 1"); // Red
    Wire.write("m 1");
    Wire.endTransmission();
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);  
    digitalWrite(LED_BUILTIN, LOW);
    delay(midTimeout); 
    ////////////////////////////////////////////////////////////////////////////////
    Wire.beginTransmission(0x30);
    Serial.println("Sending m 2"); //Yellow
    Wire.write("m 2");
    Wire.endTransmission();
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);  
    digitalWrite(LED_BUILTIN, LOW);
    delay(midTimeout); 
    ////////////////////////////////////////////////////////////////////////////////    
    Wire.beginTransmission(0x30);
    Serial.println("Sending m 3"); // Green
    Wire.write("m 3");
    Wire.endTransmission();
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);  
    digitalWrite(LED_BUILTIN, LOW);
    delay(midTimeout); 
    ////////////////////////////////////////////////////////////////////////////////
    Wire.beginTransmission(0x30);
    Serial.println("Sending m 11"); // Flashing blue
    Wire.write("m 11");
    Wire.endTransmission();
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);  
    digitalWrite(LED_BUILTIN, LOW);
    delay(longTimeout); 
    ////////////////////////////////////////////////////////////////////////////////
    Serial.println("Sending p 31"); // Short time-out
    Wire.beginTransmission(0x30);
    Wire.write("p 31");
    Wire.endTransmission();
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);  
    digitalWrite(LED_BUILTIN, LOW);
    delay(500); 
    Serial.println("Sending m 1"); // Red
    Wire.beginTransmission(0x30);
    Wire.write("m 1");
    Wire.endTransmission();
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);  
    digitalWrite(LED_BUILTIN, LOW);
    delay(midTimeout);
    ////////////////////////////////////////////////////////////////////////////////
    Serial.println("Sending p 32"); // Mid time-out
    Wire.beginTransmission(0x30);
    Wire.write("p 32");
    Wire.endTransmission();
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);  
    digitalWrite(LED_BUILTIN, LOW);
    delay(midTimeout); 
    Serial.println("Sending m 1"); // Red
    Wire.beginTransmission(0x30);
    Wire.write("m 1");
    Wire.endTransmission();
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);  
    digitalWrite(LED_BUILTIN, LOW);
    delay(midTimeout);
    ////////////////////////////////////////////////////////////////////////////////        
    Serial.println("Sending p 33"); // Long time-out
    Wire.beginTransmission(0x30);
    Wire.write("p 33");
    Wire.endTransmission();
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);  
    digitalWrite(LED_BUILTIN, LOW);
    delay(midTimeout); 
    Serial.println("Sending m 1"); // Red
    Wire.beginTransmission(0x30);
    Wire.write("m 1");
    Wire.endTransmission();
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);  
    digitalWrite(LED_BUILTIN, LOW);
    delay(midTimeout); 
    Serial.println("Sending p 32"); // Mid time-out (Default)
    Wire.beginTransmission(0x30);
    Wire.write("p 32");
    Wire.endTransmission();
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);  
    digitalWrite(LED_BUILTIN, LOW);
    delay(midTimeout); 
    ////////////////////////////////////////////////////////////////////////////////
    Serial.println("Sending p 21"); // Slow flash-rate
    Wire.beginTransmission(0x30);
    Wire.write("p 21");
    Wire.endTransmission();
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);  
    digitalWrite(LED_BUILTIN, LOW);
    delay(midTimeout); 
    Serial.println("Sending m 11"); // Flashing blue
    Wire.beginTransmission(0x30);
    Wire.write("m 11");
    Wire.endTransmission();
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);  
    digitalWrite(LED_BUILTIN, LOW);
    delay(longTimeout);
    ////////////////////////////////////////////////////////////////////////////////
    Serial.println("Sending p 22"); // Mid flash-rate
    Wire.beginTransmission(0x30);
    Wire.write("p 22");
    Wire.endTransmission();
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);  
    digitalWrite(LED_BUILTIN, LOW);
    delay(midTimeout); 
    Serial.println("Sending m 11"); // Flashing blue
    Wire.beginTransmission(0x30);
    Wire.write("m 11");
    Wire.endTransmission();
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);  
    digitalWrite(LED_BUILTIN, LOW);
    delay(longTimeout);
    ////////////////////////////////////////////////////////////////////////////////        
    Serial.println("Sending p 23"); // Long flash-rate
    Wire.beginTransmission(0x30);
    Wire.write("p 23");
    Wire.endTransmission();
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);  
    digitalWrite(LED_BUILTIN, LOW);
    delay(midTimeout); 
    Serial.println("Sending m 11"); // Flashing blue
    Wire.beginTransmission(0x30);
    Wire.write("m 11");
    Wire.endTransmission();
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);  
    digitalWrite(LED_BUILTIN, LOW);
    delay(longTimeout); 
    Serial.println("Sending p 22"); // Mid flash-rate (Default)
    Wire.beginTransmission(0x30);
    Wire.write("p 22");
    Wire.endTransmission();
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);  
    digitalWrite(LED_BUILTIN, LOW);
    delay(midTimeout); 
    ////////////////////////////////////////////////////////////////////////////////
    Serial.println("Sending p 11"); // Low brightness
    Wire.beginTransmission(0x30);
    Wire.write("p 11");
    Wire.endTransmission();
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);  
    digitalWrite(LED_BUILTIN, LOW);
    delay(midTimeout); 
    Serial.println("Sending m 5"); // Orange
    Wire.beginTransmission(0x30);
    Wire.write("m 5");
    Wire.endTransmission();
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);  
    digitalWrite(LED_BUILTIN, LOW);
    delay(midTimeout);
    ////////////////////////////////////////////////////////////////////////////////
    Serial.println("Sending p 12"); // Mid brightness
    Wire.beginTransmission(0x30);
    Wire.write("p 12");
    Wire.endTransmission();
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);  
    digitalWrite(LED_BUILTIN, LOW);
    delay(midTimeout); 
    Serial.println("Sending m 5"); // Orange
    Wire.beginTransmission(0x30);
    Wire.write("m 5");
    Wire.endTransmission();
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);  
    digitalWrite(LED_BUILTIN, LOW);
    delay(midTimeout);
    ////////////////////////////////////////////////////////////////////////////////        
    Serial.println("Sending p 13"); // High brightness
    Wire.beginTransmission(0x30);
    Wire.write("p 13");
    Wire.endTransmission();
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);  
    digitalWrite(LED_BUILTIN, LOW);
    delay(midTimeout); 
    Serial.println("Sending m 5"); // Orange
    Wire.beginTransmission(0x30);
    Wire.write("m 5");
    Wire.endTransmission();
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);  
    digitalWrite(LED_BUILTIN, LOW);
    delay(midTimeout); 
    Serial.println("Sending p 12"); // Mid brightness (Default)
    Wire.beginTransmission(0x30);
    Wire.write("p 12");
    Wire.endTransmission();
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);  
    digitalWrite(LED_BUILTIN, LOW);
    delay(midTimeout); 
   
    ////////////////////////////////////////////////////////////////////////////////

}

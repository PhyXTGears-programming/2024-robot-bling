

#include <Wire.h>

// RoboRio Test Script

#define veryShortTimeout 200
#define shortTimeout 1000
#define midTimeout 2500
#define longTimeout 10000
 
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Wire.setSDA(8);
  Wire.setSCL(9);
  Wire.begin();
  Wire.setClock(100000);
  Serial.begin(115200);
  delay(5000);
  Serial.println("Starting RoboRio Test Script");
}

void blinkLed(int localTimeOut){
    digitalWrite(LED_BUILTIN, HIGH);
    delay(localTimeOut);  
    digitalWrite(LED_BUILTIN, LOW);
    delay(localTimeOut);
}
void loop() {
    
    // Write a value over I2C from RoboRio to the responder
    char b[90];
    
    Serial.println("Sending p 0: Start *************"); // Start
    Wire.beginTransmission(0x30);
    Wire.write("p 0");
    Wire.endTransmission();
    blinkLed(veryShortTimeout); 

    Serial.println("Sending p 31: Use short time-out"); // Short time-out
    Wire.beginTransmission(0x30);
    Wire.write("p 31");
    Wire.endTransmission();
    Serial.println("Sending p 1: Use Climber"); // Climber Led Strip
    Wire.beginTransmission(0x30);
    Wire.write("p 1");
    Wire.endTransmission();
    blinkLed(veryShortTimeout); 

    Serial.println("Sending m 1: Red"); // Red
    Wire.beginTransmission(0x30);
    Wire.write("m 1");
    Wire.endTransmission();
    blinkLed(midTimeout); 
    
    ////////////////////////////////////////////////////////////////////////////////
    Serial.println("Sending p 32: Use mid time-out"); // Mid time-out
    Wire.beginTransmission(0x30);
    Wire.write("p 32");
    Wire.endTransmission();
    Serial.println("Sending p 2: Use Trap"); // Trap Led Strip
    Wire.beginTransmission(0x30);
    Wire.write("p 2");
    Wire.endTransmission();
    blinkLed(veryShortTimeout); 
    
    Serial.println("Sending m 2: Yellow"); // Yellow
    Wire.beginTransmission(0x30);
    Wire.write("m 2");
    Wire.endTransmission();
    blinkLed(midTimeout); 
    
    ////////////////////////////////////////////////////////////////////////////////        
    Serial.println("Sending p 33: Use long time-out"); // Long time-out
    Wire.beginTransmission(0x30);
    Wire.write("p 33");
    Wire.endTransmission();
    Serial.println("Sending p 3: Use Speaker"); // Speaker Led Strip
    Wire.beginTransmission(0x30);
    Wire.write("p 3");
    Wire.endTransmission();
    blinkLed(veryShortTimeout);  

    Serial.println("Sending m 3: Green"); // Green
    Wire.beginTransmission(0x30);
    Wire.write("m 3");
    Wire.endTransmission();
    blinkLed(midTimeout); 
    
    Serial.println("Sending p 32: Use mid time-out (default)"); // Back to default: Mid time-out
    Wire.beginTransmission(0x30);
    Wire.write("p 32");
    Wire.endTransmission();

    ////////////////////////////////////////////////////////////////////////////////

    Serial.println("Sending p 21: Use slow flash-rate"); // Slow flash-rate
    Wire.beginTransmission(0x30);
    Wire.write("p 21");
    Wire.endTransmission();
    Serial.println("Sending p 1: Use Climber"); // Climber Led Strip
    Wire.beginTransmission(0x30);
    Wire.write("p 1");
    Wire.endTransmission();
    blinkLed(veryShortTimeout);

    Serial.println("Sending m 11: Flashing Blue"); // Flashing blue
    Wire.beginTransmission(0x30);
    Wire.write("m 11");
    Wire.endTransmission();
    blinkLed(midTimeout);

    ////////////////////////////////////////////////////////////////////////////////
    Serial.println("Sending p 22: Use mid flash rate"); // Mid flash-rate
    Wire.beginTransmission(0x30);
    Wire.write("p 22");
    Wire.endTransmission();
    Serial.println("Sending p 2: Use Trap"); // Trap Led Strip
    Wire.beginTransmission(0x30);
    Wire.write("p 2");
    Wire.endTransmission();
    blinkLed(veryShortTimeout); 

    Serial.println("Sending m 11: Flashing Blue"); // Flashing blue
    Wire.beginTransmission(0x30);
    Wire.write("m 11");
    Wire.endTransmission();
    blinkLed(midTimeout);

    ////////////////////////////////////////////////////////////////////////////////        
    Serial.println("Sending p 23: Use high flash-rate"); // High flash-rate
    Wire.beginTransmission(0x30);
    Wire.write("p 23");
    Wire.endTransmission();
    Serial.println("Sending p 3: Use Speaker"); // Speaker Led Strip
    Wire.beginTransmission(0x30);
    Wire.write("p 3");
    Wire.endTransmission();
    blinkLed(veryShortTimeout); 

    Serial.println("Sending m 11: Flashing Blue"); // Flashing blue
    Wire.beginTransmission(0x30);
    Wire.write("m 11");
    Wire.endTransmission();
    blinkLed(midTimeout);
 
    Serial.println("Sending p 22: Use mid flash-rate (default)"); // Back to default: Mid flash-rate
    Wire.beginTransmission(0x30);
    Wire.write("p 22");
    Wire.endTransmission();
     
    ////////////////////////////////////////////////////////////////////////////////
    Serial.println("Sending p 11: Use low brightness"); // Low brightness
    Wire.beginTransmission(0x30);
    Wire.write("p 11");
    Wire.endTransmission();
    Serial.println("Sending p 1: Use Climber"); // Climber Led Strip
    Wire.beginTransmission(0x30);
    Wire.write("p 1");
    Wire.endTransmission();
    blinkLed(veryShortTimeout); 

    Serial.println("Sending m 5: Orange"); // Orange
    Wire.beginTransmission(0x30);
    Wire.write("m 5");
    Wire.endTransmission();
    blinkLed(midTimeout); 
    
    ////////////////////////////////////////////////////////////////////////////////
    Serial.println("Sending p 12: Use mid brightness"); // Mid brightness
    Wire.beginTransmission(0x30);
    Wire.write("p 12");
    Wire.endTransmission();
    Serial.println("Sending p 2: Use Trap"); // Trap Led Strip
    Wire.beginTransmission(0x30);
    Wire.write("p 2");
    Wire.endTransmission();
    blinkLed(veryShortTimeout); 

    Serial.println("Sending m 2: Yellow"); // Yellow
    Wire.beginTransmission(0x30);
    Wire.write("m 2");
    Wire.endTransmission();
    blinkLed(midTimeout); 
    
    ////////////////////////////////////////////////////////////////////////////////        
    Serial.println("Sending p 13: Use high brightness"); // High brightness
    Wire.beginTransmission(0x30);
    Wire.write("p 13");
    Wire.endTransmission();
    Serial.println("Sending p 3: Use Speaker"); // Speaker Led Strip
    Wire.beginTransmission(0x30);
    Wire.write("p 3");
    Wire.endTransmission();
    blinkLed(veryShortTimeout); 
    
    Serial.println("Sending m 6: Purple"); // Purple              
    Wire.beginTransmission(0x30);
    Wire.write("m 6");
    Wire.endTransmission();
    blinkLed(midTimeout); 
    
    Serial.println("Sending p 12: Use mid brightness (default)"); // Back to default: Mid brightness
    Wire.beginTransmission(0x30);
    Wire.write("p 12");
 
    ////////////////////////////////////////////////////////////////////////////////
}

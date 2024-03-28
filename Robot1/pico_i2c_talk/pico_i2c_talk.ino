

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
} // End setup

void p_0(){
    Serial.println("Sending p 0: Start***************"); // Start
    Wire.beginTransmission(0x30);
    Wire.write("p 0");
    Wire.endTransmission();
}

void p_1(){
    Serial.println("Sending p 1: Use Climber1"); // Climber1 Led Strip
    Wire.beginTransmission(0x30);
    Wire.write("p 1");
    Wire.endTransmission();
}

void p_2(){
    Serial.println("Sending p 2: Use Climber2"); // Climber2 Led Strip
    Wire.beginTransmission(0x30);
    Wire.write("p 2");
    Wire.endTransmission();
}

void p_3(){
    Serial.println("Sending p 3: Use Amp/Trap"); // Amp/Trap
    Wire.beginTransmission(0x30);
    Wire.write("p 3");
    Wire.endTransmission();
}

void p_4(){
    Serial.println("Sending p 4: Use Speaker"); // Speaker Led Strip
    Wire.beginTransmission(0x30);
    Wire.write("p 4");
    Wire.endTransmission();
}

void p_11(){
    Serial.println("Sending p 11: Use Low Brightness"); // Low Brightness
    Wire.beginTransmission(0x30);
    Wire.write("p 11");
    Wire.endTransmission();
}

void p_12(){
    Serial.println("Sending p 12: Use Mid Brightness"); // Mid Brightness
    Wire.beginTransmission(0x30);
    Wire.write("p 12");
    Wire.endTransmission();
}

void p_13(){
    Serial.println("Sending p 13: Use High Brightness"); // High Brightness
    Wire.beginTransmission(0x30);
    Wire.write("p 13");
    Wire.endTransmission();
}

void p_21(){
    Serial.println("Sending p 21: Use Slow Flash-rate"); // Slow Flash-rate
    Wire.beginTransmission(0x30);
    Wire.write("p 21");
    Wire.endTransmission();
}

void p_22(){
    Serial.println("Sending p 22: Use Mid Flash-rate"); // Mid Flash-rate
    Wire.beginTransmission(0x30);
    Wire.write("p 22");
    Wire.endTransmission();
}

void p_23(){
    Serial.println("Sending p 23: Use Fast Flash-rate"); // Fast Flash-rate
    Wire.beginTransmission(0x30);
    Wire.write("p 23");
    Wire.endTransmission();
}

void p_31(){
    Serial.println("Sending p 31: Use Short Timeout"); // Short Timeout 
    Wire.beginTransmission(0x30);
    Wire.write("p 31");
    Wire.endTransmission();
}

void p_32(){
    Serial.println("Sending p 32: Use Mid Timeout"); // Mid Timeout 
    Wire.beginTransmission(0x30);
    Wire.write("p 32");
    Wire.endTransmission();
}

void p_33(){
    Serial.println("Sending p 33: Use Long Timeout"); // Long Timeout 
    Wire.beginTransmission(0x30);
    Wire.write("p 33");
    Wire.endTransmission();
}

void m_1(){
    Serial.println("Sending m 1: Red"); // Red
    Wire.beginTransmission(0x30);
    Wire.write("m 1");
    Wire.endTransmission();
}

void m_2(){
    Serial.println("Sending m 2: Yellow"); // Yellow
    Wire.beginTransmission(0x30);
    Wire.write("m 2");
    Wire.endTransmission();
}

void m_3(){
    Serial.println("Sending m 3: Green"); // Green
    Wire.beginTransmission(0x30);
    Wire.write("m 3");
    Wire.endTransmission();
}

void m_5(){
    Serial.println("Sending m 5: Orange"); // Orange
    Wire.beginTransmission(0x30);
    Wire.write("m 5");
    Wire.endTransmission();
}

void m_6(){
    Serial.println("Sending m 6: Purple"); // Purple
    Wire.beginTransmission(0x30);
    Wire.write("m 6");
    Wire.endTransmission();
}

void m_11(){
    Serial.println("Sending m 11: Flashing Blue"); // Flashing Blue
    Wire.beginTransmission(0x30);
    Wire.write("m 11");
    Wire.endTransmission();
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
    
    p_0(); // Start
    blinkLed(veryShortTimeout); 
    ///////////////////////////////////////////////////////////
    p_31(); // Short time-out
    p_1(); // Climber 1
    blinkLed(veryShortTimeout); 
    m_1();// Red
    blinkLed(midTimeout); 
    ///////////////////////////////////////////////////////////
    p_32(); // Mid time-out
    p_2(); // Climber 2
    blinkLed(veryShortTimeout); 
    m_2(); // Yellow
    blinkLed(midTimeout); 
    ///////////////////////////////////////////////////////////        
    p_33(); // Long time-out
    p_3(); // Amp/Trap
    blinkLed(veryShortTimeout); 
    m_3(); // Green
    blinkLed(midTimeout); 
    p_32(); // Back to default: Mid time-out
    ///////////////////////////////////////////////////////////
    p_21(); // Slow flash-rate
    p_4(); // Speaker
    blinkLed(veryShortTimeout);
    m_11(); // Flashing blue
    blinkLed(longTimeout);
    ///////////////////////////////////////////////////////////
    p_22(); // Mid flash-rate
    p_1(); //Climber 1
    blinkLed(veryShortTimeout); 
    m_11(); // Flashing blue
    blinkLed(longTimeout);
    ///////////////////////////////////////////////////////////        
    p_23(); // High flash-rate
    p_2(); // Climber 2
    blinkLed(veryShortTimeout); 
    m_11(); // Flashing blue
    blinkLed(longTimeout);
    p_22(); // Back to default: Mid flash-rate
    ///////////////////////////////////////////////////////////
    p_11(); // Low brightness
    p_3(); // Amp/Trap
    blinkLed(veryShortTimeout); 
    m_5(); // Orange   
    blinkLed(midTimeout); 
    ///////////////////////////////////////////////////////////
    p_12(); // Mid brightness
    p_4(); // Speaker
    blinkLed(veryShortTimeout); 
    m_2(); // Yellow
    blinkLed(midTimeout); 
    ///////////////////////////////////////////////////////////        
    p_13(); // High brightness
    p_1(); // Climber 1
    blinkLed(veryShortTimeout); 
    m_6(); // Purple
    blinkLed(midTimeout); 
    p_12(); // Back to default: Mid brightness
    ///////////////////////////////////////////////////////////
}

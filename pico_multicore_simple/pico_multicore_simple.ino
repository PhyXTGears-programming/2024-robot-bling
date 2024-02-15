
//#include <stdio.h>
#include <iostream>

// Recording the timestamp at the start of the code
const int pin2 = 2;
bool pin2Status = false;
int n;
int delay_time = 1000;
// Rnning on core0
void setup() {
  pinMode(pin2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), intFunc, CHANGE);
  Serial.begin(115200);
  delay(500);
}

void loop() {
  Serial.printf("%s, \n","C0: Waiting in loop()"); 
  delay(1000);
}

void intFunc() {
  reportInt();
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(100);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(100); 
}

void reportInt(){
  Serial.printf("%s, \n","C0: Interrupt triggered:");
}

// Running on core1
void setup1() {
  pinMode(pin2, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  }

void loop1() {
  //Serial.println("C1");
  if (pin2Status == true) {
    digitalWrite(pin2, LOW);
    Serial.println("C1: setting outPin low\n");
    pin2Status = false;
  } else {
    digitalWrite(pin2, HIGH);
    pin2Status = true;
    Serial.println("C1: setting outPin high\n");
  }
  delay(5050);
  
}

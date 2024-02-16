
#include <Wire.h>

const int interruptPin  = 2;
bool interruptPinStatus = false;
String robotCmd = "";
int n;
bool char_in = false;

// Rnning on core0
void setup() {
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), interruptFunc, CHANGE);
  Serial.begin(115200);
  delay(500);
}

void loop() {
  Serial.printf("%s, \n","C0: Waiting in loop()"); 
  if (char_in == true){
    Serial.printf("buff: '%s'\r\n", robotCmd); 
    char_in =  false;
  }
  delay(1000);
}

void interruptFunc() {
  reportInt();
  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on
  delay(100);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED off
  delay(100); 
  
}

void reportInt(){
  Serial.printf("%s, %s \n","C0: Interrupt triggered, command is:",robotCmd);
}

// Running on core1
void setup1() {
  pinMode(interruptPin, OUTPUT);
  Wire1.setSDA(8);
  Wire1.setSCL(9);
  Wire1.begin(0x30);
  Wire1.onReceive(recv);
  }

void loop1() { 
}

// Called when the I2C responder receives data
void recv(int len) {
    int i;
    char buff[10];
    // Just stuff the sent bytes into a global the main routine can pick up and use
    for (i=0; i<len; i++) buff[i] = Wire1.read();
    buff[i] = 0;
    robotCmd = buff;
    if (interruptPinStatus == true) {
      digitalWrite(interruptPin, LOW);
      Serial.println("C1: setting outPin low\n");
      interruptPinStatus = false;
    } else {
      digitalWrite(interruptPin, HIGH);
      interruptPinStatus = true;
      Serial.println("C1: setting outPin high\n");
    }
}

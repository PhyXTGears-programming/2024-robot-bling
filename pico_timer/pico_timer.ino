
class Flasher
{
  // Class Member Variables
  // These are initialized in Setup()
  long OnTime;     // milliseconds of on-time
  long OffTime;    // milliseconds of off-time

  // These maintain the current state
  bool timerStatus;               // State used to enable timer
  unsigned long previousMillis;   // will store last time change was made
  
  // Constructor - creates a Flasher and initializes the member variables and state
  public:
  Flasher(bool startStatus) {
    timerStatus = startStatus;
  }

  void Setup(bool newStatus, int newOnTime, int newOffTime){
    OnTime = newOnTime;
    OffTime = newOffTime;
    timerStatus = newStatus;
  }
  
  void Update()
  {
    // check to see if it's time to change the state of the LED
    unsigned long currentMillis = millis();
     
    if((timerStatus == true) && (currentMillis - previousMillis >= OnTime))
    {
      // Turn it off
      previousMillis = currentMillis;  // Remember the time
      digitalWrite(LED_BUILTIN, LOW);  // Update the actual LED
    }
    else if ((timerStatus == true) && (currentMillis - previousMillis >= OffTime))
    {
      // turn it on
      previousMillis = currentMillis;   // Remember the time
      digitalWrite(LED_BUILTIN, HIGH);   // Update the actual LED
    }
  }
};


Flasher led1(false);

void setup()
{
led1.Setup(true,100,200);
}

void loop()
{
  led1.Update();
}


// Timers library
#include <time.h>


// Connections:
// Encoder on LEFT wheel:
const byte encoder0pinA_LEFT = 13;// A pin = interupt pin 1
const byte encoder0pinB_LEFT = 12;// B pin

// LEFT encoder variables:
byte encoder0PinALast_LEFT; // the last value on A pin
boolean Direction_LEFT; // the rotation direction
int duration_LEFT = true; // the number of the pulses
void wheelSpeed_LEFT(); // encoder function

// Logger time
long start_time = 0;
// Static adjustments for engines imperfection

//// main cycle operation time
const int cycle_time = 500; // ms

void setup()
{
 
  pinMode(encoder0pinB_LEFT, INPUT);


  // start serial port:
  Serial.begin(115200); // Initialize the serial port

  // Initialize encoders
  attachInterrupt(encoder0pinA_LEFT, wheelSpeed_LEFT, CHANGE); // pin 2 on arduino


  // create a start time mark
  start_time = millis();

 
  Serial.println("Hi!");
}


void loop()
{

  
  Serial.print("Duration left: ");
  Serial.println(duration_LEFT);

  // convert velocity from odometer pulses to meters per second
  float frequency = 1000 / cycle_time;

  // duration_LEFT / 470 * 2 * pi * (1000 / cycle_time)




  // main cycle delay
  delay(cycle_time);
}


void wheelSpeed_LEFT()
{
  int Lstate_LEFT = digitalRead(encoder0pinA_LEFT);
  if ((encoder0PinALast_LEFT == LOW) && Lstate_LEFT == HIGH)
  {
    int val = digitalRead(encoder0pinB_LEFT);
    if (val == LOW && Direction_LEFT)
    {
      Direction_LEFT = false; //Reverse
    }
    else if (val == HIGH && !Direction_LEFT)
    {
      Direction_LEFT = true; //Forward
    }
  }
  else if ((encoder0PinALast_LEFT == HIGH) && Lstate_LEFT == LOW)
  {
    int val = digitalRead(encoder0pinB_LEFT);
    if (val == HIGH && Direction_LEFT)
    {
      Direction_LEFT = false; //Reverse
    }
    else if (val == LOW && !Direction_LEFT)
    {
      Direction_LEFT = true; //Forward
    }
  }
  encoder0PinALast_LEFT = Lstate_LEFT;
  if (!Direction_LEFT) duration_LEFT++;
  else duration_LEFT--;

}

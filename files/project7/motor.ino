#include <CapacitiveSensor.h>
#include <Servo.h>
/*
  danli's firmware for a capacitive-sensor-driven motors!
*/

// one for forward movement, one for stop
int led1 = 1; //red, stop sign!
int led2 = 0; //green, go sign!

Servo servo1;
Servo servo2;

int capSensePin = 3; //it's odd, i apparently connected to pin 3...OK it's because the bitmask was set to 2. It's set at 1 now.
// Value the sensor needs to read in order to trigger a
// touch. Takes ten samples over a five-second period
// from the touch sensor; chooses the maximum sample
// and sets it to the cutoff value. During this five-
// second setup the sensor should not be touched.
int values = 0;
int capPin;
int get_cutoff() {
  for (int i=0; i<9; i++){
    capPin = readCapacitivePin(capSensePin);
    if (capPin > values) {
      values = capPin;
    delay(5);
    }
  }
  return values;
}
  
int touchedCutoff;

// the setup function runs once when you press reset or power the board
void setup(){
  // Set up the LED
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  servo1.attach(2);
  servo2.attach(7);
  // Get and print the cutoff value.
  touchedCutoff = get_cutoff();
}

// the loop function runs over and over again forever
void loop() {
  // If the capacitive sensor reads above the cutoff,
  // turn on the LED
  if (readCapacitivePin(capSensePin) > touchedCutoff) {
    digitalWrite(led2, HIGH);
    digitalWrite(led1, LOW);
    servo1.write(0);//full speed forward!
    servo2.write(0);
    delay(2);
  }
  else {
    digitalWrite(led2, LOW);
    digitalWrite(led1, HIGH); //red light!
    servo1.write(90);
    servo2.write(90);
  }
}


uint8_t readCapacitivePin(int pinToMeasure){
  // Declare a variable which will hold the PORT,
  // PIN, and DDR registers.
  volatile uint8_t* port;
  volatile uint8_t* ddr;
  volatile uint8_t* pin;
  // Translate the input pin number to the actual register
  // location. Bitmask chooses which bit we want to look at.
  // Attiny44 only has one 8-bit port, Port A (Port B is 4
  // bits wide), so we need to use Port A and its corresponding
  // DDR and PIN values.
  byte bitmask;
  port = &PORTA;
  ddr = &DDRA;
  bitmask = 1 << pinToMeasure;
  pin = &PINA;

  // Discharge the pin by setting it as an output (and writing it low)
  *port &= ~(bitmask);
  *ddr  |= bitmask;
  delay(1);
  // Make the pin an input WITHOUT the internal pull-up on
  *ddr &= ~(bitmask);
  // Now see how long the pin takes to get pulled up
  int cycles = 16000;
  for(int i = 0; i < cycles; i++){
    if (*pin & bitmask){
      cycles = i;
      break;
    }
  }
  // Discharge the pin again by setting it low and as output.
  // It's important to leave the pins low if you want to 
  // be able to touch more than 1 sensor at a time - if
  // the sensor is left pulled high, when you touch
  // two sensors, your body will transfer the charge between
  // sensors.
  *port &= ~(bitmask);
  *ddr  |= bitmask;
  
  return cycles;
}

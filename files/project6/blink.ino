#include <CapacitiveSensor.h>
//#include <SoftwareSerial.h>
//SoftwareSerial mySerial(0, 1);
/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is tset to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Blink
*/

CapacitiveSensor   cs_3_2 = CapacitiveSensor(3,2);        // 10M resistor between pins 3 & 2, pin 2 is sensor pin, add a wire and or foil if desired

int led1 = 1;
int led2 = 0;

int capSensePin = 2;
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
    delay(50);
    }
  }
  return values;
}
  
int touchedCutoff;

// the setup function runs once when you press reset or power the board
void setup(){
//  mySerial.begin(9600);
  // Set up the LED
  pinMode(led1, OUTPUT);
  digitalWrite(led1, HIGH);
  pinMode(led2, OUTPUT);
  digitalWrite(led2, HIGH);
  // Get and print the cutoff value.
  touchedCutoff = get_cutoff();
}

// the loop function runs over and over again forever
void loop() {
  // If the capacitive sensor reads above the cutoff,
  // turn on the LED
  if (readCapacitivePin(capSensePin) > touchedCutoff) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    delay(20);
    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH);
    delay(20);
  }
  else {
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
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
  bitmask = 2 << pinToMeasure;
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

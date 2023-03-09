
// Include the SoftwareSerial library to run serial on Attiny44
#include <SoftwareSerial.h>
#define bit_delay_time 8.5 // bit delay for 115200 with overhead

// declare my serial ports 0 and 1 (RX, TX)
SoftwareSerial mySerial(PA0, PA1);

int sensorPin =  7;     // my analog light intensity sensor pin
int value = 0; //store the reading in value
void setup() {
  mySerial.begin(115200); // set baud rate to 115200 bits per second
  pinMode(sensorPin, INPUT);
  CLKPR = (1 << CLKPCE);
  CLKPR = (0 << CLKPS3) | (0 << CLKPS2) | (0 << CLKPS1) | (0 << CLKPS0);
}

void loop() {
  while (1) {
//    mySerial.write(1);
    mySerial.print("my light sensor reads ");
    value = analogRead(sensorPin);
    mySerial.println(value);
    delay(200);
  } 
}

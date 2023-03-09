/*
 * HCDE Making It 2021 Autumn Quarter!
 * Made by Danli Luo 2021.12.09
 */

// add serial!
//#include <SoftwareSerial.h>
//#define bit_delay_time 8.5 // bit delay for 115200 with overhead
//SoftwareSerial mySerial(PA0, PA1);

// add LEDs!
#include <WS2812.h>
#include <TinyWireM.h>
int numleds = 18; //max value I can handle
WS2812 LED(numleds); // 24 LED
cRGB value;

// set clock!
#define F_CPU 20000000UL

//add touch pin!
int capSensePin = 3;
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

//add time!
//#include <TinyWireM.h>
#include <TinyRTClib.h>
RTC_DS1307 rtc;
int hourvalue;
uint8_t minutevalue;
uint8_t minuteled;

void setup() {
//  mySerial.begin(115200); // set baud rate to 115200 bits per second
  CLKPR = (1 << CLKPCE);
  CLKPR = (0 << CLKPS3) | (0 << CLKPS2) | (0 << CLKPS1) | (0 << CLKPS0); //change 2 and 1 to programmed, clock division factor = 8;
  rtc.begin(); 
  TinyWireM.begin();
  LED.setOutput(2); // Digital Pin 2
  touchedCutoff = get_cutoff();
}

void loop() {
//  mySerial.print("touch pin reads:");
//  mySerial.println(readCapacitivePin(capSensePin));
  value.b = 249; value.g = 249; value.r = 249;
  if (readCapacitivePin(capSensePin) > touchedCutoff) {
    DateTime now = rtc.now();
    minutevalue = now.minute();         // Get the minutes
    uint8_t hour24 = now.hour();
        // map leds!
    //get AM/PM first
    if (hour24 < 12) {
      hourvalue = hour24;
    }
    if (hour24 >= 12) {
      hourvalue = hour24 - 12;
    }
    if (hourvalue == 0) {LED.set_crgb_at(9, value);}
    if (hourvalue == 1) {LED.set_crgb_at(15, value);}
    if (hourvalue == 2) {LED.set_crgb_at(14, value);}
    if (hourvalue == 3) {LED.set_crgb_at(16, value);}
    if (hourvalue == 4) {LED.set_crgb_at(17, value);}
    if (hourvalue == 5) {LED.set_crgb_at(6, value);}
    if (hourvalue == 6) {LED.set_crgb_at(7, value);}
    if (hourvalue == 7) {LED.set_crgb_at(13, value);}
    if (hourvalue == 8) {LED.set_crgb_at(12, value);}
    if (hourvalue == 9) {LED.set_crgb_at(11, value);}
    if (hourvalue == 10) {LED.set_crgb_at(10, value);}
    if (hourvalue == 11) {LED.set_crgb_at(8, value);} 
    LED.set_crgb_at(5, value);// "点"
//    LED.sync();
    if (minutevalue >= -1 && minutevalue < 15) { // "整"
      LED.set_crgb_at(0, value);
      }
    if (minutevalue >= 15 && minutevalue < 30) { // "一刻"
      LED.set_crgb_at(4, value);
      LED.set_crgb_at(1, value);
      }
    if (minutevalue >= 30 && minutevalue < 45) { // "二刻"
      LED.set_crgb_at(3, value);
      LED.set_crgb_at(1, value);
      }
    if (minutevalue >= 45 && minutevalue < 60) { // "三刻"
      LED.set_crgb_at(2, value);
      LED.set_crgb_at(1, value);
      }
    LED.sync();
    delay(3000); // Wait 500 ms
    }
  else {
    value.b = 0; value.g = 0; value.r = 0;
    
    for (int i=0; i<numleds; i++) {
      LED.set_crgb_at(i, value);
    }
    LED.sync();
    delay(500);
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

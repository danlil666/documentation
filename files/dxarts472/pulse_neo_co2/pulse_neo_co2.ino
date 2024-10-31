/*
 * Copyright (c) 2021, Sensirion AG
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * * Neither the name of Sensirion AG nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <Adafruit_NeoPixel.h>
#include <Arduino.h>
#include <SensirionI2CScd4x.h>
#include <Wire.h>

SensirionI2CScd4x scd4x;

void printUint16Hex(uint16_t value) {
    Serial.print(value < 4096 ? "0" : "");
    Serial.print(value < 256 ? "0" : "");
    Serial.print(value < 16 ? "0" : "");
    Serial.print(value, HEX);
}

void printSerialNumber(uint16_t serial0, uint16_t serial1, uint16_t serial2) {
//    Serial.print("Serial: 0x");
//    printUint16Hex(serial0);
//    printUint16Hex(serial1);
//    printUint16Hex(serial2);
//    Serial.println();
}

// pulse sensor behavior setting variables
int pulsePin = 0;                 // Pulse Sensor purple wire connected to analog pin 0
int blinkPin = 13;                // Digital pin to blink led at each beat
int fadePin  = 5;                 // pin to do fancy neopixel effects at each beat
int fadeRate = 0;                 // used to fade LED on with PWM on fadePin

// these variables are volatile because they are used during the interrupt service routine
volatile int BPM;                   // used to hold the pulse rate
volatile int Signal;                // holds the incoming raw data
volatile int IBI = 600;             // holds the time between beats, the Inter-Beat Interval
volatile boolean Pulse = false;     // true when pulse wave is high, false when it's low
volatile boolean QS = false;        // becomes true when Arduoino finds a beat.

// Set up use of NeoPixels
const int NUMPIXELS = 24;           // Put the number of NeoPixels you are using here
const int BRIGHTNESS = 60;          // Set brightness of NeoPixels here
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, fadePin, NEO_GRB + NEO_KHZ800);

int humidity = 255;

void setup() {

    Serial.begin(9600);
    while (!Serial) {
        delay(100);
    }

    Wire.begin();

    uint16_t error;
    char errorMessage[256];

    scd4x.begin(Wire);

    // stop potentially previously started measurement
    error = scd4x.stopPeriodicMeasurement();
    if (error) {
        Serial.print("Error trying to execute stopPeriodicMeasurement(): ");
        errorToString(error, errorMessage, 256);
        Serial.println(errorMessage);
    }

    uint16_t serial0;
    uint16_t serial1;
    uint16_t serial2;
    error = scd4x.getSerialNumber(serial0, serial1, serial2);
    if (error) {
        Serial.print("Error trying to execute getSerialNumber(): ");
        errorToString(error, errorMessage, 256);
        Serial.println(errorMessage);
    } else {
        printSerialNumber(serial0, serial1, serial2);
    }

    // Start Measurement
    error = scd4x.startPeriodicMeasurement();
    if (error) {
        Serial.print("Error trying to execute startPeriodicMeasurement(): ");
        errorToString(error, errorMessage, 256);
        Serial.println(errorMessage);
    }
    pinMode(blinkPin,OUTPUT);         // pin that will blink to your heartbeat!
  //  mySerial.begin(115200);           // Serial output data for debugging or external use
    strip.begin();
    strip.setBrightness(BRIGHTNESS);
    for (int x=0; x < NUMPIXELS; x++) {  // Initialize all pixels to 'off'
       strip.setPixelColor(x, strip.Color(0, 0, 0));
    }
    strip.show();                     // Ensure the pixels are off 
    delay(1000);                      // Wait a second
    interruptSetup();                 // sets up to read Pulse Sensor signal every 2mS 


//    Serial.println("Waiting for first measurement... (5 sec)");
}

void loop() {
    //    sendDataSerial('S', Signal);      // send Processing the raw Pulse Sensor data
    if (QS == true){                    // Quantified Self flag is true when arduino finds a heartbeat
       fadeRate = 255;                  // Set 'fadeRate' Variable to 255 to fade LED with pulse
  //     sendDataSerial('B',BPM);       // send heart rate with a 'B' prefix
  //     sendDataSerial('Q',IBI);       // send time between beats with a 'Q' prefix
       QS = false;                      // reset the Quantified Self flag for next time    
    }
    ledFadeToBeat();                    // Routine that fades color intensity to the beat
    delay(20);                          //  take a break

    uint16_t error;
    char errorMessage[256];

    delay(100);

    // Read Measurement
    uint16_t co2 = 0;
    float temperature = 0.0f;
    float humidity = 0.0f;
    bool isDataReady = false;
    error = scd4x.getDataReadyFlag(isDataReady);
    if (error) {
        Serial.print("Error trying to execute readMeasurement(): ");
        errorToString(error, errorMessage, 256);
        Serial.println(errorMessage);
        return;
    }
    if (!isDataReady) {
        return;
    }
    error = scd4x.readMeasurement(co2, temperature, humidity);
    if (error) {
        Serial.print("Error trying to execute readMeasurement(): ");
        errorToString(error, errorMessage, 256);
        Serial.println(errorMessage);
    } else if (co2 == 0) {
        Serial.println("Invalid sample detected, skipping.");
    } else {
//        Serial.print("Co2:");
        Serial.print(co2);
        Serial.print(",");
//        Serial.print("Temperature:");
        Serial.print(temperature);
        Serial.print(",");
//        Serial.print("Humidity:");
        Serial.println(humidity);
    }
}

void ledFadeToBeat() {
    fadeRate -= 25;                         // Set LED fade value
    fadeRate = constrain(fadeRate,0,255);   // Keep LED fade value from going into negative numbers
    setStrip(fadeRate);                     // Write the value to the NeoPixels 
//    sendDataSerial('R',fadeRate);
}

void sendDataSerial(char symbol, int data ) {
//    mySerial.print(symbol);                // symbol prefix tells Processing what type of data is coming
//    mySerial.println(data);                // the data to send culminating in a carriage return
}

void setStrip(int r) {     // Set the strip to one color intensity (red)
   int g = r;              // Green is set to zero (for non-red colors, change this)
   int b = r;              // Blue is set to zero (for non-red colors, change this)
   for (int x=0; x < NUMPIXELS; x++) {
      strip.setPixelColor(x, strip.Color(r, g, b));
   }
   strip.show();
}

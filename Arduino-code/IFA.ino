/*
Title : IFA Workshop
Author : DataPaulette
Version : 1.0
*/
#include <Adafruit_NeoPixel.h>

#define LED_PIN   11
#define LED_COUNT 12

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

// Speaker
int speaker = 12;

// Tilt sensor
int tilt_1 = 3;
int tilt_2 = 4;
int tilt1Value;
int tilt2Value;

// ButtonHole sensor
int buttonHole = 6;
int bhValue;

// Pressure sensor
const char pressureBtn = A0;
int pressureValue;

// ON/OFF button
int classicBtn = 10;
int cbtnValue;

void setup() {
  pinMode(tilt_1, INPUT_PULLUP);
  pinMode(tilt_2, INPUT_PULLUP);
  pinMode(buttonHole, INPUT_PULLUP);
  pinMode(classicBtn, INPUT_PULLUP);

  strip.begin();
  strip.show(); 

  Serial.begin(9600);
}

void loop() {
  //When we close the button hole, we read the pressure sensor and play music with it
  bhValue = digitalRead(buttonHole);
  //Serial.println(bhValue);
  if (bhValue == LOW) {
    pressureValue = analogRead(pressureBtn);
    Serial.println(pressureValue);
    pressureValue = map(pressureValue, 500, 1023, 262, 4978);
    Serial.println(pressureValue);
    tone(speaker, pressureValue, 100);
    delay(1);
  } else {
    noTone(speaker);
  }

  cbtnValue = digitalRead(classicBtn);
  //Serial.println(classicBtn);
  if (cbtnValue == LOW) {
    theaterChase(strip.Color(127, 127, 127), 100);
  } else {
    strip.clear();
    strip.show();
  }

  int tilt1Value = digitalRead(tilt_1);
  int tilt2Value = digitalRead(tilt_2);
  //Serial.println(tilt1Value);
  //Serial.println(tilt2Value);
  if (tilt1Value == LOW && tilt2Value == HIGH) {
    colorWipe(strip.Color(255,   0,   0), 50);
  } else if (tilt1Value == HIGH && tilt2Value == LOW) {
    colorWipe(strip.Color(0,   0,   255), 50);
  } else {
    strip.clear();
    strip.show();
  }
  
}

// Fill strip pixels one after another with a color. Strip is NOT cleared
// first; anything there will be covered pixel by pixel. Pass in color
// (as a single 'packed' 32-bit value, which you can get by calling
// strip.Color(red, green, blue) as shown in the loop() function above),
// and a delay time (in milliseconds) between pixels.
void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}

// Theater-marquee-style chasing lights. Pass in a color (32-bit value,
// a la strip.Color(r,g,b) as mentioned above), and a delay time (in ms)
// between frames.
void theaterChase(uint32_t color, int wait) {
  for(int a=0; a<10; a++) {  // Repeat 10 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      strip.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in steps of 3...
      for(int c=b; c<strip.numPixels(); c += 3) {
        strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip.show(); // Update strip with new contents
      delay(wait);  // Pause for a moment
    }
  }
}

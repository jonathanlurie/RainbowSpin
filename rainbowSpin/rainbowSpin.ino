// NeoPixel Ring  RainbowSpin (c) 2016 Jonathan Lurie
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN            7

// How many NeoPixels in the ring?
#define NUMPIXELS      24

// instanciation of the main Neopixel object
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// defines the spining speed
int delayShift = 10; 

// The 24 RGB configurations are computed only once and stored here
uint8_t allR[NUMPIXELS];
uint8_t allG[NUMPIXELS];
uint8_t allB[NUMPIXELS];

// to manage the rotation
int shift = 0;


// some init
void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code

  // This initializes the NeoPixel library.
  pixels.begin();

  // To avoid burning people eyes
  pixels.setBrightness(100); // brightness in [0, 255]




  float hueStep = 1. / float(NUMPIXELS);
  float h = 0.0; // hue, starts at 0 (red)
  float s = 1.0; // saturation, at max
  float l = 0.5; // luminance, medium because 0 is black and 1 is white and it's color we want, right?

  // color channels, to be computed
  int r = 0;
  int g = 0;
  int b = 0;

  // computing all the 24 different colors, one for each LED
  for(int i=0;i<NUMPIXELS;i++){
    hls2rgb(h, l, s, &r, &g, &b);
    allR[i] = r;
    allG[i] = g;
    allB[i] = b;
    h += hueStep;
  }

}


// let's loop!
void loop() {

  for(int i=0;i<NUMPIXELS;i++){

    // the color to attributes each led depends on its position and on the the shift
    int indexInColorArray = (i+shift) % NUMPIXELS;

    // setting the color
    //pixels.setPixelColor(i, pixels.Color(allR[indexInColorArray], allG[indexInColorArray], allB[indexInColorArray]));
    pixels.setPixelColor(i, allR[indexInColorArray], allG[indexInColorArray], allB[indexInColorArray]);

    // update it
    pixels.show();

  }


  // reinit the shift if needed
  shift = shift < (NUMPIXELS-1) ? ++shift : 0;

  // wait for the next loop
  delay(delayShift);
}

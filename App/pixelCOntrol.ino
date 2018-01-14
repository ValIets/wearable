#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            D7

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      1

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setupLED() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code
  pixels.begin(); // This initializes the NeoPixel library.
  turnOff();
}
void turnRed(){
    pixels.setPixelColor(0, pixels.Color(255,0,0)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware.
}
void turnGreen(){
    pixels.setPixelColor(0, pixels.Color(0,255,0)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware.
}
void turnPurple(){
    pixels.setPixelColor(0, pixels.Color(255,0,255)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware.
}
void turnOff() {
    pixels.setPixelColor(0, pixels.Color(0,0,0)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware.
}


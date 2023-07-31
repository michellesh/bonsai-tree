#define FASTLED_ESP8266_NODEMCU_PIN_ORDER
#include <FastLED.h>

#define BUTTON_PIN 5
#define LED_PIN 2
#define NUM_LEDS 15

#include "colors.h"
#include "Palette.h"
Palette palette;

CRGB leds[NUM_LEDS];
int mode = 0;
int numModes = 2;

void setup() {
  Serial.begin(115200);
  delay(500);

  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(100);

  pinMode(BUTTON_PIN, INPUT);
}

void loop() {
  FastLED.clear();
  palette.cycle();

  static int buttonPushed = 0;
  int buttonRead = digitalRead(BUTTON_PIN); // HIGH when button held
  if (buttonRead == HIGH) {
    buttonPushed = 1;
  } else if (buttonPushed) {
    Serial.println("CLICK");
    mode++;
    mode %= numModes;
    buttonPushed = 0;
  }

  if (mode == 0) {
    twinkle();
  } else {
    solidColorFade();
  }

  FastLED.setBrightness(100);
  FastLED.show();
}

void solidColorFade() {
  int paletteIndex = beatsin8(10, 0, MAX_PALETTE_INDEX);
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = palette.getColorFromPalette(paletteIndex);
  }
}

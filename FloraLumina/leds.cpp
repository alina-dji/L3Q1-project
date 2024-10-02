#include "setup.h"
#include "leds.h"

CRGB leds[NUM_LEDS];
uint8_t gHue = 0;

void setupLeds() {
  FastLED.addLeds<LEDS_TYPE, LEDS_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  turnOffAllLights();
}


void setColor(int red, int green, int blue) {
  CRGB color = CRGB(red, green, blue);
  fill_solid(leds, NUM_LEDS, color);
  FastLED.show();
}
/**
 * @brief static rainbow
 * 
 */
// static rainbow 
void rainbowColor() {
  fill_rainbow(leds, NUM_LEDS, gHue, 7); // FastLED's built-in rainbow generator
  FastLED.show();
}
/**
 * @brief rainbow
 * 
 */
void rainbow() {
  static uint8_t hue = 0;
  fill_rainbow(leds, NUM_LEDS, hue, 7); 
  hue++;
  FastLED.show();
}

/**
 * @brief random colored speckles that blink in and fade smoothly
 * 
 */
void confetti() {
  fadeToBlackBy(leds, NUM_LEDS, 10);
  int pos = random16(NUM_LEDS);
  leds[pos] += CHSV( gHue + random8(64), 200, 255);
  FastLED.show();
}
/**
 * @brief colored stripes pulsing at a defined Beats-Per-Minute (BPM)
 * 
 */
// good add to interface
void bpm() {
  uint8_t BeatsPerMinute = 62;
  CRGBPalette16 palette = PartyColors_p;
  uint8_t beat = beatsin8(BeatsPerMinute, 64, 255);
  for( int i = 0; i < NUM_LEDS; i++) { 
    leds[i] = ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*10));
  }
  FastLED.show();
}
/**
 * @brief eight colored dots, weaving in and out of sync with each other
 * 
 */
void juggle() {
  fadeToBlackBy(leds, NUM_LEDS, 20);
  uint8_t dothue = 0;
  for( int i = 0; i < 8; i++) {
    leds[beatsin16( i+7, 0, NUM_LEDS-1 )] |= CHSV(dothue, 200, 255);
    dothue += 32;
  }
  FastLED.show();
}


void heartBeat()
{
  static uint8_t brightness = 0;
  static int i = 0;
  static bool increasing = true;
  static unsigned long lastUpdateTime = 0;
  unsigned long currentTime = millis();
  // Check if it's time to update
  if (currentTime - lastUpdateTime >= 10) {
    lastUpdateTime = currentTime; // Update the time
    if (increasing) {
      brightness = 128 + sin8(i);
      fill_solid(leds, NUM_LEDS, CRGB::Purple);
      FastLED.setBrightness(brightness);
      FastLED.show();
      i++;
      if (i >= 128) {
        increasing = false;
        i = 127; // Start decreasing
      }
    } else {
      brightness = 128 + sin8(i);
      fill_solid(leds, NUM_LEDS, CRGB::Purple);
      FastLED.setBrightness(brightness);
      FastLED.show();
      i--;
      if (i < 0) {
        increasing = true;
        i = 0; // Start increasing
      }
    }
  }
}

void theaterChase() {
  static uint8_t hue = 0;
  for (int j = 0; j < 3; j++) {
    for (int i = 0; i < NUM_LEDS; i += 3) {
      leds[i + j] = CHSV(hue + i * 10, 255, 255);
    }
  }
  FastLED.show();
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  hue += 1;
}


void colorWipe() {
  static uint8_t hue = 0;
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CHSV(hue, 255, 255);
  }
  hue += 1;
}

/* ----------------------- SOUND REACTIVE MODE ----------------------- 
Source: https://github.com/Tayfex/ArduinoMusicLights
--------------------------------------------------------------------- */

// To how many sound levels should the volume be mapped
#define AMOUNT_LEVELS 20
// Amount of different colors (must be equal to the length of colors[])
#define AMOUNT_COLORS 12
// Amount of samples to calculate current volunme
#define VOLUME_SAMPLES 20
// Complete color palette that is circled through (should have AMOUNT_COLORS entries)
CRGB colors[] = {
    CRGB(120, 0, 0),
    CRGB(90, 30, 0),
    CRGB(60, 60, 0),
    CRGB(30, 90, 0),
    CRGB(0, 120, 0),
    CRGB(0, 90, 30),
    CRGB(0, 60, 60),
    CRGB(0, 30, 90),
    CRGB(0, 0, 120),
    CRGB(30, 0, 90),
    CRGB(60, 0, 60),
    CRGB(90, 0, 30)};

int volume; // Current volume
int volumes[20]; // Last x samples of the volume
int level = 0; // Current sound level
float average = 0; // Current average sound level
bool averageExceed = false; // True whenever the average is exceed for the first time
bool levelJump = false; // True if the sound level jumped up
long nextJump = 0; // Time the next jump can happen again
int color = 0; // True if the color should be changed due to a hard level increase

void soundReactive() {
    // Get current volume
    volume = getVolume(VOLUME_SAMPLES);
    average = getAverage(volume);
    // Convert volume to level
    level = getLevel(volume, false);
    // Change color and (eventually) mode on level jump
    if (levelJump) {
        color = nextColor();
    }
    // Play one mode
    modeFlashPulse(volume, colors[color]);
    FastLED.show();
}

// This mode makes a pulse
void modeFlashPulse(int volume, CRGB color) {
  if(volume > average * 1.15 && averageExceed == false) {
    averageExceed = true;
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = color;   
    }
  } else {
    if(volume < average * 1.15) {
      averageExceed = false;
    }
    for (int i = 0; i < NUM_LEDS; i++) {
      CRGB colorTmp = leds[i];
      leds[i] = setBrightnessOfColor(leds[i], 0.7);   
    }
  }
}

// Set brightness of the color
CRGB setBrightnessOfColor(CRGB color, float brightness) {
  CRGB colorTmp = CRGB(color.r, color.g, color.b);
  // Adjust brightness for every channel
  colorTmp.r = colorTmp.r * brightness;
  colorTmp.g = colorTmp.g * brightness;
  colorTmp.b = colorTmp.b * brightness;
  return colorTmp;
}

// Reads the current volume and returns it
// unsigned long previousMillis = 0; // Variable to store the previous timestamp
int getVolume(int samples) {
  static unsigned long previousMillis = 0; // Variable to store the previous timestamp
  int volume = 0;
  for (int i = 0; i < samples; i++) {
    unsigned long currentMillis = millis(); // Get the current time
    if (currentMillis - previousMillis >= 1) { // Check if 1 millisecond has elapsed
      int sound = analogRead(MIC_PIN);
      if (sound > volume) {
        volume = sound;
      }
      previousMillis = currentMillis; // Update the previous timestamp
    }
  }
  return volume;
}

// Maps the volume to a level
int getLevel(int volume, bool smooth) {
  int levelTmp = map(volume, 550, 750, 0, AMOUNT_LEVELS);
  // Did the level jump up?
  if (levelTmp - level > 10) {
    levelJump = true;
  } else {
    levelJump = false;
  }
  // Increase or decrease level
  if (levelTmp > level) {
    if (smooth) {
      levelTmp = level + 1;
    }
  } else {
    levelTmp = level - 1;
  }
  // Avoid negative level
  if (levelTmp < 0) {
    levelTmp = 0;
  } else if (levelTmp > AMOUNT_LEVELS) {
    levelTmp = AMOUNT_LEVELS;
  }
  return levelTmp;
}

// Calculates the average of the last 20 samples and returns it
float getAverage(int volume) {
  float average = 0;
  for (int i = 19; i > 0; i--) {
    average = average + volumes[i];
    volumes[i] = volumes[i - 1];
  }
  volumes[0] = volume;
  average = average / 19;
  return average;
}

// Turns off all lights
void turnOffAllLights() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(0, 0, 0);
  }
  FastLED.show();
}

// Circles to the next color
int nextColor() {
  int nextColor = color + 1;
  if (nextColor == AMOUNT_COLORS) {
    nextColor = 0;
  }
  return nextColor;
}
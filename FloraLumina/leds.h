#ifndef LEDS_H
#define LEDS_H

void setupLeds();
void setColor(int red, int green, int blue);
void rainbowColor();
void rainbow();
void confetti();
void bpm();
void juggle();
void heartBeat();
void theaterChase();
void colorWipe();

void soundReactive();
void modeFlashPulse(int volume, CRGB color);
CRGB setBrightnessOfColor(CRGB color, float brightness);
int getVolume(int samples);
int getLevel(int volume, bool smooth);
uint8_t getLevel(uint8_t volume, bool smooth);
float getAverage(int volume);
void turnOffAllLights();
int nextColor();

#endif
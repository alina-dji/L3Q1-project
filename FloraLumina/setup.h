#ifndef SETUP_H
#define SETUP_H

#include <Arduino.h>
#include <FastLED.h>
#include <ESP8266mDNS.h>
#include <WiFiManager.h>
#include <ESP8266WebServer.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_TSL2561_U.h>
#include <Adafruit_BME280.h>
#include <Adafruit_VL53L0X.h>
#include <ESP8266WiFi.h>
#include "driver.h"


#define NUM_LEDS 24
#define LEDS_PIN 0
#define LEDS_TYPE WS2812B
#define COLOR_ORDER GRB
#define MIC_PIN A0

// Motor
extern Driver motor;
extern int motorSpeedValue;
extern int motorPositionValue;
extern bool firstRotation;

// Colors
extern uint8_t red;
extern uint8_t green;
extern uint8_t blue;

// Light effects
extern bool staticRainbowMode;
extern bool rainbowMode;
extern bool confettiMode;
extern bool heartBeatMode;
extern bool theaterChaseMode;
// extern bool glitteringStarsMode;
extern bool colorWipeMode;
extern bool bpmMode;
extern bool juggleMode;
extern bool soundReactiveMode;

// Flower modes
extern bool distanceReactiveMode;
extern bool lightTemperatureMode;
extern bool lifeCycleMode;
extern bool positionTemperatureMode;
extern bool positionHumidityMode;
extern bool epiphyllumFlowerMode;
extern bool orangeLilyFlowerMode;
extern bool tulipFlowerMode;

// Web server
extern ESP8266WebServer server;

#endif
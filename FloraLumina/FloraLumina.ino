#include "driver.h"
#include "setup.h"
#include "wemosWifi.h"
#include "wemosWebServer.h"
#include "leds.h"
#include "generateTime.h"
#include "sensorData.h"
#include "flowerControl.h"

ESP8266WebServer server(80);

Driver motor;
int motorSpeedValue = 40;
int motorPositionValue = 0;
bool firstRotation = true;

uint8_t red = 0;
uint8_t green = 255;
uint8_t blue = 0;

bool staticRainbowMode = false;
bool rainbowMode = false;
bool confettiMode = false;
bool heartBeatMode = false;
bool theaterChaseMode = false;
// bool glitteringStarsMode = false;
bool colorWipeMode = false;
bool bpmMode = false;
bool juggleMode = false;


bool soundReactiveMode = false;
bool distanceReactiveMode = false;
bool lightTemperatureMode = false;
bool lifeCycleMode = false;
bool positionTemperatureMode = false;
bool positionHumidityMode = false;
bool epiphyllumFlowerMode = false;
bool orangeLilyFlowerMode = false;
bool tulipFlowerMode = false;

void setup() {
  motor = Driver();
  setupWemosWifi();
  setupWemosWebServer();
  setupSensorData();
  setupLeds();
  Serial.begin(115200);
}

void loop() {
  // TODO: write motorLoop() function
  if (firstRotation) {
    motor.stepCounter(server);
  }
  firstRotation = false;
  
  if(WiFi.status() == WL_CONNECTED) {
    wemosWebServerLoop();
    // motor.changePosition(motorPositionValue, motorSpeedValue);
    // Light Modes
    if(staticRainbowMode) {
      rainbowColor();
    } else if(rainbowMode) {
      rainbow();
    } else if(confettiMode) {
      confetti();
    } else if(heartBeatMode) {
      heartBeat();
    } else if(theaterChaseMode) {
      theaterChase();
    } else if(colorWipeMode) {
      colorWipe();
    } else if(bpmMode) {
      bpm();
    } else if (juggleMode) {
      juggle();
    } else if (soundReactiveMode) {
      soundReactive();
    } else {
      setColor(red, green, blue);
    }
    // Flower Modes
    if(distanceReactiveMode) {
      setPositionWithDistance();
    } else if(lightTemperatureMode) {
      setColorWithTemperature();
    } else if(lifeCycleMode) {
      lifeCycle();
    } else if(positionTemperatureMode) {
      temperatureChangePosition();
    } else if(positionHumidityMode) {
      humidityChangePosition();
    } else if(epiphyllumFlowerMode){
      epiphyllumFlower();
    }else if(orangeLilyFlowerMode){
      orangeLilyFlower();
    } else if(tulipFlowerMode) {
      tulipFlower();
    } else {
      motor.changePosition(motorPositionValue, motorSpeedValue);
    }
  } else {
    // if the wiFi connection is not established, open the petals and light it up in white
    setColor(255, 255, 255);
    motor.changePosition(100, motorSpeedValue);
  }
}

/**
 * @file flowerControl.cpp
 * @brief 
 * @version 0.1
 * @date 2024-05-26
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "flowerControl.h"
#include "setup.h"
#include "sensorData.h"
#include "driver.h"
#include "generateTime.h"
#include "leds.h"

// void epiphyllumFlower() {
//   setColor(255, 255, 255);
//   static int counteur = 0;
//   static int lum = getLuminosity();
//   if(counteur >= 2000){
//     lum = getLuminosity();
//     counteur = 0;
//   }
//   counteur++;
//   if(lum < 6) {
//     motor.changePosition(100, motorPositionValue);
//   } else {
//     motor.changePosition(0, motorPositionValue);
//   }
// }

void epiphyllumFlower() {
  setColor(255, 255, 255);
  int luminosity = getLuminosity();
  if(luminosity < 6) {
    motor.changePosition(100, motorPositionValue);
  } else {
    motor.changePosition(0, motorPositionValue);
  }
}

// void orangeLilyFlower() {
//   setColor(205, 69, 15);
//   static int counteur = 0;
//   static int lum = getLuminosity();
//   static int humi = getHumidity();
//   if(counteur >= 2000){
//     lum = getLuminosity();
//     humi = getHumidity();
//     counteur = 0;
//   }
//   counteur++;
  
//   if(lum > 6 && humi >= 50 ) {
//     motor.changePosition(100, motorPositionValue);
//   } else {
//     motor.changePosition(0, motorPositionValue);
//   }
// }

void orangeLilyFlower() {
  setColor(205, 69, 15);
  int luminosity = getLuminosity();
  int humidity = getHumidity();
  if(luminosity > 6 && humidity >= 50) {
    motor.changePosition(100, motorPositionValue);
  } else {
    motor.changePosition(0, motorPositionValue);
  }
}

// void tulipFlower() {
//   setColor(228, 56, 60);
//   static int counteur = 0;
//   static int lum = getLuminosity();
//   static int temp = getTemperature();
//   if(counteur >= 2000){
//     lum = getLuminosity();
//     temp = getTemperature();
//     counteur = 0;
//   }
//   counteur++;
//   if(lum > 6 && temp >= 20) {
//     motor.changePosition(100, motorPositionValue);
//   } else {
//     motor.changePosition(0, motorPositionValue);
//   }
// }

void tulipFlower() {
  setColor(228, 56, 60);
  int luminosity = getLuminosity();
  int temperature = getTemperature();
  if(luminosity > 6 && temperature >= 20) {
    motor.changePosition(100, motorPositionValue);
  } else {
    motor.changePosition(0, motorPositionValue);
  }
}

void lifeCycle(){
  unsigned long currentMillis = millis()%600000;
  if(currentMillis <= 30000){
    motor.changePosition(10, motorSpeedValue);
  }
  if(currentMillis >30000 && currentMillis <= 60000){
    motor.changePosition(20, motorSpeedValue);
  }
  if(currentMillis >60000 && currentMillis <= 90000){
    motor.changePosition(30, motorSpeedValue);
  }
  if(currentMillis >90000 && currentMillis <= 120000){
    motor.changePosition(40, motorSpeedValue);
  }
  if(currentMillis >120000 && currentMillis <= 150000){
    motor.changePosition(50, motorSpeedValue);
  }
  if(currentMillis >150000 && currentMillis <= 180000){
    motor.changePosition(60, motorSpeedValue);
  }
  if(currentMillis >180000 && currentMillis <= 210000){
    motor.changePosition(70, motorSpeedValue);
  }
  if(currentMillis >210000 && currentMillis <= 240000){
    motor.changePosition(80, motorSpeedValue);
  }
  if(currentMillis >240000 && currentMillis <= 270000){
    motor.changePosition(90, motorSpeedValue);
  }
    if(currentMillis >270000 && currentMillis <= 300000){
    motor.changePosition(100, motorSpeedValue);
  }
  if(currentMillis >300000 && currentMillis <= 330000){
    motor.changePosition(90, motorSpeedValue);
  }
  if(currentMillis >330000 && currentMillis <= 360000){
    motor.changePosition(80, motorSpeedValue);
  }
  if(currentMillis >360000 && currentMillis <= 390000){
    motor.changePosition(70, motorSpeedValue);
  }
  if(currentMillis >390000 && currentMillis <= 420000){
    motor.changePosition(60, motorSpeedValue);
  }
  if(currentMillis >420000 && currentMillis <= 450000){
    motor.changePosition(50, motorSpeedValue);
  }
  if(currentMillis >450000 && currentMillis <= 480000){
    motor.changePosition(40, motorSpeedValue);
  }
  if(currentMillis >480000 && currentMillis <= 510000){
    motor.changePosition(30, motorSpeedValue);
  }
  if(currentMillis >510000 && currentMillis <= 540000){
    motor.changePosition(20, motorSpeedValue);
  }
  if(currentMillis >540000 && currentMillis <= 570000){
    motor.changePosition(10, motorSpeedValue);
  }
  if(currentMillis >570000 && currentMillis <= 600000){
    motor.changePosition(0, motorSpeedValue);
  }
}

void humidityChangePosition(){
  static int humiditePos = map(getHumidity(), 0, 80, 0, 100);
  int humidite = getHumidity();

  static int oldHumidite = humidite;
  if(humidite > 3+oldHumidite || humidite < oldHumidite-3){
    oldHumidite = humidite;
    if(humidite < 30){
      humidite = 30;
    }
    if(humidite > 80){
      humidite = 80;
    }
    humiditePos = map(humidite, 0, 80, 0, 100);
  }
  
  motor.changePosition(humiditePos, motorSpeedValue);
}

void temperatureChangePosition(){
  int temperature = getTemperature();
  if(temperature < 10){
    temperature = 10;
  }
  if(temperature > 30){
    temperature = 30;
  }
  int tempPos = map(temperature, 10, 30, 0, 100);
  motor.changePosition(tempPos, motorSpeedValue);
}

void setPositionWithDistance() {
  bool isOpen = false;
  if (getDistance() < 300) {
    if (isOpen) {
      motor.changePosition(100, motorSpeedValue);
    } else {
      motor.changePosition(0, motorSpeedValue);
    }
    isOpen = !isOpen;
  }
}

// void setColorWithTemperature() {
//   if (getTemperature() < 25) {
//     setColor(0, 0, 255);
//   } else {
//     setColor(255, 0, 0);
//   }
// }

void setColorWithTemperature() {
  int temp = getTemperature();
  if (temp < 10) {
    setColor(0, 0, 255); // Blue for cold temperatures
  } else if (temp < 20) {
    setColor(0, 255, 255); // Cyan for cool temperatures
  } else if (temp < 30) {
    setColor(0, 255, 0); // Green for moderate temperatures
  } else if (temp < 40) {
    setColor(255, 255, 0); // Yellow for warm temperatures
  } else {
    setColor(255, 0, 0); // Red for hot temperatures
  }
}

void turnOff() {
  motor.changePosition(0, motorPositionValue);
  turnOffAllLights();
}

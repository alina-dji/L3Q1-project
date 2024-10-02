#include "setup.h"
#include "wemosWebServer.h"
#include "webPage.h"
#include "sensorData.h"
#include "generateTime.h"
#include "flowerControl.h"

void handleRoot() {
  server.send(200, "text/html", index_html);
}

void handleSetColor() {
  String hexColor = server.arg("color");
  // Convert hex to decimal
  int number = (int)strtol(&hexColor[0], NULL, 16);
  red = number >> 16;
  green = number >> 8 & 0xFF;
  blue = number & 0xFF;
  handleRoot();
}

void handleSetMotorPosition() {
  motorPositionValue = server.arg("motorPosition").toInt();
  handleRoot();
}

void handleSetMotorSpeed() {
  int speedPercentage = server.arg("motorSpeed").toInt();
  Serial.print(speedPercentage);
  // motorSpeedValue = 150 -  map(speedPercentage, 0, 100, 0, 130);
  motorSpeedValue =  map(speedPercentage, 0, 100, 150, 40);
  Serial.print(motorSpeedValue);
  handleRoot();
}

void handleGetLuminosityData() {
    server.send(200, "text/plain", String(getLuminosity()));
}

void handleGetTemperatureData() {
    server.send(200, "text/plain", String(getTemperature()));
}

void handleGetHumidityData() {
  server.send(200, "text/plain", String(getHumidity()));
}

void handleGetPressureData() {
  server.send(200, "text/plain", String(getPressure()));
}

void handleGetDistanceData() {
  if(motor.isRotate()) {
     server.send(200, "text/plain", String(getDistance()));
  }
}

void handleSetFlowerMode() {
  if (server.arg("flowerMode") == "distanceReactive") {
    allFlowerModesOnFalse();
    distanceReactiveMode = true;
  } else if (server.arg("flowerMode") == "lightTemperature") {
    allFlowerModesOnFalse();
    lightTemperatureMode = true;
  } else if (server.arg("flowerMode") == "lifeCycle") {
    allFlowerModesOnFalse();
    lifeCycleMode = true;
  } else if (server.arg("flowerMode") == "positionTemperature") {
    allFlowerModesOnFalse();
    positionTemperatureMode = true;
  } else if(server.arg("flowerMode") == "positionHumidity") {
    allFlowerModesOnFalse();
    positionHumidityMode = true;  
  } else if(server.arg("flowerMode") == "epiphyllum") {
    allFlowerModesOnFalse();
    epiphyllumFlowerMode = true;
  } else if(server.arg("flowerMode") == "orangeLily") {
   allFlowerModesOnFalse();
   orangeLilyFlowerMode = true;
  } else if(server.arg("flowerMode") == "tulip") {
    tulipFlowerMode = true;
    allFlowerModesOnFalse();
  } else {
    allFlowerModesOnFalse();
  }
  handleRoot();
}

void handleSetLightMode() {
  if (server.arg("lightMode") == "staticRainbow") {
    allLightModesOnFalse();
    staticRainbowMode = true;
  } else if (server.arg("lightMode") == "rainbow") {
    allLightModesOnFalse();
    rainbowMode = true;
  } else if (server.arg("lightMode") == "confetti") {
    allLightModesOnFalse();
    confettiMode = true;
  } else if (server.arg("lightMode") == "heartBeat") {
    allLightModesOnFalse();
    heartBeatMode = true;
  } else if (server.arg("lightMode") == "theaterChase") {
    allLightModesOnFalse();
    theaterChaseMode = true;
  } else if (server.arg("lightMode") == "colorWipe") {
    allLightModesOnFalse();
    colorWipeMode = true;
  } else if (server.arg("lightMode") == "soundReactive") {
    allLightModesOnFalse();
    soundReactiveMode = true;
  } else {
    allLightModesOnFalse();
  }
  handleRoot();
}

// TODO: make a 404 web page ?
void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) { message += " " + server.argName(i) + ": " + server.arg(i) + "\n"; }
  server.send(404, "text/plain", message);
}

void setupWemosWebServer() {
  MDNS.begin("floralumina"); //floralumina.local
  server.on("/", handleRoot);
  server.on("/setColor", handleSetColor);
  server.on("/setLightMode", handleSetLightMode);
  server.on("/setFlowerMode", handleSetFlowerMode);
  server.on("/setMotorPosition", handleSetMotorPosition);
  server.on("/setMotorSpeed", handleSetMotorSpeed);
  server.on("/getLuminosityData", handleGetLuminosityData);
  server.on("/getTemperatureData", handleGetTemperatureData);
  server.on("/getHumidityData", handleGetHumidityData);
  server.on("/getPressureData", handleGetPressureData);
  server.on("/getDistanceData", handleGetDistanceData);
  server.onNotFound(handleNotFound);
  server.begin();
}

void wemosWebServerLoop() {
  server.handleClient();
  MDNS.update();
}

void allLightModesOnFalse() {
  staticRainbowMode = false;
  rainbowMode = false;
  confettiMode = false;
  heartBeatMode = false;
  theaterChaseMode = false;
  // glitteringStarsMode = false;
  colorWipeMode = false;
  bpmMode = false;
  juggleMode = false;
}

void allFlowerModesOnFalse() {
  distanceReactiveMode = false;
  lightTemperatureMode = false;
  lifeCycleMode = false;
  positionTemperatureMode = false;
  positionHumidityMode = false;
  epiphyllumFlowerMode = false;
  orangeLilyFlowerMode = false;
  tulipFlowerMode = false;
}
#ifndef WEMOS_WEB_SERVER_H
#define WEMOS_WEB_SERVER_H

void setupWemosWebServer();
void wemosWebServerLoop();

void handleNotFound();
void handleRoot();
void handleSetColor();
void handleSetMotorPosition();
void handleSetMotorSpeed();
void handleGetLuminosityData();
void handleGetTemperatureData();
void handleGetHumidityData();
void handleGetPressureData();
void handleGetDistanceData();
void handleSetLightMode();
void handleSetFlowerMode();

void allLightModesOnFalse();
void allFlowerModesOnFalse();


#endif
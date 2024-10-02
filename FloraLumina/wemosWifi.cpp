#include "setup.h"
#include "wemosWifi.h"

void setupWemosWifi() {
  WiFi.mode(WIFI_STA); // explicitly sets wifi mode to station, esp defaults to STA+AP
  WiFiManager wm;
  wm.resetSettings(); // reset settings - wipe stored credentials for testing
  bool connected;
  connected = wm.autoConnect("Flora Lumina"); // password protected AP
}

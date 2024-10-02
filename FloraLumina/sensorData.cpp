#include "setup.h"
#include "sensorData.h"

sensors_event_t event;
VL53L0X_RangingMeasurementData_t measure;

Adafruit_TSL2561_Unified tsl = Adafruit_TSL2561_Unified(TSL2561_ADDR_FLOAT, 12345);
Adafruit_BME280 bme;
Adafruit_VL53L0X vl53 = Adafruit_VL53L0X();
/**
 * @brief Initialisation des capteur.
 * 
 */
void setupSensorData() {
  tsl.begin();
  bme.begin(0x76);
  vl53.begin();
}
/**
 * @brief Get the Luminosity object
 * 
 * @return int 
 */
int getLuminosity() {
  tsl.getEvent(&event);
  return event.light;
}
/**
 * @brief Get the Temperature object
 * 
 * @return int 
 */
int getTemperature() {
  return bme.readTemperature();
}
/**
 * @brief Get the Humidity object
 * 
 * @return int 
 */
int getHumidity() {
  return bme.readHumidity();
}
/**
 * @brief Get the Pressure object
 * 
 * @return int 
 */
int getPressure() {
  return bme.readPressure();
}
/**
 * @brief Get the Distance object
 * 
 * @return int 
 */
int getDistance() {
  vl53.rangingTest(&measure, false);
  return measure.RangeMilliMeter;
}
#include "map"
#include "AS726X.h"

AS726X sensor;

typedef std::map<int, float> MeasurementMap;

void setup() {
  Wire.begin();
  Serial.begin(115200);

  sensor.begin();
  sensor.enableBulb();
}

void loop() {
  MeasurementMap measurementMap = getMeasurementMap(sensor);

  for (auto const& [key, value] : measurementMap) Serial.printf("%d:%.2f,", key, value);

  Serial.println();
}

MeasurementMap getMeasurementMap(AS726X sensor) {
  sensor.takeMeasurements();

  return {
    { 610, sensor.getCalibratedR() },
    { 680, sensor.getCalibratedS() },
    { 730, sensor.getCalibratedT() },
    { 760, sensor.getCalibratedU() },
    { 810, sensor.getCalibratedV() },
    { 860, sensor.getCalibratedW() }
  };
}

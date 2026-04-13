#pragma once
#include <cstring>
#include <algorithm>
#include <thread>

#include "wiringPi.h"
#include "wiringPiI2C.h"

#define SHT4x_DEFAULT_ADDR 0x44 /**< SHT4x I2C Address */
#define SHT4x_HUMIDITY_ID 0x0401
#define SHT4x_TEMPERATURE_ID 0x0400
#define SHT4x_NOHEAT_HIGHPRECISION 0xFD /**< High precision measurement, no heater */
#define SHT4x_NOHEAT_MEDPRECISION 0xF6 /**< Medium precision measurement, no heater */
#define SHT4x_NOHEAT_LOWPRECISION 0xE0 /**< Low precision measurement, no heater */
#define SHT4x_HIGHHEAT_1S 0x39 /**< High precision measurement, high heat for 1 sec */
#define SHT4x_HIGHHEAT_100MS 0x32 /**< High precision measurement, high heat for 0.1 sec */
#define SHT4x_MEDHEAT_1S 0x2F /**< High precision measurement, med heat for 1 sec */
#define SHT4x_MEDHEAT_100MS 0x24 /**< High precision measurement, med heat for 0.1 sec */
#define SHT4x_LOWHEAT_1S 0x1E /**< High precision measurement, low heat for 1 sec */
#define SHT4x_LOWHEAT_100MS 0x15 /**< High precision measurement, low heat for 0.1 sec */

#define SHT4x_READSERIAL 0x89 /**< Read Out of Serial Register */
#define SHT4x_SOFTRESET 0x94  /**< Soft Reset */

enum SHT4X_PRECISION {
  HIGH_PRECISION,
  MED_PRECISION,
  LOW_PRECISION
};

enum SHT4X_HEATER {
  NO_HEATER,
  HIGH_HEATER_1S,
  HIGH_HEATER_100MS,
  MED_HEATER_1S,
  MED_HEATER_100MS,
  LOW_HEATER_1S,
  LOW_HEATER_100MS,
};

class SHT4x {
public:
  SHT4x(uint8_t address, int16_t humidityID, int16_t temperatureID);
  ~SHT4x(void);

  bool begin();
  uint32_t readSerial(void);
  bool reset(void);

  void Read(float &humidity, float &temperature);
  void setPrecision(SHT4X_PRECISION prec);
  SHT4X_PRECISION getPrecision(void);
  void setHeater(SHT4X_HEATER heat);
  SHT4X_HEATER getHeater(void);

private:
  float _temperature;
  float _humidity;
  int16_t _HumiditySensorID = 0x0401;
  int16_t _TemperatureSensorID = 0x0400;

  uint8_t _Address;

  int32_t _handle;

  uint16_t _sensorid_humidity; ///< ID number for humidity
  uint16_t _sensorid_temp;     ///< ID number for temperature

  SHT4X_PRECISION _precision = HIGH_PRECISION;
  SHT4X_HEATER _heater = NO_HEATER;

  bool writeCommand(uint16_t cmd);
  bool readCommand(uint16_t command, uint8_t *buffer, uint8_t num_bytes);
};

#include "SHT4X.h"

static uint8_t crc8(const uint8_t *data, int len);

SHT4x::SHT4x(uint8_t address, int16_t humidityID, int16_t temperatureID) {
  _HumiditySensorID = humidityID;
  _TemperatureSensorID = temperatureID;
  _Address = address;

  _handle = wiringPiI2CSetup(_Address);
}

SHT4x::~SHT4x(void) {
}

bool SHT4x::begin() {
  if (!reset()) {
    return false;
  }
  return true;
}

uint32_t SHT4x::readSerial(void) {
  uint8_t cmd = SHT4x_READSERIAL;
  uint8_t reply[6];

  if (!wiringPiI2CRawWrite(_handle, &cmd, 1)) {
    return false;
  }
  std::this_thread::sleep_for((std::chrono::milliseconds(10)));
  if (!wiringPiI2CRawRead(_handle, reply, 6)) {
    return false;
  }

  if ((crc8(reply, 2) != reply[2]) || (crc8(reply + 3, 2) != reply[5])) {
    return false;
  }

  uint32_t serial = 0;
  serial = reply[0];
  serial <<= 8;
  serial |= reply[1];
  serial <<= 8;
  serial |= reply[3];
  serial <<= 8;
  serial |= reply[4];

  return serial;
}

bool SHT4x::reset(void) {
  uint8_t cmd = SHT4x_SOFTRESET;

  if (!wiringPiI2CRawWrite(_handle, &cmd, 1)) {
    return false;
  }
  delay(1);
  return true;
}

void SHT4x::Read(float &humidity, float &temperature) {
  bool success = false;
  uint8_t txBytes[1] = { 0xFD };
  success = wiringPiI2CRawWrite(_handle, txBytes, 1);
  std::this_thread::sleep_for(std::chrono::milliseconds(10));
  uint8_t rxBytes[6] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  success = wiringPiI2CRawRead(_handle, rxBytes, 6);
  //
  uint16_t t_ticks = rxBytes[0] * 256 + rxBytes[1];
  uint8_t checksum_t = rxBytes[2];
  uint16_t rh_ticks = rxBytes[3] * 256 + rxBytes[4];
  uint8_t checksum_rh = rxBytes[5];

  temperature = -45.0 + 175.0 * double(t_ticks)/65536.0;
  humidity = -6.0 + 125.0 * double(rh_ticks)/65536.0;

  if (humidity > 100.0) {
    humidity = 100.0;
  }
  if (humidity < 0.0) {
    humidity = 0.0;
  }
}

void SHT4x::setPrecision(SHT4X_PRECISION prec) { _precision = prec; }

SHT4X_PRECISION SHT4x::getPrecision(void) { return _precision; }

void SHT4x::setHeater(SHT4X_HEATER heat) { _heater = heat; }

SHT4X_HEATER SHT4x::getHeater(void) { return _heater; }

bool SHT4x::writeCommand(uint16_t command) {
  uint8_t cmd[2];

  cmd[0] = command >> 8;
  cmd[1] = command & 0xFF;

  return wiringPiI2CRawWrite(_handle, cmd, 2);
}

bool SHT4x::readCommand(uint16_t command, uint8_t *buffer, uint8_t num_bytes) {
  uint8_t cmd[2];

  cmd[0] = command >> 8;
  cmd[1] = command & 0xFF;

  bool success = false;
  success = wiringPiI2CRawWrite(_handle, cmd, 2);
  success = wiringPiI2CRawRead(_handle, buffer, num_bytes);
  return success;
}

static uint8_t crc8(const uint8_t *data, int len) {
  const uint8_t POLYNOMIAL(0x31);
  uint8_t crc(0xFF);

  for (int j = len; j; --j) {
    crc ^= *data++;

    for (int i = 8; i; --i) {
      crc = (crc & 0x80) ? (crc << 1) ^ POLYNOMIAL : (crc << 1);
    }
  }
  return crc;
}

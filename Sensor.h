#pragma once

#include <stdint.h>

/* Constants */
#define SENSORS_GRAVITY_EARTH (9.80665F) /**< Earth's gravity in m/s^2 */
#define SENSORS_GRAVITY_MOON (1.6F)      /**< The moon's gravity in m/s^2 */
#define SENSORS_GRAVITY_SUN (275.0F)     /**< The sun's gravity in m/s^2 */
#define SENSORS_GRAVITY_STANDARD (SENSORS_GRAVITY_EARTH)
#define SENSORS_MAGFIELD_EARTH_MAX (60.0F) /**< Maximum magnetic field on Earth's surface */
#define SENSORS_MAGFIELD_EARTH_MIN (30.0F) /**< Minimum magnetic field on Earth's surface */
#define SENSORS_PRESSURE_SEALEVELHPA (1013.25F) /**< Average sea level pressure is 1013.25 hPa */
#define SENSORS_DPS_TO_RADS (0.017453293F) /**< Degrees/s to rad/s multiplier */
#define SENSORS_RADS_TO_DPS (57.29577793F) /**< Rad/s to degrees/s  multiplier */
#define SENSORS_GAUSS_TO_MICROTESLA (100) /**< Gauss to micro-Tesla multiplier */

/** Sensor types */
enum SENSOR_TYPE {
  ACCELEROMETER = (1), /**< Gravity + linear acceleration */
  MAGNETIC_FIELD = (2),
  ORIENTATION = (3),
  GYROSCOPE = (4),
  LIGHT = (5),
  PRESSURE = (6),
  PROXIMITY = (8),
  GRAVITY = (9),
  LINEAR_ACCELERATION = (10), /**< Acceleration not including gravity */
  ROTATION_VECTOR = (11),
  RELATIVE_HUMIDITY = (12),
  AMBIENT_TEMPERATURE = (13),
  OBJECT_TEMPERATURE = (14),
  VOLTAGE = (15),
  CURRENT = (16),
  COLOR = (17),
  TVOC = (18),
  VOC_INDEX = (19),
  NOX_INDEX = (20),
  CO2 = (21),
  ECO2 = (22),
  PM10_STD = (23),
  PM25_STD = (24),
  PM100_STD = (25),
  PM10_ENV = (26),
  PM25_ENV = (27),
  PM100_ENV = (28),
  GAS_RESISTANCE = (29),
  UNITLESS_PERCENT = (30),
  ALTITUDE = (31)
};


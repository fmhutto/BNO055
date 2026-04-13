#include <iostream>
#include <bits/this_thread_sleep.h>

#include "wiringPi.h"
#include "wiringPiI2C.h"
#include "BNO055.h"
#include "SHT4X.h"

#define BNO055_SAMPLERATE_DELAY_MS (100)

int main(int argc, char* argv[]) {

    if (wiringPiSetup() == -1)
    {
        std::cout <<"Initialisation error of the GPIO \n Closing program..."<< std::endl;
        return 1;
    }

    BNO055 bno(BNO055_ID, BNO055_ADDRESS_A);
    SHT4x sht4_x(SHT4x_DEFAULT_ADDR, SHT4x_HUMIDITY_ID, SHT4x_TEMPERATURE_ID );
    sht4_x.begin();

    float humidity;
    float temperature;
    for (int i=0;i<10;i++) {
        sht4_x.Read(humidity, temperature);
        std::cout << "Humidity (%RH): " << humidity << "    Temperature (degC): " << temperature << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    std::cout << "\n\n\nOrientation Sensor Raw Data Test" << std::endl;

    /* Initialise the sensor */
    if(!bno.begin())
    {
        /* There was a problem detecting the BNO055 ... check your connections */
        std::cout << "Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!" << std::endl;
        while(1);
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    /* Display the current temperature */
    int8_t temp = bno.getTemp();
    std::cout << "Current Temperature: "<< (int)temp << " C" << std::endl;

    bno.setExtCrystalUse(true);

    std::cout << "Calibration status values: 0=uncalibrated, 3=fully calibrated"<<std::endl;

    while (1)
    {
        // Possible vector values can be:
        // - VECTOR_ACCELEROMETER - m/s^2
        // - VECTOR_MAGNETOMETER  - uT
        // - VECTOR_GYROSCOPE     - rad/s
        // - VECTOR_EULER         - degrees
        // - VECTOR_LINEARACCEL   - m/s^2
        // - VECTOR_GRAVITY       - m/s^2
        imu::Vector<3> euler = bno.getVector(BNO055::VECTOR_EULER);

        /* Display the floating point data */
        std::cout << "X: " << euler.x() <<  " Y: " << euler.y() << " Z: "
          << euler.z() << "\t\t";


        // Quaternion data
        imu::Quaternion quat = bno.getQuat();
        std::cout << "qW: " << quat.w() << " qX: " << quat.y() << " qY: " << quat.x() << " qZ: " << quat.z() << "\t\t";


        /* Display calibration status for each sensor. */
        uint8_t system, gyro, accel, mag = 0;
        bno.getCalibration(&system, &gyro, &accel, &mag);
        std::cout<< "CALIBRATION: Sys=" << (int)system << " Gyro=" << (int) gyro
         << " Accel=" << (int) accel << " Mag=" << (int)mag << std::endl;

        std::this_thread::sleep_for(std::chrono::milliseconds(BNO055_SAMPLERATE_DELAY_MS));
    }
}
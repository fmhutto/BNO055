#include <iostream>
#include <bits/this_thread_sleep.h>

#include "wiringPi.h"
#include "wiringPiI2C.h"
#include "BNO055.h"

#define BNO055_SAMPLERATE_DELAY_MS (100)

int main(int argc, char* argv[]) {
    BNO055 bno;

    if (wiringPiSetup() == -1)
    {
        std::cout <<"Initialisation error of the GPIO \n Closing program..."<< std::endl;
        return 1;
    }

    int handle = wiringPiI2CSetup(BNO055_ADDRESS_A);
    bno.SetI2CHandle(handle);

    std::cout << "Orientation Sensor Raw Data Test" << std::endl;

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

        /*
        // Quaternion data
        imu::Quaternion quat = bno.getQuat();
        Serial.print("qW: ");
        Serial.print(quat.w(), 4);
        Serial.print(" qX: ");
        Serial.print(quat.y(), 4);
        Serial.print(" qY: ");
        Serial.print(quat.x(), 4);
        Serial.print(" qZ: ");
        Serial.print(quat.z(), 4);
        Serial.print("\t\t");
        */

        /* Display calibration status for each sensor. */
        uint8_t system, gyro, accel, mag = 0;
        bno.getCalibration(&system, &gyro, &accel, &mag);
        std::cout<< "CALIBRATION: Sys=" << (int)system << " Gyro=" << (int) gyro
         << " Accel=" << (int) accel << " Mag=" << (int)mag << std::endl;

        std::this_thread::sleep_for(std::chrono::milliseconds(BNO055_SAMPLERATE_DELAY_MS));
    }
}
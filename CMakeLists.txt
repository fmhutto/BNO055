cmake_minimum_required(VERSION 4.2)
project(BNO055)

set(CMAKE_CXX_STANDARD 20)

add_executable(BNO055
        main.cpp
        BNO055.cpp
        BNO055.h
        imumaths.h
        matrix.h
        quaternion.h
        vector.h
        Sensor.h
        SHT4X.cpp
        SHT4X.h)

target_link_libraries(BNO055 wiringPi)

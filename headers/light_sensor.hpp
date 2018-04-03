#ifndef _LIGHT_SENSOR_HPP
#define _LIGHT_SENSOR_HPP

#include "BrickPi3.h"
#include "light_sensor.hpp"
#include <iostream>

using namespace std;

BrickPi3 BP_light;

//struct to save the calibrateion
struct calibrate_light{
    int max;
    int min;
};

//setup a light sensor. defauld port is PORT_1
int set_light_sensor(const uint8_t & port = PORT_1);

//get light sensor data.
int read_light_sensor(sensor_light_t data, uint8_t port = PORT_1);

//check if the sensor sees black
bool light_detect_line(sensor_light_t data, uint8_t port = PORT_1);

//return value between 0 and 100. 100 is white, 0 is black
int light_get_reflection(sensor_light_t data, uint8_t port = PORT_1);

// reset min and max value of calibrate light
void light_calibrate(sensor_light_t data, uint8_t port = PORT_1);

#endif //_LIGHT_SENSOR_HPP

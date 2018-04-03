#ifndef _COLOR_SENSOR_HPP
#define _COLOR_SENSOR_HPP

#include "BrickPi3.h"
#include "color_sensor.hpp"
#include <iostream>

using namespace std;

BrickPi3 BP_color;

struct calibrate_color {
    int max;
    int min;
};

//setup a color sensor. defauld port is PORT_2
int set_color_sensor(const uint8_t & port = PORT_2);

//retrun value between 0 to 100. 0 is black, 100 is white.
int color_get_reflection(sensor_color_t data, uint8_t port = PORT_2);

//get the color sensor data
int read_color_sensor(sensor_color_t data, uint8_t port = PORT_2);

//check if the sensor sees black
bool color_detect_line(sensor_color_t data, uint8_t port = PORT_2);

// reset min and max value for calibrate color
void color_calibrate(sensor_color_t data, uint8_t port = PORT_2);

#endif //_COLOR_SENSOR_HPP

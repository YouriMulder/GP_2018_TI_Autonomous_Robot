#ifndef _LIGHT_SENSOR_HPP
#define _LIGHT_SENSOR_HPP

using namespace std;

#include <string>

// updates the calibration values struct from the calibration_save file
void light_read_and_set_calibration_save();

//struct to save the calibrateion
struct calibrate_light{
    int max;
    int min;
};

// setup light sensor. default port is PORT_1
int set_light_sensor();

// gets light sensor data.
int read_light_sensor();

// checks if the sensor sees black
bool light_detect_line();

// returns value between 0 and 100. 100 is white, 0 is black
int light_get_reflection();

// resets min and max value of calibrate light
void light_calibrate();

#endif //_LIGHT_SENSOR_HPP

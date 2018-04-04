#ifndef _LIGHT_SENSOR_HPP
#define _LIGHT_SENSOR_HPP

using namespace std;

#include <string>

//read calibration from calibration_save file and save data to calibration struct
void light_read_and_set_calibration_save();

//struct to save the calibrateion
struct calibrate_light{
    int max;
    int min;
};

//setup a light sensor. defauld port is PORT_1
int set_light_sensor();

//get light sensor data.
int read_light_sensor();

//check if the sensor sees black
bool light_detect_line();

//return value between 0 and 100. 100 is white, 0 is black
int light_get_reflection();

// reset min and max value of calibrate light
void light_calibrate();

#endif //_LIGHT_SENSOR_HPP

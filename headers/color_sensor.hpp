#ifndef _COLOR_SENSOR_HPP
#define _COLOR_SENSOR_HPP

#define PORT_2 0x02

using namespace std;

#include <string>

struct calibrate_color {
    int max;
    int min;
};

//check if substring is in string
bool find_sub_string(string str, string sub);

//remove substring from string
string remove_sub_str(string str, string sub);

//read calibration from calibration_save file and save data to calibration struct
void read_and_set_calibration_save();

//setup a color sensor. defauld port is PORT_2
int set_color_sensor();

//retrun value between 0 to 100. 0 is black, 100 is white.
int color_get_reflection();

//get the color sensor data
int read_color_sensor();

//check if the sensor sees black
bool color_detect_line();

// reset min and max value for calibrate color
void color_calibrate();

#endif //_COLOR_SENSOR_HPP

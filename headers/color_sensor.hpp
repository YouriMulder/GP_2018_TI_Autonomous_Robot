#ifndef _COLOR_SENSOR_HPP
#define _COLOR_SENSOR_HPP

#define PORT_2 0x02

using namespace std;

#include <string>

struct calibrate_color {
    int max;
    int min;
};

//read calibration from calibration_save file and save data to calibration struct
void color_read_and_set_calibration_save();

//setup a color sensor. defauld port is PORT_2
int set_color_sensor();

//retrun value between 0 to 100. 0 is black, 100 is white.
int color_get_reflection();

/*  get the color sensor data
    black = 1
    red = 5
    white = 6
*/
int read_color_sensor();

//check if the sensor sees black
bool color_detect_line();

bool is_color_red();

// reset min and max value for calibrate color
void color_calibrate();

#endif //_COLOR_SENSOR_HPP

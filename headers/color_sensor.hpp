#ifndef _COLOR_SENSOR_HPP
#define _COLOR_SENSOR_HPP

#define PORT_2 0x02

using namespace std;

struct calibrate_color {
    int max;
    int min;
};

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

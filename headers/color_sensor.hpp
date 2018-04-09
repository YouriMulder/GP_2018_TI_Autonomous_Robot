#ifndef _COLOR_SENSOR_HPP
#define _COLOR_SENSOR_HPP

#define PORT_2 0x02

struct calibrate_color {
    int max;
    int min;
};

// reads calibration from calibration_save file and save data to calibration struct
void color_read_and_set_calibration_save();

// setup color sensor. defauld port is PORT_2
int set_color_sensor();

// returns value between 0 to 100. 100 is black, 0 is white.
int color_get_reflection();

// gets the color sensor data
int read_color_sensor();

// checks if the sensor sees black
bool color_detect_line();

bool is_color_red();

// resets min and max value for calibrate color
void color_calibrate();

#endif /* _COLOR_SENSOR_HPP */

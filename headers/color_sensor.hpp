#ifndef _COLOR_SENSOR_HPP
#define _COLOR_SENSOR_HPP

#define PORT_2 0x02

using namespace std;

#include <string>

struct calibrate_color {
    int max;
    int min;
};

/**
 * @brief read calibration from calibration_save file and save data to calibration struct
 */
 void color_read_and_set_calibration_save();

/**
 * @brief setup a color sensor. defauld PORT_2 is PORT_2_2
 * @return int
 */
 int set_color_sensor();

/**
 * @brief calculate sensor data to a scale from 0 to 100.
 * @return int reflection -between 0 and 100
 */
 int color_get_reflection();

/**
 * @brief get the color sensor data
 * @return int dat.color -color sensor data
 */
int read_color_sensor();

/**
 * @brief check if the sensor sees black
 * @return bool -true if sensor sees black
 */
 bool color_detect_line();

/**
 * @brief check if color sensor sees red
 * @return bool -true if sensor sees red
 */
bool is_color_red();

/**
 * @brief reset min and max value for calibrate color
 */
 void color_calibrate();

#endif //_COLOR_SENSOR_HPP

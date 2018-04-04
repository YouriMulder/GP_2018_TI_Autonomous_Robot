#ifndef _COLOR_SENSOR_HPP
#define _COLOR_SENSOR_HPP

#define PORT_2 0x02

using namespace std;

struct calibrate_color {
    int max;
    int min;
};

/**
 * @brief setup a color sensor, default port is PORT_2
 * @return error code
 */
int set_color_sensor();

/**
 * @brief get reflected color value from sensor
 * @return return value between 0 to 100. 0 is black, 100 is white
 */
int color_get_reflection();

/**
 * @brief get the color sensor data
 * @return sensor data
 */
int read_color_sensor();

/**
 * @brief check if the sensor detects black
 * @return boolean true for black false for white e.g.
 */
bool color_detect_line();

/**
 * @brief reset min and max value for calibrate color
 */
void color_calibrate();

#endif //_COLOR_SENSOR_HPP

#ifndef _LIGHT_SENSOR_HPP
#define _LIGHT_SENSOR_HPP

using namespace std;

//struct to save the calibrateion
struct calibrate_light{
    int max;
    int min;
};

/**
 * @brief setup a light sensor. default port is PORT_1
 * @return error code
 */
int set_light_sensor();

/**
 * @brief get light sensor data
 * @return light sensor data
 */
int read_light_sensor();

/**
 * @brief check if the sensor detects black
 * @return boolean true for black false for white e.g.
 */
bool light_detect_line();

/**
 * @brief get light reflection value from sensor 
 * @return return value between 0 and 100. 0 is blask, 100 is white
 */
int light_get_reflection();

/**
 * @brief reset min and max value of calibrate light
 */

void light_calibrate();

#endif //_LIGHT_SENSOR_HPP

#ifndef _COLOR_SENSOR_HPP
#define _COLOR_SENSOR_HPP

/**
 * @brief setup a color sensor. default port is PORT_2.
 * @param port
 * @return 
 */
int set_color_sensor(const uint8_t & port = PORT_2);

/**
 * @brief get the color sensor data.
 * @param data
 * @param port
 * @return color data
 */
int read_color_sensor(sensor_color_t data, uint8_t port = PORT_2);

/** get color reflection from sensor.
 * @brief 
 * @param data
 * @param port
 * @return value between 0 to 100. 0 is black, 100 is white.
 */
int color_get_reflection(sensor_color_t data, uint8_t port = PORT_2);

//check if the sensor sees black
/**
 * @brief check if the sensor detects black surface.
 * @param data
 * @param port
 * @return boolean true for black false for white e.g.
 */
bool color_detect_line(sensor_color_t data, uint8_t port = PORT_2);
#endif //_COLOR_SENSOR_HPP

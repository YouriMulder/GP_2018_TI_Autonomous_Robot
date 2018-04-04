#ifndef _LIGHT_SENSOR_HPP
#define _LIGHT_SENSOR_HPP

//setup a light sensor. default port is PORT_1.
/**
 * @brief setup a light sensor. default port is PORT_1.
 * @param port
 * @return 
 */
int set_light_sensor(const uint8_t & port = PORT_2);

//get light sensor data.
/**
 * @brief get the light sensor data.
 * @param data
 * @param port
 * @return light data
 */
int read_light_sensor(sensor_light_t data, uint8_t port = PORT_2);

//check if the sensor sees black
/**
 * @brief check if the sensor detects black surface.
 * @param data
 * @param port
 * @return boolean true for black false for white e.g.
 */
bool light_detect_line(sensor_light_t data, uint8_t port = PORT_2);

#endif //_LIGHT_SENSOR_HPP

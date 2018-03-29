#ifndef _COLOR_SENSOR_HPP
#define _COLOR_SENSOR_HPP

//setup a color sensor. defauld port is PORT_2
int set_color_sensor(const uint8_t & port = PORT_2);

//get the color sensor data
int read_color_sensor(sensor_color_t data, uint8_t port = PORT_2);

//retrun value between 0 to 100. 0 is black, 100 is white.
int color_get_reflection(sensor_color_t data, uint8_t port = PORT_2);

//check if the sensor sees black
bool color_detect_line(sensor_color_t data, uint8_t port = PORT_2);
#endif //_COLOR_SENSOR_HPP

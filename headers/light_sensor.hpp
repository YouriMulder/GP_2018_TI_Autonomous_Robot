#ifndef _LIGHT_SENSOR_HPP
#define _LIGHT_SENSOR_HPP

//setup a light sensor. defauld port is PORT_1
int set_light_sensor(const uint8_t & port = PORT_2);

//get light sensor data.
int read_light_sensor(sensor_light_t data, uint8_t port = PORT_2);

//check if the sensor sees black
bool light_detect_line(sensor_light_t data, uint8_t port = PORT_2);

#endif //_LIGHT_SENSOR_HPP

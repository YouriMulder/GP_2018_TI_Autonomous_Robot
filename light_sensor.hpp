#ifndef _LIGHT_SENSOR_HPP
#define _LIGHT_SENSOR_HPP

int set_light_sensor(const uint8_t & port = PORT_2);

int read_light_sensor(sensor_light_t data, uint8_t port = PORT_2);

bool detect_line(sensor_light_t data, uint8_t port = PORT_2);

#endif //_LIGHT_SENSOR_HPP

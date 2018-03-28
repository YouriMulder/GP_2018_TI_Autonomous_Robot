#include "BrickPi3.h"
#include "light_sensor.hpp"

using namespace std;

BrickPi3 BP;

int set_light_sensor(const uint8_t & port = PORT_2){
    return BP.set_sensor_type(port, SENSOR_TYPE_NXT_LIGHT_ON);
}

int read_light_sensor(sensor_light_t data, uint8_t port = PORT_2){
    BP.get_sensor(port, data);
    return data.reflected;
}

bool detect_line(sensor_light_t data, uint8_t port = PORT_2){
    int result = read_light_sensor(data, port);
    if(result > 2100){
        return true;
    }
    return false;
}
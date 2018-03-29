#include "BrickPi3.h"
#include "light_sensor.hpp"

using namespace std;

BrickPi3 BP_light;

//setup a light sensor. defauld port is PORT_1
int set_light_sensor(const uint8_t & port = PORT_1){
    return BP_light.set_sensor_type(port, SENSOR_TYPE_NXT_LIGHT_ON);
}

//get light sensor data.
int read_light_sensor(sensor_light_t data, uint8_t port = PORT_1){
    BP_light.get_sensor(port, data);
    return data.reflected;
}

//check if the sensor sees black
bool light_detect_line(sensor_light_t data, uint8_t port = PORT_1){
    int result = read_light_sensor(data, port);
    if(result > 2100){
        return true;
    }
    return false;
}
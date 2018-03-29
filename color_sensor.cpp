#include "BrickPi3.h"
#include "color_sensor.hpp"

using namespace std;

BrickPi3 BP_color;

//setup a color sensor. defauld port is PORT_2
int set_color_sensor(const uint8_t & port = PORT_2){
    return BP_color.set_sensor_type(port, SENSOR_TYPE_NXT_COLOR_FULL);
}

//get the color sensor data
int read_color_sensor(sensor_color_t data, uint8_t port = PORT_2){
    BP_color.get_sensor(port, data);
    return data.color;
}

//check if the sensor sees black
bool color_detect_line(sensor_color_t data, uint8_t port = PORT_2){
    int result = read_color_sensor(data, port);
    if(result == 1){
        return true;
    }
    return false;
}
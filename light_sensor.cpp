#include "BrickPi3/BrickPi3.h"
#include "headers/light_sensor.hpp"
#include <iostream>
#include <unistd.h>
using namespace std;

//define BrickPi3 library
BrickPi3 BP_light;

//define light_data
sensor_light_t light_data;

//define default port for light sensor
uint8_t default_light_port = PORT_1;

//define calibration for light sensor
calibrate_light light = {1480, 2430};

//setup a light sensor
int set_light_sensor(uint8_t port = default_light_port){
    return BP_light.set_sensor_type(port, SENSOR_TYPE_NXT_LIGHT_ON);
}

//get light sensor light_data.
int read_light_sensor(uint8_t port = default_light_port){
    BP_light.get_sensor(port, light_data);
    return light_data.reflected;
}

//check if the sensor sees black
bool light_detect_line(uint8_t port = default_light_port){
    int result = read_light_sensor(port);
    if(result > 2100){
        return true;
    }
    return false;
}

//return value between 0 and 100. 100 is white, 0 is black
int light_get_reflection(uint8_t port = default_light_port){
    BP_light.get_sensor(port, light_data);
    float reflection = light_data.reflected;
    reflection = (reflection - light.min)/(light.max - light.min) * 100;
    if(reflection < 0){
        reflection = 0;
    }
    if(reflection > 100){
        reflection = 100;
    }
    return 100-reflection;
}

// reset min and max value of calibrate light
void light_calibrate(uint8_t port = default_light_port){
    float max = 0;
    float min = 0;
    char temp;
    cout << "put sensor on white\n";
    cin >> temp;
    for (int i = 0; i < 10; ++i) {
        BP_light.get_sensor(port, light_data);
        if(light_data.reflected < min || min == 0){
            min = light_data.reflected;
        }
        usleep(100000);
    }
    cout << "put sensor on black\n";
    cin >> temp;
    for (int j = 0; j < 10; ++j) {
        BP_light.get_sensor(port, light_data);
        if(light_data.reflected > max || max == 0){
            max = light_data.reflected;
        }
        usleep(100000);
    }
    light.max = max;
    light.min = min;
}

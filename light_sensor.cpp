#include "BrickPi3/BrickPi3.h"
#include "headers/light_sensor.hpp"

using namespace std;

BrickPi3 BP_light;

calibrate light = {1480, 2430};

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

//return value between 0 and 100. 100 is white, 0 is black
int light_get_reflection(sensor_light_t data, uint8_t port = PORT_1){
    BP_lightget_sensor(port, data);
    float reflection = data.reflected;
    cout << "test1: " << reflection << "\n";
    reflection = (reflection - light.min)/(light.max - color.min) * 100;
    if(reflection < 0){
        reflection = 0;
    }
    if(reflection > 100){
        reflection = 100;
    }
    return 100-reflection;
}

// reset min and max value of calibrate light
void light_calibrate(sensor_light_t data, uint8_t port = PORT_1){
    float max = 0;
    float min = 0;
    float reflection = 0;
    char temp;
    cout << "put sensor on white\n";
    cin >> temp;
    for (int i = 0; i < 10; ++i) {
        BP_lightget_sensor(port, data);
        if(data.reflected < min || min == 0){
            min = data.reflected;
        }
        usleep(100000);
    }
    cout << "put sensor on black\n";
    cin >> temp;
    for (int j = 0; j < 10; ++j) {
        BP_lightget_sensor(port, data);
        if(data.reflected > max || max == 0){
            max = data.reflected;
        }
        usleep(100000);
    }
    light.max = max;
    light.min = min;
}
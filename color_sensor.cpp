#include "BrickPi3/BrickPi3.h"
#include "headers/color_sensor.hpp"
#include <unistd.h>
#include <iostream>
using namespace std;

BrickPi3 BP_color;

sensor_color_t data;

calibrate_color color = {430, 770};

//setup a color sensor. defauld PORT_2 is PORT_2_2
int set_color_sensor(){
    return BP_color.set_sensor_type(PORT_2, SENSOR_TYPE_NXT_COLOR_FULL);
}

//retrun value between 0 to 100. 0 is black, 100 is white.
int color_get_reflection(){
    BP_color.get_sensor(PORT_2, data);
    float reflection = data.reflected_green;
    cout << "test1: " << reflection << "\n";
    reflection += data.reflected_red;
    reflection += data.reflected_blue;

    reflection = ((reflection / 3) - color.min)/(color.max - color.min) * 100;
    if (reflection < 0){
        return 0;
    }
    return (int) reflection;
}

//get the color sensor data
int read_color_sensor(){
    BP_color.get_sensor(PORT_2, data);
    return data.color;
}

//check if the sensor sees black
bool color_detect_line(){
    int result = read_color_sensor();
    if(result == 1){
        return true;
    }
    return false;
}

// reset min and max value for calibrate color
void color_calibrate(){
    float max = 0;
    float min = 0;
    char temp;
    cout << "put sensor on white\n";
    cin >> temp;
    for (int i = 0; i < 10; ++i) {
        BP_color.get_sensor(PORT_2, data);
        float reflected = data.reflected_green;
        reflected += data.reflected_red;
        reflected += data.reflected_blue;
        reflected /= 3;
        if(reflected < min || min == 0){
            min = reflected;
        }
        usleep(100000);
    }
    cout << "put sensor on black\n";

    cin >> temp;
    for (int j = 0; j < 10; ++j) {
        BP_color.get_sensor(PORT_2, data);
        float reflected = data.reflected_green;
        reflected += data.reflected_red;
        reflected += data.reflected_blue;
        reflected /= 3;
        if(reflected > max || max == 0){
            max = reflected;
        }
        usleep(100000);
    }
    cout << "min= " << min << "\nmax= " << max << "\n";
    color.max = max;
    color.min = min;
}
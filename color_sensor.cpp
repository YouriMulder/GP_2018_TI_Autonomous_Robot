#include "BrickPi3/BrickPi3.h"
#include "headers/color_sensor.hpp"

using namespace std;

BrickPi3 BP_color;

struct calibrate{
    int max;
    int min;
};
calibrate color = {430, 770};

//setup a color sensor. defauld port is PORT_2
int set_color_sensor(const uint8_t & port = PORT_2){
    return BP_color.set_sensor_type(port, SENSOR_TYPE_NXT_COLOR_FULL);
}

//retrun value between 0 to 100. 0 is black, 100 is white.
int color_get_reflection(sensor_color_t data, uint8_t port = PORT_2){
    BP_color.get_sensor(port, data);
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

// reset min and max value for calibrate color
void color_calibrate(sensor_color_t data, uint8_t port = PORT_2){
    float max = 0;
    float min = 0;
    float reflection = 0;
    char temp;
    cout << "put sensor on white\n";
    cin >> temp;
    for (int i = 0; i < 10; ++i) {
        BP_lightget_sensor(port, data);
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
        BP_lightget_sensor(port, data);
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
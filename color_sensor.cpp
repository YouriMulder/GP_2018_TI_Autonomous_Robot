#include "BrickPi3/BrickPi3.h"
#include "headers/color_sensor.hpp"
#include "headers/general_functions.hpp"
#include <unistd.h>
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

//brick pi 3 library
BrickPi3 BP_color;

//variable to store color data in
sensor_color_t data;

//default calibration values
calibrate_color color = {447, 661};


/**
 * @brief read calibration from calibration_save file and save data to calibration struct
 */
void color_read_and_set_calibration_save(){
    try {
        ifstream readFile("calibration_save");
        int max_color = 0;
        int min_color = 0;
        string line;
        if (readFile.is_open()) {
            while (getline(readFile, line)) {
                if (find_sub_string(line, "max_color:")) {
                    line = remove_sub_str(line, "max_color:");
                    max_color = atoi(remove_sub_str(line, "\n:").c_str());
                }
                if (find_sub_string(line, "min_color:")) {
                    line = remove_sub_str(line, "min_color:");
                    min_color = atoi(remove_sub_str(line, "\n:").c_str());
                }
            }
            readFile.close();
            cout << max_color << "\n" << min_color << "\n";
            color = {min_color, max_color};
        } else {
            cout << "can't read calibration_save\n";
        }
    } catch (int e) {
        cout << "something went wrong, does calibration_save file exist";
    }
}
/**
 * @brief setup a color sensor. defauld PORT_2 is PORT_2_2
 * @return int
 */
int set_color_sensor(){
    return BP_color.set_sensor_type(PORT_2, SENSOR_TYPE_NXT_COLOR_FULL);
}

/**
 * @brief calculate sensor data to a scale from 0 to 100.
 * @return int reflection -between 0 and 100
 */
int color_get_reflection(){
    BP_color.get_sensor(PORT_2, data);
    float reflection = data.reflected_green;
    reflection += data.reflected_red;
    reflection += data.reflected_blue;
    reflection = (((reflection / 3) - color.min)/(color.max - color.min)) * 100;
    if (reflection < 0){
        return 0;
    }
	if(reflection > 100){
      reflection = 100;
    }
    return (int) reflection;
}

/**
 * @brief get the color sensor data
 * @return int dat.color -color sensor data
 */
int read_color_sensor(){
    BP_color.get_sensor(PORT_2, data);
    return data.color;
}

/**
 * @brief check if the sensor sees black
 * @return bool -true if sensor sees black
 */
bool color_detect_line(){
    int result = read_color_sensor();
    if(result == 1){
        return true;
    }
    return false;
}

/**
 * @brief check if color sensor sees red
 * @return bool -true if sensor sees red
 */
bool is_color_red() {
  return read_color_sensor() == 5;
}

/**
 * @brief reset min and max value for calibrate color
 */
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

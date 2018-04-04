#include "BrickPi3/BrickPi3.h"
#include "headers/light_sensor.hpp"
#include "headers/general_functions.hpp"
#include <iostream>
#include <unistd.h>
#include <fstream>
#include <string>
using namespace std;

BrickPi3 BP_light;

sensor_light_t light_data;

calibrate_light light = {1877, 2609};

//read calibration from calibration_save file and save data to calibration struct
void light_read_and_set_calibration_save(){
    ifstream readFile ("calibration_save");
    int max_light = 0;
    int min_light = 0;
    string line;
    if (readFile.is_open()){
        while (getline(readFile, line)) {
            if(find_sub_string(line, "max_light:")){
                line = remove_sub_str(line, "max_light:");
                max_light = atoi(remove_sub_str(line, "\n:").c_str());
            }
            if(find_sub_string(line, "min_light:")){
                line = remove_sub_str(line, "min_light:");
                min_light = atoi(remove_sub_str(line, "\n:").c_str());
            }
        }
        readFile.close();
        cout << max_light << "\n" << min_light << "\n";
        light = {min_light, max_light};
    }else{
        cout << "can't read calibration_save\n";
    }
}

//setup a light sensor. defauld PORT_1 is PORT_1
int set_light_sensor(){
    return BP_light.set_sensor_type(PORT_1, SENSOR_TYPE_NXT_LIGHT_ON);
}

//get light sensor light_data.
int read_light_sensor(){
    BP_light.get_sensor(PORT_1, light_data);
    return light_data.reflected;
}

//check if the sensor sees black
bool light_detect_line(){
    int result = read_light_sensor();
    if(result > 2100){
        return true;
    }
    return false;
}

//return value between 0 and 100. 100 is white, 0 is black
int light_get_reflection(){
    BP_light.get_sensor(PORT_1, light_data);
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
void light_calibrate(){
    float max = 0;
    float min = 0;
    char temp;
    cout << "put sensor on white\n";
    cin >> temp;
    for (int i = 0; i < 10; ++i) {
        BP_light.get_sensor(PORT_1, light_data);
        if(light_data.reflected < min || min == 0){
            min = light_data.reflected;
        }
        usleep(100000);
    }
    cout << "put sensor on black\n";
    cin >> temp;
    for (int j = 0; j < 10; ++j) {
        BP_light.get_sensor(PORT_1, light_data);
        if(light_data.reflected > max || max == 0){
            max = light_data.reflected;
        }
        usleep(100000);
    }
	cout << "light max =" << max << endl;
	cout << "light min =" << min << endl;
    light.max = max;
    light.min = min;
}

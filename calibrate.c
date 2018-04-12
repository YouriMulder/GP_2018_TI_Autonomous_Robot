#include "headers/calibrate.hpp"
#include "headers/light_sensor.hpp"
#include "headers/color_sensor.hpp"
#include "headers/driving_motors.hpp"
#include "BrickPi3/BrickPi3.h"
#include <unistd.h>
#include <fstream>
#include <iostream>
using namespace std;

BrickPi3 BP_calibrate;

sensor_color_t calibrate_color_data;

sensor_light_t calibrate_light_data;

/**
  saves the new calibration to file
  @return bool whether the data is written to the file or not
 */
bool save_calibration(int max_color, int min_color, int max_light, int min_light){
    ofstream writeFile;
    writeFile.open("calibration_save", ofstream::out);
    if(writeFile.is_open()){
        writeFile << "max_color:"<< max_color<<"\n";
        writeFile << "min_color:"<< min_color<<"\n";
        writeFile << "max_light:"<< max_light<<"\n";
        writeFile << "min_light:"<< min_light<<"\n";
        writeFile.close();
    } else {
        cout << "can't open calibration_save\n";
        return false;
    }
    return true;
}

// calibrates the sensors and saves it using save_calibration
void calibrate_line_sensors(){
    BP_calibrate.set_sensor_type(PORT_1, SENSOR_TYPE_NXT_LIGHT_ON);
    BP_calibrate.set_sensor_type(PORT_2, SENSOR_TYPE_NXT_COLOR_FULL);
    float max_light = 0;
    float min_light = 0;
    float max_color = 0;
    float min_color = 0;
    char choice;
    cout << "put sensors on black. with motor y/n?\n";
    cin >> choice;
    //sensors on black
    for (int i = 0; i < 10; ++i) {

        BP_calibrate.get_sensor(PORT_2, calibrate_color_data);
        float reflected = calibrate_color_data.reflected_green;
        reflected += calibrate_color_data.reflected_red;
        reflected += calibrate_color_data.reflected_blue;
        reflected /= 3;
        if(reflected < min_color || min_color == 0){
            min_color = reflected;
        }

        BP_calibrate.get_sensor(PORT_1, calibrate_light_data);
        if(calibrate_light_data.reflected < min_light || min_light == 0){
            min_light = calibrate_light_data.reflected;
        }

        usleep(100000);
    }
    //sensors on white
    if(choice == 'y'){
        straight(5, 'f');
        usleep(300000);
        stop();
    } else {
        cout << "put sensors on white";
        cin >> choice;
    }

    for (int j = 0; j < 10; ++j) {

        BP_calibrate.get_sensor(PORT_2, calibrate_color_data);
        float reflected = calibrate_color_data.reflected_green;
        reflected += calibrate_color_data.reflected_red;
        reflected += calibrate_color_data.reflected_blue;
        reflected /= 3;
        if(reflected > max_color || max_color == 0){
            max_color = reflected;
        }

        BP_calibrate.get_sensor(PORT_1, calibrate_light_data);
        if(calibrate_light_data.reflected > max_light || max_light == 0){
            max_light = calibrate_light_data.reflected;
        }

        usleep(100000);
    }
    if(save_calibration((int) max_color, (int) min_color, (int) max_light, (int) min_light)){
        cout << "calibration successful\n";
    } else {
        cout << "calibration failed";
    }
}

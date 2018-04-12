#include "headers/light_sensor.hpp"
#include "BrickPi3/BrickPi3.h"
#include "headers/general_functions.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <unistd.h>
using namespace std;

BrickPi3 BP_light;

sensor_light_t light_data;

calibrate_light light = {1877, 2609};

// updates the calibration values struct from the calibration_save file
void light_read_and_set_calibration_save() {
  try {
    ifstream readFile("calibration_save");
    int max_light = 0;
    int min_light = 0;
    string line;
    if (readFile.is_open()) {
      while (getline(readFile, line)) {
        if (find_sub_string(line, "max_light:")) {
          line = remove_sub_str(line, "max_light:");
          max_light = atoi(remove_sub_str(line, "\n:").c_str());
        }
        if (find_sub_string(line, "min_light:")) {
          line = remove_sub_str(line, "min_light:");
          min_light = atoi(remove_sub_str(line, "\n:").c_str());
        }
      }
      readFile.close();
      cout << max_light << "\n" << min_light << "\n";
      light = {min_light, max_light};
    } else {
      cout << "can't read calibration_save\n";
    }
  } catch (int e) {
    cout << "something went wrong, does calibration_save file exist";
  }
}

/**
  setup a light sensor. default PORT_1 is PORT_1
  @return int error code from set_sensor_type in BrickPi3 library
 */
int set_light_sensor() {
  return BP_light.set_sensor_type(PORT_1, SENSOR_TYPE_NXT_LIGHT_ON);
}

/**
  gets light sensor light_data reflection value
  @returns int light_sensor reflection value
 */
int read_light_sensor() {
  BP_light.get_sensor(PORT_1, light_data);
  return light_data.reflected;
}

/**
  check if the sensor sees black
  @return bool
 */
bool light_detect_line() {
  int result = read_light_sensor();
  cout << read_light_sensor() << " " << light.min << endl;
  if (result > 2000) {
    return true;
  }
  return false;
}

// return value between 0 and 100. 100 is white, 0 is black
int light_get_reflection() {
  BP_light.get_sensor(PORT_1, light_data);
  float reflection = light_data.reflected;

  reflection = (reflection - light.min) / (light.max - light.min) * 100;
  if (reflection < 0) {
    reflection = 0;
  }
  if (reflection > 100) {
    reflection = 100;
  }
  return 100 - reflection;
}

// resets min and max value of calibrate light
void light_calibrate() {
  float max = 0;
  float min = 0;
  char temp;
  cout << "put sensor on white\n";
  cin >> temp;
  for (int i = 0; i < 10; ++i) {
    BP_light.get_sensor(PORT_1, light_data);
    if (light_data.reflected < min || min == 0) {
      min = light_data.reflected;
    }
    usleep(100000);
  }
  cout << "put sensor on black\n";
  cin >> temp;
  for (int j = 0; j < 10; ++j) {
    BP_light.get_sensor(PORT_1, light_data);
    if (light_data.reflected > max || max == 0) {
      max = light_data.reflected;
    }
    usleep(100000);
  }
  cout << "light max =" << max << endl;
  cout << "light min =" << min << endl;
  light.max = max;
  light.min = min;
}

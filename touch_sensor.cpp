#include "headers/touch_sensor.hpp"
#include "BrickPi3/BrickPi3.h"
#include <iostream>
#include <stdio.h>
using namespace std;

BrickPi3 BP_touch;

sensor_touch_t sensor_touch;

// intitalizes touch sensor
void init_touch() {
  BP_touch.detect();
  BP_touch.set_sensor_type(PORT_3, SENSOR_TYPE_TOUCH);
}

/**
        gets the touch sensor touch sensor data
        @return int whether the button is pressed or not
 */
int get_touch_data() {
  BP_touch.get_sensor(PORT_3, sensor_touch);
  return sensor_touch.pressed;
}

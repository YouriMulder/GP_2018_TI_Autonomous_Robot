#include <stdio.h>
#include "BrickPi3/BrickPi3.h"
#include <iostream>
#include "headers/touch_sensor.hpp"
using namespace std;

BrickPi3 BP_touch;

sensor_touch_t sensor_touch;

void init_touch() {
	BP_touch.detect();
	BP_touch.set_sensor_type(PORT_3, SENSOR_TYPE_TOUCH);
}

int return_data() {
	BP_touch.get_sensor(PORT_3, sensor_touch);
	return sensor_touch.pressed;
}

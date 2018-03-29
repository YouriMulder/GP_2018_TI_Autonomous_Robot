#include <stdio.h>
#include "BrickPi3.h"
#include <iostream>
#include "touch.hpp"
using namespace std;

BrickPi3 BP;

void init_touch(){
	sensor_touch_t sensor_touch;
	BP.detect();
	BP.set_sensor_type(PORT_3, SENSOR_TYPE_TOUCH);
}

int return_data(){
	BP.get_sensor(PORT_3, sensor_touch);
	return sensor_touch.pressed;
}
#include "driving_motors.hpp"
BrickPi3 BP;

uint8_t L = PORT_A;
uint8_t R = PORT_B;

void straight(int speed, char f_b){
	if (f_b == 'f') {
		BP.set_motor_power(L,speed);
		BP.set_motor_power(R,speed);
	}
	else if (f_b == 'r'){
		BP.set_motor_power(L,speed -127);
		BP.set_motor_power(R,speed -127);
	}
}

void stop(){
	BP.set_motor_power(L,0);
	BP.set_motor_power(R,0);
}

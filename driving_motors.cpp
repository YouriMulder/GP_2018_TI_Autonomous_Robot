#include "driving_motors.hpp"
#include "BrickPi3.h"
#include <iostream>
using namespace std;


BrickPi3 BP_wheels;

uint8_t L = PORT_A;
uint8_t R = PORT_B;

void initialize(){
	BP_wheels.detect();
}

void straight (float speed, char f_r) {
	speed = speed/5;
	speed = speed *32.767;
	if (f_r == 'f') {
		BP_wheels.set_motor_dps(L,speed);
		BP_wheels.set_motor_dps(R,speed);
	}
	else if (f_r == 'r'){
		BP_wheels.set_motor_dps(L,speed*-1);
		BP_wheels.set_motor_dps(R,speed*-1);
	}
}

void stop () {
	BP_wheels.set_motor_power(L,0);
	BP_wheels.set_motor_power(R,0);
}

void free () {
	BP_wheels.set_motor_power(L,-128);
	BP_wheels.set_motor_power(R,-128);
}

void turn (float speed, char f_r, float corner){
	float left_motor;
	float right_motor;
	corner = 10*corner /100;
	speed = speed /5;

	if (f_r == 'f'){
		speed = speed *32.767;
		if (corner>0){
			left_motor = speed + (speed * corner);
			right_motor = speed;
		}

		if (corner<0){
			corner = corner *-1;
			right_motor = speed + (speed * corner);
			left_motor = speed;
		}
	}
	else if (f_r == 'r'){
		speed = speed*-1;
		speed = speed * 32.767;
		if (corner>0){
			left_motor = speed + (speed * corner);
			right_motor = speed;
		}

		if (corner<0){
			corner = corner *-1;
			right_motor = speed + (speed * corner);
			left_motor = speed;
		}
	}

	BP_wheels.set_motor_dps(L,left_motor);
	BP_wheels.set_motor_dps(R,right_motor);
}

void reset_motors(){
	free();
}

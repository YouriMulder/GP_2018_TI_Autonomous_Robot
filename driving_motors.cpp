#include "headers/driving_motors.hpp"
#include "BrickPi3/BrickPi3.h"
#include <iostream>
using namespace std;

uint8_t L = PORT_A;
uint8_t R = PORT_B;

BrickPi3 BP_wheels;

// initializes the motors
void init_motors(){
	BP_wheels.detect();
}

/**
 * starts driving the robot straight forward or backward
 * @param speed a float that controls the speed of the motors 0-100
 * @param f_r is a char that defines the direction of the motors 'f' means forward, 'r' means reverse
 */
void straight (float speed, char f_r) {
	speed = speed * 32.767 / 5 ;
	if (f_r == 'f') {
		BP_wheels.set_motor_dps(L,speed - 0.01525 * speed);
		BP_wheels.set_motor_dps(R,speed);
	}
	else if(f_r == 'r'){
		BP_wheels.set_motor_dps(L,speed*-1 - 0.01525 * speed);
		BP_wheels.set_motor_dps(R,speed*-1);
	}
}

// stops both motors
void stop () {
	BP_wheels.set_motor_power(L,0);
	BP_wheels.set_motor_power(R,0);
}

// sets both motors in the free rotating position
void free () {
	BP_wheels.set_motor_power(L,-128);
	BP_wheels.set_motor_power(R,-128);
}

/**
 * drives robot forward or backward using a given angle
 * @param speed controls the speed of the motors 0-100
 * @param f_r the direction of the motors 'f' means forward, 'r' means reverse
 * @param corner the angle the robot is turning
 */
void turn(float speed, char f_r, float corner){
	float left_motor;
	float right_motor;
	BP_wheels.set_motor_limits(L,80,1200);
	BP_wheels.set_motor_limits(R,80,1200);
	speed = speed * 32.767/5;
	corner = corner /18;
	if (f_r == 'r'){
				speed = speed*-1;
	}

	if (corner>0){
		left_motor = speed + 0.3*(speed * corner);
		right_motor = speed - 0.5*(speed * corner);
	} else if (corner<0){
		corner = corner *-1;
		right_motor = speed + 0.3*(speed * corner);
		left_motor = speed -0.5*(speed * corner);
	} else {
		left_motor = speed;
		right_motor = speed;
	}

	BP_wheels.set_motor_dps(L,left_motor);
	BP_wheels.set_motor_dps(R,right_motor+3);
}

// calls free()
void reset_motors(){
	free();
}

/**
 * turns robot on it's place
 * @param f_r a char that defines the direction of the motors 'f' means forward, 'r' means reverse
 * @param corner defines the angle how far the robot will turn higher means more
 */
void turn_on_place(char f_r,float corner){
	 BP_wheels.set_motor_limits(L,35,1200);
	 BP_wheels.set_motor_limits(R,35,1200);
	if (f_r == 'f'){
		BP_wheels.set_motor_position_relative(L,corner*2.35);
		BP_wheels.set_motor_position_relative(R,corner*2.35*-1);
	}
	if (f_r == 'r'){
		BP_wheels.set_motor_position_relative(R,corner*2.35);
		BP_wheels.set_motor_position_relative(L,corner*2.35*-1);
	}
}

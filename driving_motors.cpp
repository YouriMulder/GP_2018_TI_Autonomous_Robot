#include "driving_motors.hpp"
#include "BrickPi3.h"
BrickPi3 BP_wheels;
#include <iostream>
using namespace std;

uint8_t L = PORT_A;
uint8_t R = PORT_B;

void initialize(){
	/**
	 * purpose: initializing the robots itself so the brickpi is comunicating with the code
	 */
	BP_wheels.detect();
}

void straight (float speed, char f_r) {
	/**
	 * sending the robot straight forward or backwards
	 * 
	 * @param speed an float value that controls the speed of the motors higher means faster
	 * @param f_r is a char that defines the direction of the motors 'f' means forward, 'r' means revers
	 * */
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
	/**
	 * stopping both motors
	 */
	BP_wheels.set_motor_power(L,0);
	BP_wheels.set_motor_power(R,0);
}

void free () {
	/**
	 * setting both motors in the free rotating position
	 */
	BP_wheels.set_motor_power(L,-128);
	BP_wheels.set_motor_power(R,-128);
}

void turn (float speed, char f_r, float corner){
	/**
	 *turning the robot in different ways 
	 * @param speed defines the speed the robot moves with
	 * @param f_r defines the direction of the robot 'f' means forward 'r' means backwards(reverse)
	 * @param corner defines how much the robot needs to corner a higher value means a more tight corner and a lower value means a shallow corner
	**/	
	float left_motor;
	float right_motor;
	speed = speed/5;
	speed = speed * 32.767;
	corner = 10*corner /180;
	if (f_r == 'f'){
		if (corner == 0){
			left_motor = speed;
			right_motor = speed;
		}
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
		if (corner == 0){
			left_motor = speed;
			right_motor = speed;
		}
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

void turn_on_place(char f_r,float corner){
	/**
	 * @param f_r defines the direction of the robot 'f' means forward 'r' means backwards(reverse)
	 * @param corner defines the angle how far the robot will turn higher means more
	 * */
	 BP_wheels.set_motor_limits(L,35,1200);
	 BP_wheels.set_motor_limits(R,35,1200);
	if (f_r == 'f'){
		BP_wheels.set_motor_position_relative(L,corner*3.5);
		BP_wheels.set_motor_position_relative(R,corner*3.5*-1);
	}
	if (f_r == 'r'){
		BP_wheels.set_motor_position_relative(R,corner*3.5);
		BP_wheels.set_motor_position_relative(L,corner*3.5*-1);
	}
}
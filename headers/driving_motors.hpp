#ifndef _DRIVING_MOTORS_HPP
#define _DRIVING_MOTORS_HPP

// initializes the motors
void init_motors();

// starts driving the robot straight forward or backward
void straight (float speed, char f_r);

// drives robot forward or backward using a given angle
void turn (float speed, char f_r, float corner);

// stops both motors
void stop ();

// sets both motors in the free rotating position
void free ();

// calls free()
void reset_motors();

// turns robot on it's place
void turn_on_place(char f_r,float corner);

#endif /* _DRIVING_MOTORS_HPP*/

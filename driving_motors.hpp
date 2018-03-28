#ifndef _DRIVING_MOTORS_HPP
#define _DRIVING_MOTORS_HPP

void initialize ();

void straight (float speed, char f_r);

void turn (float speed, char f_r, float corner);

void stop ();

void free ();

void reset_motors();

#endif /* _DRIVING_MOTORS_HPP */

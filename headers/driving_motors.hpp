#ifndef _DRIVING_MOTORS_HPP
#define _DRIVING_MOTORS_HPP

void init_motors();

void straight (float speed, char f_r);

void turn (float speed, char f_r, float corner);

void stop ();

void free ();

void reset_motors();

void turn_on_place (char f_r,float corner);

#endif /* _DRIVING_MOTORS_H{{}}*/

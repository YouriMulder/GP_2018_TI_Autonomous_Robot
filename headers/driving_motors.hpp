#ifndef _DRIVING_MOTORS_HPP
#define _DRIVING_MOTORS_HPP

/**
 * @brief initializing the robot and brickpi to enable communication with the parts and code
 */
void init_motors();

/**
 * @brief sending the robot straight forward or backward
 * @param speed a float that controls the speed of the motors 0-100
 * @param f_r is a char that defines the direction of the motors 'f' means forward, 'r' means reverse
 */
void straight (float speed, char f_r);

/**
 * @brief turning the robot in different ways
 * @param speed a float that controls the speed of the motors 0-100
 * @param f_r a char that defines the direction of the motors 'f' means forward, 'r' means reverse
 * @param corner defines how much the robot needs to corner a higher value means a more tight corner and a lower value means a shallow corner
 */
void turn (float speed, char f_r, float corner);

/**
 * @brief stopping both motors
 */
void stop ();

/**
 * @brief setting both motors in the free rotating position
 */
void free ();

/**
 * @brief call free()
 */
void reset_motors();

/**
 * @brief make the robot turn on its place
 * @param f_r a char that defines the direction of the motors 'f' means forward, 'r' means reverse
 * @param corner defines the angle how far the robot will turn higher means more
 */
void turn_on_place (char f_r,float corner);

#endif /* _DRIVING_MOTORS_H{{}}*/

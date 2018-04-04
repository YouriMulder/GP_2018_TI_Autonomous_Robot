#ifndef DRIVING_MOTORS_HPP
#define DRIVING_MOTORS_HPP


<<<<<<< HEAD:headers/driving_motors.hpp
/**
 * @brief initialize the robot, enable communication with the brickpi and code.
 */
void init_motors();
=======
/**
 * @brief initialize the robot, enable communication with the brickpi and code.
 */
void initialize_motors ();
>>>>>>> master:driving_motors.hpp

/**
 * @brief sending the robot straight forward or backwards.
 * @param speed a float value that controls the speed of the motors higher means faster.
 * @param f_r is a char that defines the direction of the motors 'f' means forward, 'r' means reverse.
 */
void straight (float speed, char f_r);

/**
 * @brief turn the robot in different ways 
 * @param speed a float value that controls the speed of the motors higher means faster.
 * @param f_r is a char that defines the direction of the motors 'f' means forward, 'r' means reverse.
 * @param corner defines how much the robot needs to corner a higher value means a more tight corner and a lower value means a shallow corner.
 */
void turn (float speed, char f_r, float corner);

/**
 * @brief stopping both motors.
 */
void stop ();

/**
 * @brief setting both motors in the free rotating position.
 */
void free ();

/**
 * @brief calls free()
 */
void reset_motors();

/**
 * @brief turn robot on place.
 * @param f_r defines the direction of the robot 'f' means forward 'r' means backwards(reverse).
 * @param corner defines the angle how far the robot will turn higher means more.
 */
void turn_on_place (char f_r,float corner);

#endif

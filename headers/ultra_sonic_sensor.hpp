#ifndef _ULTRA_SONIC_SENSOR_HPP
#define _ULTRA_SONIC_SENSOR_HPP

void exit_signal_handler(int signo);

/**
 * @brief resets the motor offset
 */
void reset_motor_ultra_offset();

/**
 * @brief set motor to a absolute position
 * @param position the abosolute position where the motor turns to
 */
void set_motor_ultra_position(const int& position);

/**
 * @brief sets the motor to the starting position
 */
void set_motor_ultra_start_pos();

/**
 * @brief turns motor a amount of degrees relative to the current position
 * @param degrees amount of degrees the motor has to turn
 */
void turn_motor_ultra(const int& degrees);

/**
 * @brief sets motor straight (starting position)
 */
void set_motor_ultra_straight();

/**
 * @brief turns the motor left (-90 degrees)
 */
void set_motor_ultra_left();

/**
 * @brief turns the motor right (90 degrees)
 */
void set_motor_ultra_right();

/**
 * @brief gets the sensor data and returns the distance in centimeters
 * @return int the distance in centimeters (max 255)
 */
int get_ultra_distance();

/**
 * @brief checks if the sensor is active and stores it's data
 * @return ultra is active or not active
 */
int is_ultra_active();

/**
 * @brief checks if the distance is more than the minimum distance
 * @return bool enough distance between object and sensor
 */
bool is_ultra_distance_enough();

/**
 * @brief sets up the ultrasonic sensor and the motor where it's attached to
 */
void init_ultra_sensor();

#endif /* _ULTRA_SONIC_SENSOR_HPP */

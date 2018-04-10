#ifndef _ULTRA_SONIC_SENSOR_HPP
#define _ULTRA_SONIC_SENSOR_HPP

void exit_signal_handler(int signo);

// getters and setters
int get_min_ultra_distance();
void set_min_ultra_distance(const int& value);
int get_default_min_ultra_distance();
void set_motor_ultra_position(const int& position);

// resets the motor encoder to 0
void reset_motor_ultra_offset();

// sets the motor to the starting position
void set_motor_ultra_start_pos();

// gets the motor position
int get_motor_ultra_position();

// turns motor a amount of degrees relative to the current position
void turn_motor_ultra(const int& degrees);

// sets the motor to the starting position
void set_motor_ultra_straight();

// turns the motor left (-90 degrees)
void set_motor_ultra_left();

// turns the motor right (90 degrees)
void set_motor_ultra_right();

// gets the sensor data and returns the distance in centimeters
int get_ultra_distance();

// checks if the sensor is active and returns it's a given error code
int is_ultra_active();

// checks if the distance is more than the minimum distance
bool is_ultra_distance_enough();

// sets up the ultrasonic sensor and the motor where it's attached to
void init_ultra_sensor();

#endif /* _ULTRA_SONIC_SENSOR_HPP */

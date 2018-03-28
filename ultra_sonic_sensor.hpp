#ifndef _ULTRA_SONIC_SENSOR_HPP
#define _ULTRA_SONIC_SENSOR_HPP

void exit_signal_handler(int signo);

void reset_motor_offset();
void set_motor_position(const int& position);
void set_motor_start_pos();
void turn_motor(const int& degrees);
void set_motor_straight();
void set_motor_left();
void set_motor_right();

int get_ultrasonic_distance();
int is_sensor_active();
void init_ultrasonic_sensor();

#endif /* _ULTRASONICSENSOR_HPP */

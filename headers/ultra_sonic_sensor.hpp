#ifndef _ULTRA_SONIC_SENSOR_HPP
#define _ULTRA_SONIC_SENSOR_HPP

void exit_signal_handler(int signo);

int get_min_ultra_distance();
void set_min_ultra_distance(const int& value);
int get_default_min_ultra_distance();

void reset_motor_ultra_offset();
void set_motor_ultra_position(const int& position);
void set_motor_ultra_start_pos();
void turn_motor_ultra(const int& degrees);
void set_motor_ultra_straight();
void set_motor_ultra_left();
void set_motor_ultra_right();

int get_ultra_distance();
int is_ultra_active();
bool is_ultra_distance_enough();
void init_ultra_sensor();

#endif /* _ULTRA_SONIC_SENSOR_HPP */

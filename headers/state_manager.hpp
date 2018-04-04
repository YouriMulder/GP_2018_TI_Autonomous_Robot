#ifndef _STATE_MANAGER_HPP
#define _STATE_MANAGER_HPP
#include <vector>
using namespace std;

int get_current_speed();
void set_current_speed(const int& speed);
int get_current_angle();
void set_current_angle(const int& angle);
char get_current_direction();
void set_current_direction(const char& direction);

void dodge_object_state();
float update_vect(int & current_angle);
void follow_line_state();

#endif /* _STATE_MANAGER_HPP */

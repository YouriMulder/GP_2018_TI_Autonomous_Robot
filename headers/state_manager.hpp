#ifndef _STATE_MANAGER_HPP
#define _STATE_MANAGER_HPP
using namespace std;

int get_current_speed();
void set_current_speed(const int& speed);
int get_current_angle();
void set_current_angle(const int& angle);
char get_current_direction();
void set_current_direction(const char& direction);

// transfers the state from dodge_object to follow_line
void dodge_object_state();

// adds the current_angle to the vector with the angles
float update_vect(const int& current_angle);

// follows the line and detects objects on the line
bool follow_line_state();

#endif /* _STATE_MANAGER_HPP */

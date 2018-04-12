#ifndef _STATE_MANAGER_HPP
#define _STATE_MANAGER_HPP
using namespace std;

#include <vector>

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

//print a 2d vector
void print_map(const std::vector<vector<int>> & grid);

//decide which way to head to.
char grid_decision(const std::vector<vector<int>> & grid, const int & current_x, const int & current_y, const int & max_w, const int & max_h, const int & x, const int & y);

//find a way to a cordinate on a grit
void grid(const int & x, const int & y, const int & max_w = 0, const int & max_h = 0);

#endif /* _STATE_MANAGER_HPP */

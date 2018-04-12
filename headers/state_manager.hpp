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
bool follow_line_state();

//print a 2d vector
void print_map(const vector<vector<int>> & grid);

//decide which way to head to.
char grid_decision(const vector<vector<int>> & grid, const int & current_x, const int & current_y, const int & max_w, const int & max_h, const int & x, const int & y);

//find a way to a cordinate on a grit
void grid(const int & x, const int & y, const int & max_w = 0, const int & max_h = 0);

#endif /* _STATE_MANAGER_HPP */

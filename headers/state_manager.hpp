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

char grid_decision(const vector<vector<int>> & grid, int current_x, int current_y, int max_w, int max_h, int x, int y);
void grid(const int & x, const int & y, const int & max_w = 0, const int & max_h = 0);

#endif /* _STATE_MANAGER_HPP */

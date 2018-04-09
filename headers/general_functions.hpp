#ifndef GP_2018_TI_AUTONOMOUS_ROBOT_GENERAL_FUNCTIONS_HPP
#define GP_2018_TI_AUTONOMOUS_ROBOT_GENERAL_FUNCTIONS_HPP

#include <vector>

// checks if a substring is the given string
bool find_sub_string(string str, string sub);

// removes substring from the given string
string remove_sub_str(string str, string sub);

// calculates the average value of the vector
int average_vector(const std::vector<int>& v);

#endif /* GP_2018_TI_AUTONOMOUS_ROBOT_GENERAL_FUNCTIONS_HPP */

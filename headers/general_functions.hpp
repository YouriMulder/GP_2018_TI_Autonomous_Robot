#ifndef GP_2018_TI_AUTONOMOUS_ROBOT_GENERAL_FUNCTIONS_HPP
#define GP_2018_TI_AUTONOMOUS_ROBOT_GENERAL_FUNCTIONS_HPP

#include <vector>
#include <string>

// checks if a substring is the given string
bool find_sub_string(std::string str, std::string sub);

// removes substring from the given string
std::string remove_sub_str(std::string str, std::string sub);

// calculates the average value of the vector
int average_vector(const std::vector<int>& v);

#endif /* GP_2018_TI_AUTONOMOUS_ROBOT_GENERAL_FUNCTIONS_HPP */

#include "BrickPi3/BrickPi3.h"
#include <iostream>
#include <unistd.h>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

BrickPi3 BP_gfunctions;

/**
 * @brief check if substring is in string
 * @param string str -string to search in
 * @param string sub -string so find
 * @return bool -true if sub has been found
 */
bool find_sub_string(string str, string sub){
    while (str.find(sub) != string::npos){
        return true;
    }
    return false;
}

/**
 * @brief remove substring from string
 * @param string str -string to search in
 * @param string sub -string to remove
 * @return string str -returns str where sub has been removed from
 */
string remove_sub_str(string str, string sub){
    while (str.find(sub) != string::npos){
        str.erase(str.find(sub), sub.length());
    }
    return str;
}

/**
 * @brief calculate the average in in a vector<int>
 * @param const vector<int> & v
 * @return int -average
 */
int average_vector(const vector<int>& v) {
  int total = 0;
  for(const int& x : v) { total += x; }
  return total/v.size();
}

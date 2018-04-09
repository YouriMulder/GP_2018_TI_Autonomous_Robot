#include "BrickPi3/BrickPi3.h"
#include <iostream>
#include <unistd.h>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

BrickPi3 BP_gfunctions;

/**
  checks if substring is in the given substring
  @param string full string
  @param string substring
  @return bool true if the value is found, else false
 */
bool find_sub_string(string str, string sub){
    while (str.find(sub) != string::npos){
        return true;
    }
    return false;
}

/**
  removes substring from the given substring
  @param string str full string you want to remove from
  @param string sub substring you want to remove from the full string
  @return string the string minus the substring
 */
string remove_sub_str(string str, string sub){
    while (str.find(sub) != string::npos){
        str.erase(str.find(sub), sub.length());
    }
    return str;
}

/**
  returns the average value of the vector
  @param vector the vector you want the average value from
  @return int average value in the vector
 */
int average_vector(const vector<int>& v) {
  int total = 0;
  for(const int& x : v) { total += x; }
  return total/v.size();
}

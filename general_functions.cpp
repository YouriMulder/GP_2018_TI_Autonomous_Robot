#include "BrickPi3/BrickPi3.h"
#include <iostream>
#include <unistd.h>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

BrickPi3 BP_gfunctions;

//check if substring is in string
bool find_sub_string(string str, string sub){
    while (str.find(sub) != string::npos){
        return true;
    }
    return false;
}

//remove substring from string
string remove_sub_str(string str, string sub){
    while (str.find(sub) != string::npos){
        str.erase(str.find(sub), sub.length());
    }
    return str;
}

int average_vector(const vector<int>& v) {
  int total = 0;
  for(const int& x : v) { total += x; }
  return total/v.size();
}

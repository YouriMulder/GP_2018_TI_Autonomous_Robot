#include <thread>
#include <chrono>
#include <iostream>
#include "headers/state_manager.hpp"
#include "headers/driving_motors.hpp"
#include "headers/ultra_sonic_sensor.hpp"
using namespace std;

int current_speed = 100;
int current_angle = 0;
char current_direction = 'f';
// getters and setters
// -------------------
int get_current_speed() {
  return current_speed;
}

void set_current_speed(const int& speed) {
  current_speed = speed;
}

int get_current_angle() {
  return current_angle;
}

void set_current_angle(const int& angle) {
  current_angle = angle;
}

char get_current_direction() {
  return current_direction;
}

void set_current_direction(const char& direction) {
  current_direction = direction;
}
// ------------------

void dodge_object_state() {
  cout << "Dodge" << endl;
}

void follow_line_state() {
  if(!is_ultra_distance_enough()) {
    stop();
  } else {
    straight(current_speed, current_direction);
  }
}

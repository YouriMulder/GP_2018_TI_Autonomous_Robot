#include <thread>
#include <chrono>
#include <iostream>
#include "state_manager.hpp"
#include "driving_motors.hpp"
#include "ultra_sonic_sensor.hpp"
using namespace std;

void dodge_object_state() {
  cout << "Dodge" << endl;
}

void follow_line_state() {
  straight(100, 'f');
  cout << get_ultra_distance() << endl;
  if(!is_ultra_distance_enough()) {
    stop();
    dodge_object_state();
  }
}

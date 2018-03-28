#include "ultra_sonic_sensor.hpp"
#include <chrono>
#include <thread>
#include <iostream>
using namespace std;

int main() {
  init_ultrasonic_sensor();

  while(true) {
    if(is_sensor_active() == 0) {
      if(get_ultrasonic_distance() < 10) {
        cout << "OOPS" << endl;
      } else {
        cout << "MEH" << endl;
      }
    }
  }
}

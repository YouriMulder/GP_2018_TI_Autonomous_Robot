#include <chrono>
#include <thread>
#include <signal.h>
#include <iostream>
#include "BrickPi3.h"

#include "ultra_sonic_sensor.hpp"
#include "driving_motors.hpp"
using namespace std;

BrickPi3 BP_main;

void exit_signal_handler(int signo);


int main() {
  signal(SIGINT, exit_signal_handler);

  init_ultrasonic_sensor();
  reset_motors();
  straight(25, 'f');
  while(true) {
    if(is_sensor_active() == 0) {
      cout << get_ultrasonic_distance() << endl;
      if(get_ultrasonic_distance() < 20) {
        stop();
        std::this_thread::sleep_for(std::chrono::milliseconds(3000));
      } else {
        straight(25, 'f');
      }

    }

  }
}

void exit_signal_handler(int signo) {
  if(signo == SIGINT) {
    reset_motors();
    set_motor_straight();
    BP_main.reset_all();
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    exit(-2);
  }
}

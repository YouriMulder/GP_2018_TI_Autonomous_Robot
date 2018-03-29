#include <chrono>
#include <thread>
#include <signal.h>
#include <iostream>
#include "BrickPi3.h"

#include "ultra_sonic_sensor.hpp"
#include "driving_motors.hpp"
#include "state_manager.hpp"
using namespace std;

bool robot_active = true;

BrickPi3 BP_main;

void exit_signal_handler(int signo);

int main() {
  signal(SIGINT, exit_signal_handler);

  init_ultra_sensor();
  reset_motors();

  while(robot_active) {
    follow_line_state();
  }
}

void exit_signal_handler(int signo) {
  if(signo == SIGINT) {
    reset_motors();
    set_motor_ultra_straight();
    BP_main.reset_all();
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    exit(-2);
  }
}

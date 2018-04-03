#include <chrono>
#include <thread>
#include <signal.h>
#include <iostream>
#include "BrickPi3/BrickPi3.h"

#include "headers/ultra_sonic_sensor.hpp"
#include "headers/driving_motors.hpp"
#include "headers/state_manager.hpp"
#include "headers/touch_sensor.hpp"
using namespace std;

bool robot_active = true;

BrickPi3 BP_main;

void exit_signal_handler(int signo);

void init_all() {
  init_ultra_sensor();
  init_motors();
  init_touch();
}

int main() {
  cout << "Starting bot" << endl;

  signal(SIGINT, exit_signal_handler);
  init_all();
  reset_motors();

  straight(get_current_speed(), get_current_direction());

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

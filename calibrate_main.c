#include "BrickPi3/BrickPi3.h"
#include <chrono>
#include <iostream>
#include <signal.h>
#include <thread>

#include "headers/calibrate.hpp"
#include "headers/color_sensor.hpp"
#include "headers/driving_motors.hpp"
#include "headers/light_sensor.hpp"
using namespace std;

bool robot_active = true;

BrickPi3 BP_main;

void exit_signal_handler(int signo);

void init_all() {
  init_motors();
  set_light_sensor();
  set_color_sensor();
}

int main() {
  cout << "Starting bot" << endl;

  signal(SIGINT, exit_signal_handler);
  init_all();
  reset_motors();
  calibrate_line_sensors();
}

void exit_signal_handler(int signo) {
  if (signo == SIGINT) {
    reset_motors();
    BP_main.reset_all();
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));

    exit(-2);
  }
}

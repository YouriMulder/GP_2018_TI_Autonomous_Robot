#include <chrono>
#include <thread>
#include <signal.h>
#include <iostream>
#include <unistd.h>
#include "BrickPi3/BrickPi3.h"

#include "headers/ultra_sonic_sensor.hpp"
#include "headers/driving_motors.hpp"
#include "headers/state_manager.hpp"
#include "headers/touch_sensor.hpp"
#include "headers/light_sensor.hpp"
#include "headers/color_sensor.hpp"
using namespace std;

bool robot_active = true;

BrickPi3 BP_main;

void exit_signal_handler(int signo);

void init_all() {
  init_ultra_sensor();
  init_motors();
  init_touch();
  set_light_sensor();
  //light_calibrate();
  set_color_sensor();
  //color_calibrate();
}

void calibrate_ultra_sonic_motor(const int& touch_to_middle_degrees) {
  while(true) {
    turn_motor_ultra(-10);
    if(get_touch_data()) {
      reset_motor_ultra_offset();
      turn_motor_ultra(touch_to_middle_degrees);
      std::this_thread::sleep_for(std::chrono::seconds(1));

      reset_motor_ultra_offset();

      break;
    }
  }
}

int main() {
  cout << "Starting bot" << endl;

  signal(SIGINT, exit_signal_handler);
  init_all();
  reset_motors();
	int start =0;
	cout << "start driving" <<endl;
	cin >> start;

	if(start ==1) {
    calibrate_ultra_sonic_motor(90);
    while(robot_active) {
      robot_active = follow_line_state();
    }
  }
  exit_signal_handler(SIGINT);
}

void exit_signal_handler(int signo) {
  if(signo == SIGINT) {
    reset_motors();
    set_motor_ultra_straight();
    BP_main.reset_all();
    std::this_thread::sleep_for(std::chrono::seconds(1));

    exit(-2);
  }
}

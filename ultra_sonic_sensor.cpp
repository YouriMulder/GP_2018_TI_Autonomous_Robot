#include "ultra_sonic_sensor.hpp"

#include "BrickPi3.h"
#include <iostream>
#include <signal.h>
#include <chrono>
#include <thread>
using namespace std;

#define MOTOR PORT_D
#define ULTRASONIC PORT_4

BrickPi3 BP;

void exit_signal_handler(int signo);

sensor_ultrasonic_t ultra_sonic;

void reset_motor_offset() {
  BP.offset_motor_encoder(MOTOR, BP.get_motor_encoder(MOTOR));
}

void set_motor_position(const int& position) {
  BP.set_motor_position(MOTOR, position);
}

void set_motor_start_pos() {
  set_motor_position(0);
}

void turn_motor(const int& degrees) {
  BP.set_motor_position_relative(MOTOR, degrees);
}

void set_motor_straight() {
  set_motor_start_pos();
}

void set_motor_left() {
  set_motor_position(-90);
}

void set_motor_right() {
  set_motor_position(90);
}

int get_ultrasonic_distance() {
  BP.get_sensor(ULTRASONIC, ultra_sonic);
  return ultra_sonic.cm;
}

int is_sensor_active() {
  return BP.get_sensor(ULTRASONIC, ultra_sonic);
}

void init_ultrasonic_sensor() {
  signal(SIGINT, exit_signal_handler);
  int detect = BP.detect();
  int sensor_type = BP.set_sensor_type(ULTRASONIC, SENSOR_TYPE_NXT_ULTRASONIC);
  reset_motor_offset();
}

void exit_signal_handler(int signo) {
  if(signo == SIGINT) {
    set_motor_straight();
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    exit(-2);
  }
}

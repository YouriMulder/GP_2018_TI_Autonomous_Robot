#include "ultra_sonic_sensor.hpp"

#include "BrickPi3.h"
#include <iostream>
#include <chrono>
#include <thread>
using namespace std;

#define MOTOR PORT_D
#define ULTRASONIC PORT_4

BrickPi3 BP_ultra;

sensor_ultrasonic_t ultra_sonic;

void reset_motor_offset() {
  BP_ultra.offset_motor_encoder(MOTOR, BP_ultra.get_motor_encoder(MOTOR));
}

void set_motor_position(const int& position) {
  BP_ultra.set_motor_position(MOTOR, position);
}

void set_motor_start_pos() {
  set_motor_position(0);
}

void turn_motor(const int& degrees) {
  BP_ultra.set_motor_position_relative(MOTOR, degrees);
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
  BP_ultra.get_sensor(ULTRASONIC, ultra_sonic);
  return ultra_sonic.cm;
}

int is_sensor_active() {
  return BP_ultra.get_sensor(ULTRASONIC, ultra_sonic);
}

void init_ultrasonic_sensor() {
  int detect = BP_ultra.detect();
  int sensor_type = BP_ultra.set_sensor_type(ULTRASONIC, SENSOR_TYPE_NXT_ULTRASONIC);
  reset_motor_offset();
}

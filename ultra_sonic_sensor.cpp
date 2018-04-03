#include "headers/ultra_sonic_sensor.hpp"

#include "BrickPi3/BrickPi3.h"
#include <iostream>
#include <chrono>
#include <thread>
using namespace std;

#define MOTOR PORT_D
#define ULTRASONIC PORT_4

#define min_ultra_distance 20

BrickPi3 BP_ultra;

sensor_ultrasonic_t ultra_sonic;

void reset_motor_ultra_offset() {
  BP_ultra.offset_motor_encoder(MOTOR, BP_ultra.get_motor_encoder(MOTOR));
}

void set_motor_ultra_position(const int& position) {
  BP_ultra.set_motor_position(MOTOR, position);
}

void set_motor_ultra_start_pos() {
  set_motor_ultra_position(0);
}

void turn_motor_ultra(const int& degrees) {
  BP_ultra.set_motor_position_relative(MOTOR, degrees);
}

void set_motor_ultra_straight() {
  set_motor_ultra_start_pos();
}

void set_motor_ultra_left() {
  set_motor_ultra_position(-90);
}

void set_motor_ultra_right() {
  set_motor_ultra_position(90);
}

int is_ultra_active() {
  return BP_ultra.get_sensor(ULTRASONIC, ultra_sonic);
}

int get_ultra_distance() {
  BP_ultra.get_sensor(ULTRASONIC, ultra_sonic);
  return ultra_sonic.cm;
}

bool is_ultra_distance_enough() {
  int distance = get_ultra_distance();
  cout << !(distance > 0 && distance < min_ultra_distance) << endl;
  return !(distance > 0 && distance < min_ultra_distance);
}

void init_ultra_sensor() {
  int detect = BP_ultra.detect();
  int sensor_type = BP_ultra.set_sensor_type(ULTRASONIC, SENSOR_TYPE_NXT_ULTRASONIC);
  set_motor_ultra_start_pos();
  reset_motor_ultra_offset();
}

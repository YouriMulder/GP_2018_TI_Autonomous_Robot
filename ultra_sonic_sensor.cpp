#include "headers/ultra_sonic_sensor.hpp"
#include "BrickPi3/BrickPi3.h"
#include <iostream>
#include <chrono>
#include <thread>
using namespace std;

#define MOTOR PORT_D
#define ULTRASONIC PORT_4

// minimum distance
int min_ultra_distance = 10;
#define default_min_ultra_distance 20

BrickPi3 BP_ultra;

// get the minimum distance there may be between a object and the robot
int get_min_ultra_distance() { return min_ultra_distance; }

// set the minimum distance there may be between a object and the robot
void set_min_ultra_distance(const int& value) { min_ultra_distance = value; }

int get_default_min_ultra_distance() { return default_min_ultra_distance; }

// ultra_sonic distance sensor variables are saved here
sensor_ultrasonic_t ultra_sonic;

// resets the motor offset
void reset_motor_ultra_offset() {
  BP_ultra.offset_motor_encoder(MOTOR, BP_ultra.get_motor_encoder(MOTOR));
}

/**
  * set motor to a absolute position
  * @param position the abosolute position where the motor turns to
  */
void set_motor_ultra_position(const int& position) {
  BP_ultra.set_motor_position(MOTOR, position);
}

// sets the motor to the starting position
void set_motor_ultra_start_pos() {
  set_motor_ultra_position(0);
}

/**
  * turns motor a amount of degrees relative to the current position
  * @param degress amount of degress the motor has to turns
  */
void turn_motor_ultra(const int& degrees) {
  BP_ultra.set_motor_position_relative(MOTOR, degrees);
}

// sets motor straight aka starting position
void set_motor_ultra_straight() {
  set_motor_ultra_start_pos();
}

// turns the motor left (-90 degrees)
void set_motor_ultra_left() {
  set_motor_ultra_position(-90);
}

// turns the motor right (90 degrees)
void set_motor_ultra_right() {
  set_motor_ultra_position(90);
}

// checks if the sensor is active and stores it's data
int is_ultra_active() {
  return BP_ultra.get_sensor(ULTRASONIC, ultra_sonic);
}

/**
  * gets the sensor data and returns the distance in centimeters
  * @return int the distance in centimeters (max 255)
  */
int get_ultra_distance() {
  BP_ultra.get_sensor(ULTRASONIC, ultra_sonic);
  return ultra_sonic.cm;
}

/**
  * checks if the distance is more than the minimum distance
  * @return bool enough distance between object and sensor
  */
bool is_ultra_distance_enough() {
  int distance = get_ultra_distance();
  return !(distance > 0 && distance < min_ultra_distance);
}

// sets up the ultrasonic sensor and the motor where it's attached to
void init_ultra_sensor() {
  int detect = BP_ultra.detect();
  int sensor_type = BP_ultra.set_sensor_type(ULTRASONIC, SENSOR_TYPE_NXT_ULTRASONIC);
  set_motor_ultra_start_pos();
  reset_motor_ultra_offset();
  BP_ultra.set_motor_limits(MOTOR, 50, 100);
}

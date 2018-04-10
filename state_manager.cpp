#include <thread>
#include <chrono>
#include <ctime>
#include <iostream>
#include <unistd.h>
#include <vector>
#include "headers/state_manager.hpp"
#include "headers/driving_motors.hpp"
#include "headers/ultra_sonic_sensor.hpp"
#include "headers/light_sensor.hpp"
#include "headers/color_sensor.hpp"
#include "headers/general_functions.hpp"
using namespace std;

// variables for calculating angles
vector<float> angles ={0,0,0};
int index = 0;
float avg_angle;

// robot variables
int current_speed = 50;
int default_speed = 50;
int current_angle = 0;
char current_direction = 'f';

// getters and setters
// -------------------
int get_current_speed() {
  return current_speed;
}

void set_current_speed(const int& speed) {
  current_speed = speed;
}

int get_current_angle() {
  return current_angle;
}

void set_current_angle(const int& angle) {
  current_angle = angle;
}

char get_current_direction() {
  return current_direction;
}

void set_current_direction(const char& direction) {
  current_direction = direction;
}
// ------------------

/**
  gives a random boolean
  @return bool random value between 0-1
 */
bool random_bool() {
  srand(time(NULL));
  return rand() % 2;
}

/**
  turns the robot perpendicular to the object
  @param char direction the robot is moving 'f' forward, 'r' reverse
  @param int degrees the robots has to turn
  @param bool whether the ultra sonic sensor has to turn
 */
void turn_to_object(const char& movement, const int& degrees, const bool& ultra_sonic_turn) {
  turn_on_place(movement, degrees);
  if(ultra_sonic_turn) {
    turn_motor_ultra(degrees * -1);
  }
  this_thread::sleep_for(chrono::seconds(1));
}

/**
  drives alongside the object
  @param char direction the robot is moving 'f' forward, 'r' reverse
  @param int speed the robot is driving at
 */
bool trace_object(const char& movement, const int& speed) {
  vector<int> distances = {};
  for(int i = 0; i < 20; i++, distances.push_back(get_ultra_distance()));
  int avg_distance = average_vector(distances);

  straight(speed, movement);

  while(!is_ultra_distance_enough()) {
    turn(speed, movement, 5 * (get_ultra_distance() - avg_distance));
    if(light_get_reflection() > 50 || color_detect_line()) {
      cout << light_get_reflection() << ' ' << color_get_reflection() << endl;
    }
    if(light_get_reflection() > 50 || color_detect_line()) {
      stop();
      return true;
    }
  }

  stop();

  this_thread::sleep_for(chrono::seconds(1));

  if(!is_ultra_distance_enough()) {
    return trace_object(movement, speed);
  }
  return false;
}


/**
  drives the robot past the object
  @param char direction the robot is moving 'f' forward, 'r' reverse
  @param int speed the robot is driving at
 */
bool move_past_object(const char& movement, const int& speed) {
  straight(speed, movement);
  for(int i =0; i < 130; i++) {
    if(light_get_reflection() > 50 || color_detect_line()) {
      return true;
    }
    this_thread::sleep_for(chrono::milliseconds(10));
  }
  stop();
  return false;
}

/**
  drives a centrain direction until there is a object detected
  @param char direction the robot is moving 'f' forward, 'r' reverse
  @param int speed the robot is driving at
 */
bool move_to_object(const char& movement, const int& speed) {
  straight(speed, movement);
  while(is_ultra_distance_enough()) {
    if(light_get_reflection() > 50 || color_detect_line()) {
      stop();
      return true;
    }
  }
  stop();
  return false;
}

/**
  inverse an integer negative becomes positive and vise vesa
  @param int the value you want to inverse
 */
void inverse_degrees(int& degrees) {
  degrees *= -1;
}

/**
  transfers the state from dodge_object to follow_line
  @param char direction the robot is moving 'f' forward, 'r' reverse
  @param int degrees the robot has to turn to set everything straight
 */
void dodge_object_to_follow_line_state(const char& movement, int& degrees) {
  stop();
  inverse_degrees(degrees);
  set_motor_ultra_straight();
  turn(10, current_direction, degrees * 1.1);
  set_min_ultra_distance(get_default_min_ultra_distance());
  this_thread::sleep_for(chrono::milliseconds(1500));
}

/**
  drives around the detected object
  @param char direction the robot is moving 'f' forward, 'r' reverse
 */
void dodge_object_state(const char& movement) {
  set_min_ultra_distance(get_default_min_ultra_distance());

  int start_angle = get_motor_ultra_position();
  set_motor_ultra_start_pos();
  current_speed = default_speed;
  int degrees = 90;
  //bool side = random_bool();
  bool side = 1;

  set_min_ultra_distance(get_min_ultra_distance() + 10);

  this_thread::sleep_for(chrono::seconds(1));

  if(!is_ultra_distance_enough()) {
    stop();

    if(side) {
      degrees *= -1;
    }

    turn_to_object(movement, degrees + start_angle, true);
    trace_object(movement, current_speed);

    move_past_object(movement, current_speed);

    inverse_degrees(degrees);

    turn_to_object(movement, degrees, false);
    if(move_to_object(movement, current_speed) ||
        trace_object(movement, current_speed) ||
        move_past_object(movement, current_speed)) {
      cout << "prima" << endl;
      dodge_object_to_follow_line_state(movement, degrees);
      return;
    }

    turn_to_object(movement, degrees, true);
    straight(current_speed, movement);
    while(light_get_reflection() < 50 && color_get_reflection() < 50) {}
    dodge_object_to_follow_line_state(movement, degrees);
  }
}

/**
  adds the current_angle to the vector with the angles
  @param int the current_angle the robot should move to
  @return float average value of the vector angles
 */
float update_vect(const int& current_angle){
	float sum =0;
	angles[index]=current_angle;
		 for (unsigned int i=0;i<angles.size();i++){
			 sum += angles[i];
		 }
	float avg_angle = sum/angles.size();
		  if (index == 2){
			  index =0;
		  } else {
			index++;
		  }
	return avg_angle;
}

/**
  follows the line and detects objects on the line
  @return bool whether the robot should be active or not
 */
bool follow_line_state() {
  current_speed = default_speed;

  if(is_color_red()) {
    stop();
    return false;
  }

  if(!is_ultra_distance_enough()) {
		stop();
    current_direction = 'f';
    dodge_object_state(current_direction);
  }

  if (light_get_reflection()>color_get_reflection()){
	  current_angle = light_get_reflection();
  }
  else {
	  current_angle = -1 * color_get_reflection();
  }

	avg_angle = update_vect(current_angle);

  if(avg_angle > 5 && avg_angle < 15) {
    current_angle = 5 ;
  }
	else if(avg_angle < -5 && avg_angle > -15) {
    current_angle = -5 ;
  }
  else if(avg_angle >= 15 &&  avg_angle <= 75){
		current_speed = current_speed - 0.3*current_angle;
    current_angle *=2;
	}
	else if(avg_angle < -15 && avg_angle >= -75){
		current_speed = current_speed - (-1*0.3*current_angle);
    current_angle *=2;
	}

  if(avg_angle > -90 && avg_angle < 90) {
    set_motor_ultra_position(avg_angle);
	  turn(current_speed, current_direction, avg_angle);
  }
  else {
    set_motor_ultra_position(avg_angle);
    turn_on_place(current_direction, current_angle);
  }
  usleep(7500);
  return true;
}

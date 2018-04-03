#include <thread>
#include <chrono>
#include <iostream>
#include <unistd.h>
#include "headers/state_manager.hpp"
#include "headers/driving_motors.hpp"
#include "headers/ultra_sonic_sensor.hpp"
#include "headers/light_sensor.hpp"
#include "headers/color_sensor.hpp"
using namespace std;

int current_speed = 25;
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

void dodge_object_state() {
  set_motor_ultra_right();
  current_angle = 90;
  turn_on_place(current_direction, current_angle);
  current_angle = 0;
  std::this_thread::sleep_for(std::chrono::milliseconds(3000));
  set_motor_ultra_straight();
  straight(current_speed, current_direction);
}

void follow_line_state() {


		  //if(!is_ultra_distance_enough()) {
			//stop();
			//dodge_object_state();
		  //} 
		  if (light_get_reflection()>color_get_reflection()){
			  int l_ref = light_get_reflection();
			  current_angle = l_ref;
			   if (l_ref>90){
				  turn_on_place(current_speed,15);
				  cout << "error" <<endl;
			  }
			  else if (l_ref>75){
				  current_angle *=6;
				 
			  }
			  else if (l_ref>50){
				  current_angle *=4;
			  }
			  else if (l_ref>25){
				current_angle *=2;
			  }
			  current_angle = light_get_reflection();
		  }
		  else {
			  int c_ref = color_get_reflection();
			  current_angle = -1* c_ref;
			  if (c_ref>90){
				  turn_on_place(current_speed,15);
				  cout << "error" <<endl;
			  }
			  else if (c_ref>75){
				  current_angle *=6;
			  }
			  else if (c_ref>50){
				  current_angle *=4;
			  }
			  else if (c_ref>25){
				  current_angle *=2;
			  }
			  
			  current_angle = -1*color_get_reflection();
		  }
		
		  cout << current_angle << endl;
		turn(current_speed, current_direction, current_angle*2);
		
}

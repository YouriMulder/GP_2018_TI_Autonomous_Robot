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
using namespace std;

vector<float> angles ={0,0,0};
int index =0;
float avg_angles;

int current_speed = 50;
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

bool random_bool() {
  srand(time(NULL));
  return rand() % 2;
}

// side 0 == left | side 1 == right
void dodge_object_state(const char& movement) {
  int degrees = 90;
  bool side = random_bool();

  set_min_ultra_distance(get_min_ultra_distance() + 10);

  if(!is_ultra_distance_enough()) { // add red line)
    stop();
    if(side) {
      degrees *= -1;
    }

    turn_on_place(movement, degrees);
    turn_motor_ultra(degrees * -1);
    std::this_thread::sleep_for (std::chrono::seconds(5));

    while(!is_ultra_distance_enough()) {
      straight(current_speed, movement);
    }

    std::this_thread::sleep_for(std::chrono::seconds(1));

    //while(!is_ultra_distance_enough) {}

    //turn_on_place(movement, degrees * -1);
    stop();
    turn_motor_ultra(degrees);
    set_min_ultra_distance(get_default_min_ultra_distance());
    std::this_thread::sleep_for (std::chrono::seconds(5));
  }
}

float update_vect(int & current_angle){
	float sum =0;
	angles[index]=current_angle;
		 for (unsigned int i=0;i<angles.size();i++){
			 sum += angles[i];
		 }
	float avg_angles = sum/angles.size();
		  if (index ==5){
			  index =0;
		  }
		  else{
			index++;
		  }
	return avg_angles;
}

void follow_line_state() {
	current_speed = 50;
		  if(!is_ultra_distance_enough()) {
			stop();
			dodge_object_state('f');
			}
		  if (light_get_reflection()>color_get_reflection()){
			  current_angle = light_get_reflection();
		  }
		  else {
			  current_angle = -1 * color_get_reflection();
		  }
		avg_angles = update_vect(current_angle);

    if(avg_angles > 5 && avg_angles < 15) {
      avg_angles = 5;
    }
	else if(avg_angles < -5 && avg_angles > -15) {
      avg_angles = -5;
    }
	else if(avg_angles >= 15 &&  avg_angles < 75){
		current_speed = current_speed - 0.3*current_angle;
	}
	else if(avg_angles < -15 && avg_angles > -75){
		current_speed = current_speed - (-1*0.3*current_angle);
	}
    cout << current_speed << endl;


    if(current_angle > -90 && current_angle < 90) {
		turn(current_speed, current_direction, avg_angles);
  } else {
		turn_on_place(current_direction, current_angle);
  }
}

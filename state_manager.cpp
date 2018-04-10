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

vector<float> angles ={0,0,0};
int index = 0;
float avg_angle;

int current_speed = 25;
int default_speed = 25;
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

void turn_to_object(const char& movement, const int& degrees, const bool& ultra_sonic_turn) {
  turn_on_place(movement, degrees);
  if(ultra_sonic_turn) {
    turn_motor_ultra(degrees * -1);
  }
  this_thread::sleep_for(chrono::seconds(1));
}

void trace_object(const char& movement, const int& speed) {
  vector<int> distances = {};
  for(int i = 0; i < 20; i++, distances.push_back(get_ultra_distance()));
  int avg_distance = average_vector(distances);

  straight(speed, movement);

  while(!is_ultra_distance_enough()) {
    turn(speed, movement, 5 * (get_ultra_distance() - avg_distance));
  }

  stop();

  this_thread::sleep_for(chrono::seconds(1));

  if(!is_ultra_distance_enough()) {
    trace_object(movement, speed);
  }
}

void move_past_object(const char& movement, const int& speed) {
  straight(speed, movement);
  this_thread::sleep_for(chrono::milliseconds(1500));
  stop();
}

void move_to_object(const char& movement, const int& speed) {
  straight(speed, movement);
  while(is_ultra_distance_enough()) {}
  stop();
}

void inverse_degrees(int& degrees) {
  degrees *= -1;
}

void dodge_object_to_follow_line_state(const char& movement, int& degrees) {
  stop();
  inverse_degrees(degrees);
  turn_motor_ultra(degrees);
  turn_on_place(movement, degrees);
  this_thread::sleep_for(chrono::seconds(1));
  set_min_ultra_distance(get_default_min_ultra_distance());
}

// side 0 == left | side 1 == right
void dodge_object_state(const char& movement) {
  current_speed = default_speed;
  int degrees = 90;
  bool side = random_bool();
  side = 1;

  set_min_ultra_distance(get_min_ultra_distance() + 10);

  if(!is_ultra_distance_enough()) { // add red line)
    stop();
    if(side) {
      degrees *= -1;
    }

    turn_to_object(movement, degrees, true);
    trace_object(movement, current_speed);

    move_past_object(movement, current_speed);

    inverse_degrees(degrees);


    turn_to_object(movement, degrees, false);
    move_to_object(movement, current_speed);
    trace_object(movement, current_speed);

    move_past_object(movement, current_speed);

    turn_to_object(movement, degrees, true);

    straight(current_speed, movement);
    while(light_get_reflection() < 50 && color_get_reflection() < 50) { }

    inverse_degrees(degrees);
    turn_on_place(movement, degrees);

    this_thread::sleep_for(chrono::seconds(1));

    set_min_ultra_distance(get_default_min_ultra_distance());
  }
}

float update_vect(int & current_angle){
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

bool follow_line_state() {
  current_speed = default_speed;

  if(is_color_red()) {
    stop();
    return false;
  }

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
	  turn(current_speed, current_direction, avg_angle);
    set_motor_ultra_position(avg_angle);
  }
  else {
    turn_on_place(current_direction, current_angle);
  }
  usleep(5000);
  return true;
}

void print_map(const vector<vector<int>> & grid){
    cout << endl;
    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[i].size(); ++j) {
            cout << grid[i][j] << ", ";
        }
        cout << "\n";
    }
    cout << endl;
}

char grid_decision(const vector<vector<int>> & grid, const int & current_x, const int & current_y, const int & max_w, const int & max_h, const int & x, const int & y, char direction){
    cout << "current_x: " << current_x << endl;
    cout << "current_y: " << current_y << endl;
    cout << "max_w: " << max_w << endl;
    cout << "max_h: " << max_h << endl;
    cout << "x: " << x << endl;
    cout << "y: " << y << endl;
    print_map(grid);
    if(current_x == max_w){
        if(max_h == current_y){
            if(current_x > x && current_x-1 >= 0){
                if(grid[current_y][current_x-1] != 2){
                    return 'l';
                }
            }
            return 'u';
        }
        if(current_y == 0){
            if(current_x > x && current_x-1 >= 0 ){
                if(grid[current_y][current_x-1] != 2){
                    return 'l';
                }
            }
            return 'd';
        }

        if(current_x < x && current_x+1 <= max_w ) {
            if (grid[current_y][current_x + 1] != 2){
                return 'r';
            }
        }
        if(current_y < y && current_y+1 <= max_h){
            if(grid[current_y+1][current_x] != 2){
                return 'd';
            }
        }
        if(current_x > x && current_x-1 >= 0 ){
            if(grid[current_y][current_x-1] != 2){
                return 'l';
            }
        }
        if(current_y >= y && current_y-1 >= 0){
            if(grid[current_y-1][current_x] != 2){
                return 'u';
            }
        }
    }

    if(current_x == 0){
        if(current_y == 0){
            if(current_x < x && current_x+1 <= max_w ){
                if(grid[current_y][current_x+1] != 2){
                    return 'r';
                }
            }else{
                if(current_y+1 <= max_h && grid[current_y+1][current_x] != 2){
                    return 'd';
                } else {
                    return 'r';
                }
            }
        }
        if(current_y == max_h){
            if(current_x < x){
                if(current_x+1 <= max_w && grid[current_y][current_x+1] != 2){
                    return 'r';
                } else {
                    return 'u';
                }
            }
            if(current_y-1 > 0 && grid[current_y-1][current_x] != 2){
                return 'u';
            } else {
                return 'r';
            }

        }
        if(current_x < x && current_x+1 <= max_w) {
            if (grid[current_y][current_x + 1] != 2){
                return 'r';
            }
        }
        if(current_y < y && current_y+1 <= max_h ){
            if(grid[current_y+1][current_x] != 2){
                return 'd';
            }
        }
        if(current_x > x && current_x-1 > 0){
            if(grid[current_y][current_x-1] != 2){
                return 'l';
            }
        }
        if(current_y > y && current_y-1 > 0){
            if(grid[current_y-1][current_x] != 2){
                return 'u';
            }
        }
    }
    if(current_x < x && current_x+1 <= max_w) {
        if (grid[current_y][current_x + 1] != 2){
            return 'r';
        } else {
            if(direction == 'r'){
                return 'd';
            } else {
                return direction;
            }
        }
    }
    if(current_y < y){
        if(current_y+1 <= max_h && grid[current_y+1][current_x] != 2){
            return 'd';
        } else {
            if(direction == 'd'){
                return 'r';
            } else {
                return direction;
            }
        }
    }
    if(current_x > x){
        if(current_x-1 > 0 && grid[current_y][current_x-1] != 2){
            return 'l';
        } else {
            if(direction == 'l'){
                return 'u';
            } else {
                return direction;
            }
        }
    }
    if(current_y > y){
        if(current_y-1 > 0 && grid[current_y-1][current_x] != 2){
            return 'u';
        } else {
            if(direction == 'u'){
                return 'l';
            } else {
                return direction;
            }
        }
    }
    cout << "ik ben er... denk ik?!?!?!???";
    return 's';
}

void grid(const int & x, const int & y, const int & max_w, const int & max_h){
    set_motor_ultra_straight();
    cout << "test grid";
    int furthest_x = 0;
    char direction = 'r';
    int current_x = 1;
    int current_y = 0;
    int offset = 0;

    vector<vector<int>> grid;

    for (int i = 0; i < max_h; ++i) {
        vector<int> m;
        grid.push_back(m);
        for (int j = 0; j < max_w; ++j) {
            grid[i].push_back(0);
        }
    }


    while(true){
        current_speed = default_speed;
        if(get_ultra_distance() < 15) {
            cout << "object detected" << endl;
            stop();
            grid[current_y][current_x] = 2;
            if(direction == 'r'){
                current_x--;
            } else if(direction == 'l'){
                current_x++;
            } else if(direction == 'u'){
                current_y++;
            } else if(direction == 'd'){
                current_y--;
            }

           current_angle = 0;

            while(-1*color_get_reflection() > -90 && light_get_reflection() < 90) {
                if (light_get_reflection()>color_get_reflection()){
                    current_angle =  light_get_reflection();
                }
                else {
                    current_angle = -1* color_get_reflection();
                }
                straight(10,'r');
            }
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
        }
        else if(avg_angle < -15 && avg_angle >= -75){
            current_speed = current_speed - (-1*0.3*current_angle);
        }

        if(-1*color_get_reflection() > -90 && light_get_reflection() < 90) {
            turn(current_speed, current_direction, avg_angle);
        }
        else {
            //kruispunt
            grid[current_y][current_x] = 1;
            char new_direction = grid_decision(grid, current_x, current_y, max_w, max_h, x, y, direction);

            if(direction == 'r'){
                offset = 0;
            } else if(direction == 'l'){
                offset = -180;
            } else if(direction == 'u'){
                offset = 90;
            } else if(direction == 'd'){
                offset = -90;
            }
            cout << "\nold direction: " << direction << "new direction: " << new_direction << " offset: " << offset;
            if(new_direction == 'r'){
                turn(10, current_direction, offset+0);
                current_x++;
                cout << "\n going right";
            } else if(new_direction == 'd'){
                cout << "\n going down";
                turn(10, current_direction, offset+90);
                current_y++;
            } else if(new_direction == 'l'){
                current_x--;
                cout << "\n going left";
                turn(10, current_direction, offset+180);
            } else if(new_direction == 'u'){
                current_y--;
                cout << "\n going up";
                turn(10, current_direction, offset-90);
            } else if (new_direction == 's'){
                cout << "\n stopping";
                stop();
                break;
            }
            this_thread::sleep_for(chrono::milliseconds(1500));
            direction = new_direction;
            straight(current_speed, current_direction);
            usleep(500000);
            cout << "\n___________________________________________\n";
        }
        usleep(5000);
    }
}
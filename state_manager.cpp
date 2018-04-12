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

/**
 * @brief print a 2d vector
 * @param vector<vector<int>> grid
 */
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

/**
 * @brief find the direction where find is located
 * @param const vector<vector<int>> & grid
 * @param const int & current_x
 * @param const int & current_y
 * @param const int & max_y
 * @param cons int & max_x
 * @param int find
 * @return char direction
 */
char find_in_grid(const vector<vector<int>> & grid, const int & current_x, const int & current_y, const int & max_y, const int & max_x, int find){
    if(current_x+1 <= max_x && grid[current_y][current_x+1] == find){
        return 'n';
    }
    if(current_y+1 <= max_y && grid[current_y+1][current_x] == find){
        return 'e';
    }
    if(current_y-1 >= 0 && grid[current_y-1][current_x] == find){
        return 'w';
    }
    if(current_x-1 >= 0 && grid[current_y][current_x-1] == find){
        return 's';
    }
    cout << "best way stop " << find << endl;
    return 'h';
}

/**
 * @brief find the best direction to head based on the grid
 * @param const vector<vector<int>> & grid
 * @param const int & current_x
 * @param const int & current_y
 * @param const int & max_y
 * @param const int & max_x
 * @return
 */
char find_best_way(const vector<vector<int>> & grid, const int & current_x, const int & current_y, const int & max_y, const int & max_x){
    cout << "best way" << endl;
    char result = find_in_grid(grid, current_x, current_y, max_y, max_x, 0);
    if(result != 'h'){
        return result;
    }
    cout << "going for 1" << endl;
    return find_in_grid(grid, current_x, current_y, max_y, max_x, 1);
}

/**
 * @brief decide which way to head to.
 * @param const vector<vector<int>> &  grid
 * @param const int & current_x
 * @param const int & current_y
 * @param const int & max_x
 * @param const int & max_y
 * @param const int & x -target axis
 * @param const int & y -target axis
 * @param char direction
 * @return char best direction to head for
 */
char grid_decision(vector<vector<int>> & grid, const int & current_x, const int & current_y, const int & max_x, const int & max_y, const int & x, const int & y, char direction){
    cout << "current_x: " << current_x << endl;
    cout << "current_y: " << current_y << endl;
    cout << "max_x: " << max_x << endl;
    cout << "max_y: " << max_y << endl;
    cout << "x: " << x << endl;
    cout << "y: " << y << endl;

    print_map(grid);

    if(current_x < x && current_x+1 <= max_x) {
        if (grid[current_y][current_x + 1] == 0){
            return 'n';
        } else {
            return find_best_way(grid, current_x, current_y, max_y, max_x);
        }
    }
    if(current_y < y){
        if(current_y+1 <= max_y && grid[current_y+1][current_x] == 0){
            return 'e';
        } else {
            return find_best_way(grid, current_x, current_y, max_y, max_x);
        }
    }

    if(current_x > x){
        if(current_x-1 >= 0 && grid[current_y][current_x-1] == 0){
            return 's';
        } else {
            return find_best_way(grid, current_x, current_y, max_y, max_x);
        }
    }
    if(current_y > y){
        if(current_y-1 >= 0 && grid[current_y-1][current_x] == 0){
            return 'w';
        } else {
            return find_best_way(grid, current_x, current_y, max_y, max_x);
        }
    }
    cout << "ik ben er... denk ik?!?!?!???";
    return 'h';
}

/**
 * @brief find a way to a cordinate on a grit
 * @param const int & x -head to this x axis
 * @param const int & y -head to this y axis
 * @param const int & max_x -max x coordinate before going of the grid
 * @param const int & max_y -max y coordinate before going of the grid
 */
void grid(const int & x, const int & y, const int & max_x, const int & max_y){
    set_motor_ultra_straight();
    cout << "test grid";
    int furthest_x = 0;
    char direction = 'n';
    int current_x = 1;
    int current_y = 0;
    int offset = 0;
    int angle = 0;
    char new_direction = 'n';
    bool cross = false;

    vector<bool> sensor_data = {};

    vector<vector<int>> grid;

    for (int i = 0; i < max_y+1; ++i) {
        vector<int> m;
        grid.push_back(m);
        for (int j = 0; j < max_x+1; ++j) {
            grid[i].push_back(0);
        }
    }

    set_min_ultra_distance(10);

    while(true){
        if(current_x < 0 || current_x > max_x || current_y < 0 || current_y > max_x){
            cout << "\nOf grid" << endl;
            stop();
            break;
        }
        current_speed = default_speed;


        if (!is_ultra_distance_enough()) {
            //object in front //////////////////////////////////////////////////////////////////
            cout << "object detected" << endl;
            free();
            grid[current_y][current_x] = 2;

            if (direction == 'n') {
                current_x--;
            } else if (direction == 's') {
                current_x++;
            } else if (direction == 'w') {
                current_y++;
            } else if (direction == 'e') {
                current_y--;
            }

            current_angle = 0;

            while (color_get_reflection() < 20 && light_get_reflection() < 70) {
                straight(10, 'r');
                this_thread::sleep_for(chrono::milliseconds(500));
            }
            stop();
            cross = true;
            straight(10,'f');
            this_thread::sleep_for(chrono::milliseconds(400));
            //stop();
            //this_thread::sleep_for(chrono::milliseconds(1000));
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

        if((color_get_reflection() > 60 && light_get_reflection() > 60) || cross) {
            //intersection///////////////////////////////////////////////////////////////////////////////////

            cross = false;
            cout << color_get_reflection() << "\n" << light_get_reflection() << endl;
            stop();
            grid[current_y][current_x] = 1;
            if(current_x == x && current_y == y){
                cout << "Ik ben er!!!";
                new_direction = 'h';
            } else {
                new_direction = grid_decision(grid, current_x, current_y, max_x, max_y, x, y, direction);
                for (unsigned int y=0; y<grid.size();y++){
                    for (unsigned int x=0; x<grid[y].size();x++){
                        if ((y+1 <= max_y && grid[y+1][x] == 2) && (x+1 <= max_x && grid[y][x+1] == 2)){
                            grid[y][x] = 2;
                        } else if((y+1 <= max_y && grid[y+1][x] == 2) && x+1 > max_x){
                            grid[y][x] = 2;
                        } else if((x+1 <= grid[y][x+1] == 2) && y+1 > max_y){
                            grid[y][x] = 2;
                        }
                    }
                }
            }


            if(direction == 'n'){
                offset = 0;
            } else if(direction == 's'){
                offset = -180;
            } else if(direction == 'w'){
                offset = 90;
            } else if(direction == 'e'){
                offset = -90;
            }
            cout << "\nold direction: " << direction << "\nnew direction: " << new_direction << " offset: " << offset;
            if(new_direction == 'n'){
                angle = offset+0;
                current_x++;
                cout << "\n going north" << endl;
            } else if(new_direction == 'e'){
                cout << "\n going east" << endl;
                angle = offset+90;
                current_y++;
            } else if(new_direction == 's'){
                current_x--;
                cout << "\n going south" << endl;
                angle = offset+180;
            } else if(new_direction == 'w'){
                current_y--;
                cout << "\n going west" << endl;
                angle = offset-90;
            } else if (new_direction == 'h'){
                cout << "\n stopping" << endl;
                stop();
                break;
            }
            cout << "angle: " << angle << endl;
            if(angle == 180){
                cout << "turn on place" << endl;
                turn(10, current_direction, 160);
            } else {
                cout << "turn" << endl;
                turn(10,current_direction, angle);
            }
            this_thread::sleep_for(chrono::milliseconds(1500));
            direction = new_direction;
            cout << "\n___________________________________________\n";
        } else {
            if(avg_angle < -95 || avg_angle > 95) {
                turn(current_speed, current_direction, avg_angle/3);
            } else {
                turn(current_speed, current_direction, avg_angle);
            }
        }
        usleep(5000);
    }
}
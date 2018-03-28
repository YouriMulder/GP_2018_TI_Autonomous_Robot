#include "BrickPi3.h"
#include <iostream>
#include <signal.h>
using namespace std;

#define MOTOR PORT_D
#define ULTRASONIC PORT_4

BrickPi3 BP;


void exit_signal_handler(int signo);

int main() {
  signal(SIGINT, exit_signal_handler);

  int detect = BP.detect();

  int sensor_type = BP.set_sensor_type(ULTRASONIC, SENSOR_TYPE_NXT_ULTRASONIC);
  BP.offset_motor_encoder(MOTOR, BP.get_motor_encoder(MOTOR));

  BP.set_motor_position_relative(MOTOR, 90);

  sensor_ultrasonic_t ultra_sonic;

  while(true) {
    if(BP.get_sensor(ULTRASONIC, ultra_sonic) == 0) {
      int32_t encoder_a = BP.get_motor_encoder(MOTOR);
      cout << encoder_a << endl;
      cout << "Light sensor (S0) : reflected" << ultra_sonic.cm << endl;
    }
  }
}

void exit_signal_handler(int signo) {
  if(signo == SIGINT) {
    BP.reset_all();
    exit(-2);
  }
}

#include "BrickPi3.h"
#include <iostream>
#include <signal.h>

BrickPi BP;

void exit_signal_handler(int signo);

int main() {
  signal(SIGINT, exit_signal_handler);

  BP.detect();

  BP.set_sensor_type(PORT_1, SENSOR_TYPE_NXT_LIGHT_ON);

  sensor_light_t light;

  while(true) {
    if(BP.get_sensor(PORT_1, light) == 0) {
      std::cout << "Light sensor (S0) : reflected" << setw(4) << Light.reflected << endl;
    }
  }
}

void exit_signal_handler(int signo) {
  if(signo == SIGINT) {
    BP.reset_all();
    exit(-2);
  }
}

#include "driving_motors.hpp"
#include "BrickPi3.h"
#include <unistd.h>
#include <signal.h>
#include <iostream>
using namespace std;
BrickPi3 BP2;


void exit_signal_handler(int signo);

int main(){
	signal(SIGINT, exit_signal_handler);
	initialize();
	int angle =0;
	for (;;){
		cin >> angle;
		straight(angle,'f');
	}
	
}

void exit_signal_handler(int signo) {
  if(signo == SIGINT) {
    reset_motors();
    exit(-2);
  }
}
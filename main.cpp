#include <stdio.h>
#include <thread>
#include <iostream>
#include <chrono>
using namespace std;

void print_test1(){
	for(;;){
	cout << "test" << endl;
	this_thread::sleep_for(chrono::seconds(1));
	}
	}


void print_test2(){
	this_thread::sleep_for(chrono::microseconds(50000));
	for(;;){
		cout << "test2" << endl;
		this_thread::sleep_for(chrono::seconds(1));
	}
}

int main()
{
	thread one(print_test1);
	thread two(print_test2);
	one.join();
	two.join();
}

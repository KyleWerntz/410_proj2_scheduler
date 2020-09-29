//============================================================================
// Name        : 410_proj2_OS.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include "../includes/joblist.h"
#include "../includes/dispatcher.h"
#include "../includes/scheduler_RR.h"
#include "../includes/scheduler_FIFO.h"
#include "../includes/scheduler_SRTF.h"
#include "../includes/PCB.h"
#include "../includes/CPU.h"
#include "../includes/stats.h"
#include "../includes/simulator.h"
#include "../includes/tester.h"

//use first or second test file
//#define TESTFILE1

using namespace std;

//prints out metrics associated with PCBs in finished_vector
void print_stats(std::string info, std::vector<PCB> &finished_vector){
	Stats myStats(finished_vector);

	cout<<endl<<info<<" ------------------------"<<endl;
	cout<<"Average wait time 		="<<myStats.get_av_wait_time()<<endl;
	cout<<"Average Response time 		="<<myStats.get_av_response_time()<<endl;
	cout<<"Average Turnaround time 	="<<myStats.get_av_turnaround_time()<<endl;
	myStats.showAllProcessInfo();
	cout<<endl;
}

//clears all containers
void resetContainer(std::queue<PCB> &ready_Q ){
		//queues dont have a built in clear
		while(!ready_Q.empty()) ready_Q.pop();	//clear it
}

//runs a complete simulation with the passed in scheduler, calculates metrics, then compares them to correct values
//returns the number of failed tests
int test_simulation(std::string info, Scheduler & s, float av_wait_time,float av_response_time, float  av_turnaround_time){

	//where all the finished processes go
	std::vector<PCB> finished_vector;

#ifdef TESTFILE1
	simulate(SOURCE_FILE_1,s,finished_vector );
#else
	simulate(SOURCE_FILE_2,s,finished_vector );
#endif
	print_stats(info, finished_vector);
	return verify_stats(info,finished_vector,av_wait_time,av_response_time,av_turnaround_time);
}

//return value is number of failed tests
int main(){

	//where all the ready to run processes go
	std::queue<PCB> ready_Q;

	//round robin
	Scheduler_RR  scheduler1(ready_Q,DEFAULT_TIME_SLICE);
#ifdef TESTFILE1
	int numb_failed_tests = test_simulation(std::string("RR"),scheduler1,9.5,1.75,15.25);//testdata1
#else
	int  numb_failed_tests= test_simulation(std::string("RR"),scheduler1,5.0,1.5,9.0);	//testdata2
#endif
	resetContainer(ready_Q);

	//SRTF
	Scheduler_SRTF  scheduler2(ready_Q);
#ifdef TESTFILE1
	numb_failed_tests += test_simulation(std::string("SRTF"),scheduler2,4.75,4.75,10.5);//testdata1
#else
	numb_failed_tests += test_simulation(std::string("SRTF"),scheduler2,3.00,0.5,7);//testdata2
//	numb_failed_tests += test_simulation(std::string("SRTF"),scheduler2,4.00,0.5,9);//testdata2
#endif
	resetContainer(ready_Q);

	//FIFO
	Scheduler_FIFO  scheduler3(ready_Q);
#ifdef TESTFILE1
	numb_failed_tests+= test_simulation(std::string("FIFO"),scheduler3,8.25,8.25,14);	//testdata1
#else
	numb_failed_tests += test_simulation(std::string("FIFO"),scheduler3,4.75,4.75,8.75);   //testdata2
#endif


	resetContainer(ready_Q);

	std::cout<<"numb_failed_tests = "<<numb_failed_tests<<std::endl;
	return numb_failed_tests;
}


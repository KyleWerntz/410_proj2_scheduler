/*
 * tester.cpp
 *
 *  Created on: Sep 11, 2019
 *      Author: keith
 */
#include <iostream>
#include <queue>
#include <vector>
#include <cmath>
#include <string>
#include "../includes/stats.h"
#include "../includes/tester.h"
#include "../includes/stats.h"

//returns true if expectedVal is withen tolerance of actualVal AND actualVal is a number
bool EXPECT_NEAR(std::string info, float expectedVal, float actualVal,float tolerance){
	float val = std::abs((expectedVal - actualVal));
	bool bret = (val<tolerance) && !std::isnan(actualVal);

	if (bret){
		PRINT2(info," PASSED TEST");
//		std::cout<<info<<" PASSED TEST"<<std::endl;
	}
	else{
		PRINT4(info<<" FAILED  expected=",std::to_string(expectedVal)," actual=",std::to_string(actualVal));
//		std::cout<<info<<" FAILED  expected="<<std::to_string(expectedVal)<<" actual="<<std::to_string(actualVal)<<std::endl;
	}
	return bret;
}

//creates a Stats object from data in finished_vector, pulls performance metrics from Stats object, and then
//runs the above test for  av_wait_time, av_response_time,  and av_turnaround_time
int verify_stats( std::string info, std::vector<PCB> &finished_vector, float av_wait_time,float av_response_time, float  av_turnaround_time){
	Stats myStats(finished_vector);

	int numb_failed_tests = ZERO_FAILED_TEST;

	if (!EXPECT_NEAR(info,av_wait_time,  myStats.get_av_wait_time(),TOLERANCE)) numb_failed_tests++;
	if (!EXPECT_NEAR(info,av_response_time,  myStats.get_av_response_time(),TOLERANCE)) numb_failed_tests++;
	if (!EXPECT_NEAR(info,av_turnaround_time,  myStats.get_av_turnaround_time(),TOLERANCE)) numb_failed_tests++;

	return numb_failed_tests;
}


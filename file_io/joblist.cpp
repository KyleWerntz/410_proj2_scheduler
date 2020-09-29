/*
 * Joblist.cpp
 *
 *  Created on: Sep 8, 2019
 *      Author: keith
 */

#include "../includes/file_io.h"
#include "../includes/joblist.h"


int Joblist::init(const char *filename) {
	retCode = loadData(filename);
	sortData(ARRIVAL_TIME);
	return retCode;
}

//returns true if its time for any job to be submitted
bool Joblist::has_ready_jobs(int currentTick) {
	int nextStartTime = peekNextStartTime();
	return (currentTick>= nextStartTime && nextStartTime>=0);
}

//returns  a job for submission
//then erases it from Joblist internal data structure
PCB Joblist::get_next_job(int currentTick){
	PCB p;
	if (has_ready_jobs(currentTick))
		p =getNext();

	return p;
}

//returns true if there are still jobs waiting to start
	//false otherwise
	bool Joblist::isEmpty(){
		return (peekNextStartTime() == NO_JOBS);
	}


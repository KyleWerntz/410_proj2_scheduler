#include <numeric>  
#include <math.h> 
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "../includes/file_io.h"
#include "../includes/constants.h"
#include "stdlib.h"


using namespace std;

//holds all the data read
vector<PCB> myVector;

//********************** private to this compilation unit **********************

//if myString does not contain a string rep of number returns o
//if int not large enough has undefined behaviour, very fragile
int stringToInt(const char *myString) {
	return atoi(myString);
}

const int MINIMUM_CHARS =7;
//don�t add this to header file, that way only functions withen this file can see it
//(for the most part) sort of like a private member function
int processData(std::ifstream &file, bool skipFirstLine=true) {
	std::string line;
	std::string token;
	PCB myStats;
	stringstream ss;

	while (!file.eof()) {

		std::getline(file, line); //get a line from the file 

		if (skipFirstLine){
			skipFirstLine=false;	//ensures we only skip 1 line
			continue;
		}

		//cheesy check to handle empty lines
		if(line.length()<MINIMUM_CHARS)
			continue;

		ss.str(line);

		//get rid of the old values
		//mymeasurement.clear();

		//!!!!!! NO ERROR CHECK HERE DONT ASSUMME PERFECT DATA 		!!!!!!
		//!!!!!! if any of the following fail retValue should		!!!!!!
		//!!!!!! be set to false, break out of loop, then return;	!!!!!!

		//get process_number
		if (std::getline(ss, token, CHAR_TO_SEARCH_FOR))
			myStats.process_number = stringToInt(token.c_str());

		//get start_time
		if ( std::getline(ss, token, CHAR_TO_SEARCH_FOR))
			myStats.arrival_time = stringToInt(token.c_str());

		//get cpu_time
		if( std::getline(ss, token, CHAR_TO_SEARCH_FOR)){
			myStats.required_cpu_time = stringToInt(token.c_str());
			myStats.remaining_cpu_time = stringToInt(token.c_str());
		}

		//get IO_time
		if (std::getline(ss, token, CHAR_TO_SEARCH_FOR))
			myStats.io_time = stringToInt(token.c_str());

		//finally add to vector (makes a COPY of myMeasurement)
		myVector.push_back(myStats);

		//clear stream so it will work for next read
		ss.clear();
	}
	return SUCCESS;
}

//**************************************************************

int loadData(const char* filename) {
	int iRet = FAIL;	//pessimism

	//open file
	ifstream myInFile;
	myInFile.open(filename);
	if (!myInFile.is_open())
		return COULD_NOT_OPEN_FILE;

	//processfile contents
	iRet = processData(myInFile);
	if (iRet != SUCCESS)
		return iRet;

	//close file
	if (myInFile.is_open())
		myInFile.close();

	return SUCCESS;
}

//sorting functions
bool sort_cpu_time(const PCB &measurement1, const PCB &measurement2) {
	return measurement1.remaining_cpu_time < measurement2.remaining_cpu_time;
}
bool sort_process_number(const PCB &measurement1, const PCB &measurement2) {
	return measurement1.process_number < measurement2.process_number;
}
bool sort_arrival_time(const PCB &measurement1, const PCB &measurement2) {
	return measurement1.arrival_time < measurement2.arrival_time;
}

//will sort according to user preference
void sortData(SORT_ORDER mySortOrder) {
	switch (mySortOrder) {
	case CPU_TIME:
		std::sort(myVector.begin(), myVector.end(), sort_cpu_time);
		break;
	case PROCESS_NUMBER:
		std::sort(myVector.begin(), myVector.end(), sort_process_number);
		break;
	case ARRIVAL_TIME:
		std::sort(myVector.begin(), myVector.end(), sort_arrival_time);
		break;
	default:
		break;
	}
}

//return the first struct in the vector
//then deletes it from the vector
PCB getNext() {
	PCB myFirst;

	if (!myVector.empty()) {
		myFirst = myVector[0];
		myVector.erase(myVector.begin());
	}
	return myFirst;
}

int size() {
	return myVector.size();
}

//returns when the next job starts without altering the container
int peekNextStartTime() {
	int iRet = NO_JOBS;
	if (!myVector.empty())
		iRet = myVector[0].arrival_time;

	return iRet;
}


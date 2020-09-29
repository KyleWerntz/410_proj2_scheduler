/*
 * Stats.cpp
 *
 *  Created on: Sep 10, 2019
 *      Author: keith
 */

#include "../includes/stats.h"


Stats::Stats(std::vector<PCB> &finished_vector): vec(&finished_vector) {
	Stats::av_response_time = get_av_response_time();
	Stats::av_turnaround_time = get_av_turnaround_time();
	Stats::av_wait_time = get_av_wait_time();
}

void Stats::showAllProcessInfo()	{
	for (int i = 0; i < vec->size(); i++)	{
		std::cout << "Process " << i+1 << "Required CPU time:" << vec->at(i).required_cpu_time
				<< " arrived:" << vec->at(i).arrival_time << " started:" << vec->at(i).start_time
				<< " finished:" << vec->at(i).finish_time << std::endl;
	}
}

float Stats::get_av_response_time()	{
	float avg_time = 0.0;

	for (int i = 0; i < vec->size(); i++)	{
		avg_time = avg_time + vec->at(i).start_time - vec->at(i).arrival_time;
	}
	avg_time = avg_time / vec->size();
	return avg_time;
}

float Stats::get_av_turnaround_time()	{
	float avg_time = 0.0;

		for (int i = 0; i < vec->size(); i++)	{
			avg_time = avg_time + vec->at(i).finish_time - vec->at(i).arrival_time;
		}
		avg_time = avg_time / vec->size();
		return avg_time;
}

float Stats::get_av_wait_time()	{
	float avg_time = 0.0;

		for (int i = 0; i < vec->size(); i++)	{
			avg_time = avg_time + vec->at(i).finish_time - vec->at(i).arrival_time - vec->at(i).required_cpu_time;
		}
		avg_time = avg_time / vec->size();
		return avg_time;
}

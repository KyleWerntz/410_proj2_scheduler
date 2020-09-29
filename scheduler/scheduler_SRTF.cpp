/*
 * SchedulerSRTF.cpp
 *
 *  Created on: Sep 10, 2019
 *      Author: keith
 *
 *      implements shortest remaining time first scheduling algorithm
 *     pre-emptive
 */

#include <algorithm>
#include <vector>
#include "../includes/scheduler_SRTF.h"

bool compare_cpu_time(PCB a, PCB b)	{
	return (a.required_cpu_time < b.required_cpu_time);
}

bool Scheduler_SRTF::time_to_switch_processes(int tick_count, PCB &p)	{
	sort();
	return Scheduler::time_to_switch_processes(tick_count, p);
}

void Scheduler_SRTF::sort()	{
	std::vector<PCB> v;
	for (int i = 0; i < ready_q->size(); i++)	{
		v.push_back(ready_q->front());
		ready_q->pop();
	}
	std::sort(v.begin(), v.end(), compare_cpu_time);

	for (int i = 0; i < v.size(); i++)	{
		ready_q->push(v.at(i));
	}
}

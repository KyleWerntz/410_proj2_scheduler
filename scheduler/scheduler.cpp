/*
 * scheduler.cpp
 *
 *  Created on: Sep 8, 2019
 *      Author: keith
 */

#include "../includes/scheduler.h"

bool Scheduler::isEmpty()	{
	return ready_q->empty();
}

PCB Scheduler::getNext()	{
	PCB p = ready_q->front();
	ready_q->pop();

	return p;
}

//STF doesn't have anything in it when it's adding the 2nd one???
void Scheduler::add(PCB p)	{
	if (!ready_q->empty() && p.process_number == ready_q->front().process_number)
		ready_q->pop();
	ready_q->push(p);
	sort();
}

// (required - remaining) % timeslice
bool Scheduler::time_to_switch_processes(int tick_count, PCB &p)	{
	if (p.remaining_cpu_time == 0)
		return true;
	else if (p.process_number == -5 && ready_q->size() > 0)
		return true;

	else if (preemptive)	{
		if (time_slice == -5)
			return !ready_q->empty() && p.remaining_cpu_time > ready_q->front().remaining_cpu_time;

		if (p.required_cpu_time != p.remaining_cpu_time)	{
			return (p.required_cpu_time - p.remaining_cpu_time) % time_slice == 0;
		}
	}
	else
		return p.remaining_cpu_time == 0;

	return false;
}


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
	return ready_q->front();
}

void Scheduler::add(PCB p)	{
	sort();
	ready_q->push(p);
}

bool Scheduler::time_to_switch_processes(int tick_count, PCB &p)	{
	if (preemptive)	{
		if (tick_count > time_slice)	{
			return true;
		}
	} else	{
		if (p.remaining_cpu_time == 0)	{
			return true;
		}
	}

	return false;
}

/*
 * simulator.cpp
 *
 *  Created on: Sep 11, 2019
 *      Author: keith
 *
 *      simulates processes being loaded and unloaded onto a CPU using a dispatcher and scheduler
 */
#include <string>
#include "../includes/simulator.h"
#include "../includes/joblist.h"
#include "../includes/dispatcher.h"
#include "../includes/scheduler.h"
#include "../includes/PCB.h"
#include "../includes/CPU.h"
#include "../includes/stats.h"

//simulates processes being loaded and unloaded onto a CPU using a dispatcher and scheduler
void simulate(const char* pSourceFile, Scheduler &s,std::vector<PCB> &finished_vector, int time_slice) {
	Scheduler *scheduler=&s;
	int tick_count 	= TIMER_BEGIN;

	Joblist joblist;
	int ret = joblist.init(pSourceFile);
	if (ret!= SUCCESS)
	{
			std::cout<<"joblist::init failed with retCode "<<ret<<std::endl;
			return;
	}

	CPU cpu;													//will hold currently executing process
	Dispatcher dispatch(cpu);						//responsible for swapping processes on and off the CPU

	//main process handling loop
	while(true){

		//get any jobs that are ready to run and add to scheduler
		while(joblist.has_ready_jobs(tick_count))
			scheduler->add(joblist.get_next_job(tick_count));

		//get a copy of the current job, if nothing is running
		//an uninitialized PCB is returned
		PCB currentJob = cpu.get_COPY_of_Current_Process();

		//see if its time to switch
		if (scheduler->time_to_switch_processes(tick_count, currentJob)){

			//if current job is valid then remove it
			if (dispatch.isValidJobOnCPU()){
					//pull current job off CPU
					PCB removed_job= dispatch.get_from_CPU();

					//is job finished?
					if (removed_job.remaining_cpu_time == 0){
						//job is finished. Add it to the completed vector
						//then record finish time (for metric calculations)
						removed_job.finish_time = tick_count;
						finished_vector.push_back(removed_job);
					} else{
						//job not finished, put it back on the ready_q to wait
						//for another turn on the CPU
						scheduler->add(removed_job);
					}
			}

			//any jobs to run?
			if(!scheduler->isEmpty()){
				//Yep, run one
				currentJob = scheduler->getNext();

				//you only want to set start_time the FIRST time a process is loaded
				//not every time its reloaded when running a pre-emptive scheduler
				if(currentJob.start_time == UNINITIALIZED)
					currentJob.start_time = tick_count;		//for metric calculations
				dispatch.put_on_CPU(currentJob);

				PRINT4("Current job is ",currentJob.process_number, " started:",currentJob.start_time );
			}
		}

		//time to exit?
		if(joblist.isEmpty() && scheduler->isEmpty() && currentJob.isEmpty() )
			break;


		//finally run the job for 1 tick
		if (dispatch.isValidJobOnCPU()){
			cpu.run();
			PRINT4("Running process ",std::to_string(currentJob.process_number)," ;tick_count=",std::to_string(tick_count));
		}
		else
			PRINT3("Current tick is ",tick_count, " Invalid CPU Job");

		//increment 1 clock tick
		tick_count++;
	}
}


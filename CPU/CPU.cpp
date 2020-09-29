/*
 * CPU.cpp
 *
 *  Created on: Sep 8, 2019
 *      Author: keith
 *
 *      simulates a CPU with a single core
 */

#include "../includes/CPU.h"

//move a process on CPU to run
	void CPU::put_process_on_core(PCB &pcb){

		//make sure there is nothing running on core before we put new process on
		if (current_Process!= NULL)
			throw std::logic_error("CPU::put_process_on_core called when there is still a running process on CPU");

		current_Process = &pcb;
	}

	//run for 1 tick
	void CPU::run(){
		if (current_Process == NULL)
					throw std::logic_error("CPU::run() called when there is no running process on CPU");

		current_Process->remaining_cpu_time--;
	}

	//lets get a COPY of private data or pass back an uninitialized PCB
	PCB CPU::get_COPY_of_Current_Process(){
		if (current_Process== NULL)
			return PCB();										//return uninitialized PCB
		else
			return PCB(*current_Process);		//return a copy of current_process
	}


	//will return the PCB thats currently on the core or an uninitialized PCB
	PCB CPU::get_process_off_core(){
			if (current_Process !=NULL){
				PCB tmp = *current_Process;
				current_Process = NULL;
				return PCB(tmp);//remove from CPU
			}else
				return PCB();
	}



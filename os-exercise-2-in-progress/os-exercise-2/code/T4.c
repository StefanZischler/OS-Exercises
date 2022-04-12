#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 5
struct process{
	int process_id;
	int arrival_time;
	int execution_time;
	int start_time;
};

void init_processes(struct process *);
void display(struct process *);
void display_average_waiting_time(struct process *);
void schedule_FCFS(struct process *);
void schedule_SJF(struct process *);
void schedule_LJF(struct process *);

int main()
{
	struct process processes[SIZE];	
	init_processes(processes);

	printf("Orignial input (processes)\n");
	display(processes);
	
	
	schedule_FCFS(processes);
	printf("Execution according to FCFS policy\n");
	display(processes);
	display_average_waiting_time(processes);
	

	schedule_SJF(processes);
	printf("Execution according to SJF policy\n");
	display(processes);
	display_average_waiting_time(processes);

	
	schedule_LJF(processes);
	printf("Execution according to LJF policy\n");
	display(processes);
	display_average_waiting_time(processes);	
	
}
void init_processes(struct process * input)
{
	srand(100);
	for(int i=0;i<SIZE;i++)
	{
		input[i].arrival_time = rand()%10;
		input[i].execution_time = rand()%10;
		input[i].process_id= i;
		input[i].start_time=-1;      
	}	
}
void display(struct process * input){
	printf("process<id, arr, exe, start>:");
	for(int i=0;i<SIZE;i++)
	{
		printf("<%d,%d,%d,%d> ",  input[i].process_id,
		 input[i].arrival_time,  input[i].execution_time, input[i].start_time);	
	}
	printf("\n");
}

void schedule_FCFS(struct process * arr)
{
	//TODO
	//initialize a process variable to hold processes
	struct process *process = (struct process *) arr;
	//initialize a temp variable 
	struct process temp;
	//switch the processes so they are in FCFS order
	for (int i = 0; i < SIZE; i++) {
		for (int j = i + 1; j < SIZE; j++) {
			if (process[i].arrival_time > process[j].arrival_time) {
				temp = process[i];
				process[i] = process[j];
				process[j] = temp; 
			}
		}
	}
	// printf("Not implemented Yet!\n");
}
void schedule_SJF(struct process * arr)
{
	//TODO
	//initialize a process variable to hold processes
	struct process *process = (struct process *) arr;
	//initialize a temp variable 
	struct process temp;
	//switch the processes so they are in SJF order
	for (int i = 0; i < SIZE; i++) {
		for (int j = i + 1; j < SIZE; j++) {
			if (process[i].execution_time > process[j].execution_time) {
				temp = process[i];
				process[i] = process[j];
				process[j] = temp; 
			}
		}
	}
	//printf("Not implemented Yet!\n");
}
void schedule_LJF(struct process * arr)
{
	//TODO
	//initialize a process variable to hold processes
	struct process *process = (struct process *) arr;
	//initialize a temp variable 
	struct process temp;
	//switch the processes so they are in LJF order
	for (int i = 0; i < SIZE; i++) {
		for (int j = i + 1; j < SIZE; j++) {
			if (process[i].execution_time < process[j].execution_time) {
				temp = process[i];
				process[i] = process[j];
				process[j] = temp; 
			}
		}
	}
	//printf("Not implemented Yet!\n");
}
void display_average_waiting_time(struct process * arr)
{
	//TODO
	//initialize a process variable to hold processes
	struct process *process = (struct process *) arr;
	//create waiting_time array with the waiting times for each process
	int waiting_time[SIZE];
	waiting_time[0]  = 0;
	//calculate the waiting time for each process
	for (int i = 1; i < SIZE; i++) {
		waiting_time[i] = process[i-1].execution_time - waiting_time[i-1];
		printf("Waiting time: %d\n", waiting_time[i]);
	}
	//calculate total waiting time of all processes
	int total_wait_time = 0;
	for (int i = 0; i < SIZE; i++) {
		total_wait_time += waiting_time[i];
	}
	//calculate average waiting time over all processes
	int avrg_time =(float)total_wait_time / (float)SIZE;
	//display average waiting time
	printf("Average waiting time: %d\n", avrg_time);
}

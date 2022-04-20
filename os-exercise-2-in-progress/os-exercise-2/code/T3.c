#include<stdio.h>
#include<stdlib.h>
#include<unistd.h> 
#include<pthread.h> 
#define SIZE 10000
#define NUM_THREADS 5
int result;
pthread_mutex_t lock;

struct args
{
	int *arr;
	int start;
	int end;
};

void * accumulate(void * in)
{
	//TODO implement accumulate
	struct args *args = (struct args *) in;
	int thread_num = pthread_self();
	//move start and end point
	args->start = thread_num * (SIZE/NUM_THREADS);
	args->end = thread_num * (SIZE/NUM_THREADS) + (SIZE/NUM_THREADS);
	//close lock
	pthread_mutex_lock(&lock);
	//add to gloabal variable 
	printf("Incrementing result. Result atm:%d\n", result);
	for (int i = args->start; i < args->end; ++i) {
		result += 1;
	}
	//open lock
	pthread_mutex_unlock(&lock);
	return NULL;
}
int main ()
{

	result=0;
	int arr[SIZE];    
	for(int i=0;i<SIZE;i++){
		arr[i]=1;
	}

	pthread_t threads[NUM_THREADS-1];
	struct args thread_args[NUM_THREADS-1];
	// TODO create a team of thread, each thread must take SIZE/NUM_THREADS to accumulate
	// TODO use struct args to pass arguments to the accumulate function  
	// TODO main thread must participate in the calculation
	// TODO make sure all threads finised
	
	
	//main thread calculation
	for (int i = (SIZE/NUM_THREADS * (NUM_THREADS-1)); i < SIZE; ++i) {
		result += 1;
	}
	//create threads with correct arguments
	for (int i = 0; i < NUM_THREADS -1; i++) {
		pthread_create(&threads[i], NULL, accumulate,thread_args);
	}

	//Wait for all threads to finish
	for (int i = 0; i < NUM_THREADS -1; i++) {
		pthread_join(threads[i], NULL);
	}
	//print result
	printf("Result is: %d\n", result);
}


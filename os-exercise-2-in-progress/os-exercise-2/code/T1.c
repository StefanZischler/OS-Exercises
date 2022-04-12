#include<stdio.h>
#include<sys/mman.h>
#include<stdlib.h>
#include <fcntl.h>
#include <unistd.h> 
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/stat.h>

#define SIZE 10000
#define NAME "/T1"

void swap(int *xp, int *yp);
void sort(int arr[], int size);

int main ()
{
 	int arr[SIZE];         
	for(int i=SIZE-1;i>=0;i--)
		if(i%2==0)
            arr[(SIZE-1)-i]=0;
		else
			arr[(SIZE-1)-i]=1;

	// TODO fork another process here
	// One process should calculate the median
	// The other process should calculate the mean
	// One process should communicate its value to the other process
	// The other process should print both calculated results
	// Hint use shm_open, ftrucate, mmap, and mumap to communicate over mapped files
	
	//name of the shared memory object
	//const char *name = "/T1";
	//test array
	/*
	for (int i = 0; i < 10; i++) {
		printf("Array at %d: %d\n", i, arr[i]);
	}*/
	//shared memory file decriptor
	int pid = fork();
	if (pid == 0) {
		//child proccess
		//print process ID
		printf("Child process ID: %d\n", getpid());
		//create shared memory file
		int fd;
		fd = shm_open(NAME, O_CREAT | O_RDWR, 0777);
		printf("fd: %d\n",fd);
		if (fd < 0) {
		//error message if file wasnt created
		printf("Error creating shared memory: %s\n",strerror(errno));
		exit(0);	
		} else {
			ftruncate(fd, 4096);
			float *mean = 0;
			double sum = 0;
			//calculate mean over array
			for (int i = 0; i < SIZE; i++) {
				sum += arr[i];
			}
			mean = mmap(0, 4096, PROT_READ|PROT_WRITE, MAP_SHARED,fd,0);
			*mean = (float)(sum / SIZE);
			munmap (mean, 4096);
			close(fd);
		}
	} else {
		//parent proccess
		//print proccess ID
		printf("Parent process ID: %d\n", getpid());
		//calculate median
		sort(arr, SIZE);
		double median = 0;
		if (SIZE % 2 == 0){
			median = (arr[(SIZE-1) / 2] + arr[SIZE / 2]) / 2.0;
		} else {
			median = arr[SIZE/2];
		}
		//wait for child to complete
		wait(NULL);
		//open shared memory
		int fd = shm_open(NAME, O_CREAT|O_RDWR, 777);
		if (fd < 0) {
		//error message if file wasnt created
		printf("Error creating shared memory: %s\n",strerror(errno));
		exit(0);	
		} else {
			float *mean = mmap(0, 4096, PROT_READ|PROT_WRITE, MAP_SHARED,fd,0);
			printf("Mean of array: '%f' \n",*mean);
			printf("Median of array: '%f' \n",median);
			munmap (0, 4096);
			//close shared file
			close(fd);
			//remove link
			shm_unlink(NAME);
		}
	}
	return 0;
}




void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void sort(int *arr, int size)
{
   int i, j;
   for (i = 0; i < size-1; i++)    
  
       // Last i elements are already in place   
       for (j = 0; j < size-i-1; j++) 
           if (arr[j] > arr[j+1])
              swap(&arr[j], &arr[j+1]);
}



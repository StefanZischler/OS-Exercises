#include<stdio.h>
#include<stdlib.h>
#include<unistd.h> 
#include<pthread.h> 
#define SIZE 10000

void swap(int *xp, int *yp);
void sort(int arr[], int size);
void *median(void *param); /*thread calls this function*/
double med; /*this data is shared by the threads*/

int main (){

        int arr[SIZE];    
        for(int i=SIZE-1;i>=0;i--)
                if(i%2==0)
                        arr[(SIZE-1)-i]=0;
                else
                        arr[(SIZE-1)-i]=1;
	// TODO implement you solution here
	// TODO a new thread here
        // One thread should calculate the median
        // The other thread should calculate the mean
	// One thread should display the result (mean, median)

        //calculate mean
        double mean = 0;
        double sum = 0;
        //calculate mean over array
        for (int i = 0; i < SIZE; i++) {
                sum += arr[i];
        }
        mean = sum / SIZE;

        //define thread and thread attributes
        pthread_t tid;
        pthread_attr_t attr; 
        //get the default attributes
        pthread_attr_init (&attr); 
        //create thread
        int *tidn = malloc(pthread_create (&tid, &attr, median, arr));
        //print Thread ID from main thread
        printf("Main Thread ID '%lu': \n",pthread_self());
        //wait for thread to exit
        pthread_join(tid, NULL);
        //print the results
        printf("Mean of array:'%f' \n",mean);
        printf("Median of array: '%f' \n",med);
        //free the allocated memory
        free(tidn);
        return 0;
}
//thread will start with this function
void *median(void *param) {
        int *arry;
        arry = param;
        sort(arry, SIZE);

        //print thread ID
        printf("Thread ID '%lu': \n",pthread_self());
        if (SIZE % 2 == 0){
                med = (arry[(SIZE-1) / 2] + arry[SIZE / 2]) / 2.0;
        } else {
                med = arry[SIZE/2];
        }
        pthread_exit(0);
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

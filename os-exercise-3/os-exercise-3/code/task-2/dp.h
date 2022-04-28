//#pragma once
//#ifndef DP_H
//#define DP_H

#include <pthread.h>

#define NUMBER 5
#define MAX_SLEEP_TIME 1

enum
{
    THINKING,
    HUNGRY,
    EATING
} state[NUMBER];

int thread_id[NUMBER];

// condition variables and associated mutex lock
pthread_cond_t cond_vars[NUMBER];
pthread_mutex_t mutex_lock;

void pickup_forks(int number);
void return_forks(int number);
void *philosopher(void *param);

//#endif 
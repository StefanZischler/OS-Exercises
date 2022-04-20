/**
 * bounded-buffer problem using the producer-consumer model
 * meant to be solved with counting semaphores and mutex locks
 * 
 * to compile: gcc -o T1 T1.c -lpthread
 * to run: ./T1 <duration> <producer threads> <consumer threads>
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 5
#define TRUE 1

typedef int buffer_item;
int insertPointer = 0;
int removePointer = 0;

buffer_item buffer[BUFFER_SIZE];
pthread_mutex_t mutex;
sem_t empty;
sem_t full;

int insert_item(buffer_item item);
int remove_item(buffer_item *item);

void *producer(void *param);
void *consumer(void *param);

int insert_item(buffer_item item)
{
    // TODO acquire "empty" semaphore and mutex lock

    buffer[insertPointer++] = item;
    insertPointer = insertPointer % BUFFER_SIZE;

    // TODO release mutex lock and "full" semaphore

    return 0;
}

int remove_item(buffer_item *item)
{
    // TODO acquire "full" semaphore and mutex lock

    *item = buffer[removePointer];
    buffer[removePointer++] = -1;
    removePointer = removePointer % BUFFER_SIZE;

    // TODO release mutex lock and "empty" semaphore

    return 0;
}

int main(int argc, char *argv[])
{
    int duration, producerThreads, consumerThreads;
    int i, j;

    if (argc != 4)
    {
        fprintf(stderr, "Useage: <duration> <producer threads> <consumer threads>\n");
        return -1;
    }

    duration = atoi(argv[1]);
    producerThreads = atoi(argv[2]);
    consumerThreads = atoi(argv[3]);

    // TODO initialize the synchronization tools

    srand(time(0));

    // create the producer and consumer threads
    for (i = 0; i < producerThreads; i++)
    {
        pthread_t tid;
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_create(&tid, &attr, producer, NULL);
    }

    for (j = 0; j < consumerThreads; j++)
    {
        pthread_t tid;
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_create(&tid, &attr, consumer, NULL);
    }

    // sleep for user specified time
    sleep(duration);
    return 0;
}

void *producer(void *param)
{
    buffer_item random;
    int r;

    while (TRUE)
    {
        r = rand() % 5;
        sleep(r);
        random = rand();

        if (insert_item(random))
            fprintf(stderr, "Error");

        printf("Producer produced: %d, buffer position: %d \n", random, (insertPointer + 4) % 5);
    }
}

void *consumer(void *param)
{
    buffer_item random;
    int r;

    while (TRUE)
    {
        r = rand() % 5;
        sleep(r);

        if (remove_item(&random))
            fprintf(stderr, "Error Consuming");
        else
            printf("Consumer consumed: %d, buffer position: %d \n", random, (removePointer + 4) % 5);
    }
}

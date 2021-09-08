#include    <pthread.h>
#include    <semaphore.h>
#include    <stdlib.h>
#include    <stdio.h>
#include    <unistd.h>

#define    N 2
#define    TRUE 1

int    buffer[N], in = 0, out = 0;
sem_t  empty, full, mutexC, mutexP;

void *producer(void *arg) {

   while(TRUE) {
       sleep(rand()%5);

       sem_wait(&empty);
       sem_wait(&mutexP);
    
       buffer[in] = rand() % 100;
       printf("Producing buffer[%d] = %d\n", in, buffer[in]);
       in= (in+1) % N;

       sem_post(&mutexP);
       sem_post(&full);
       
   }
}

void *consumer(void *arg) {

   while(TRUE) {
       
       sleep(rand()%5);
       sem_wait(&full);
       sem_wait(&mutexC);
       
       printf("Consuming buffer[%d] = %d\n", out, buffer[out]);
       out = (out+1) % N;
       
       sem_post(&mutexC);
       sem_post(&empty);
       
   }
}

int main(int argc, char *argv[ ]) {
    pthread_t cons, prod;

    sem_init(&mutexC, 0, 1);
    sem_init(&mutexP, 0, 1);
    sem_init(&empty, 0, N);
    sem_init(&full, 0, 0);
    
    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);
    
    pthread_exit(0);
}

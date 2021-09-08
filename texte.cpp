#include    <pthread.h>
#include    <semaphore.h>
#include    <stdlib.h>
#include    <unistd.h>
#include    <iostream>
#include    <list>

#define    TRUE 1
#define    N 2

using namespace std;

list<int> sharedList;

sem_t hasItems;
sem_t busy;

void *producer(void *arg) {

   while(TRUE) {
       
       sleep(rand()%5);

       sem_wait(&busy);
       int prod = rand() % 100;
       cout << "producing: " << prod << endl;
       sharedList.push_back(prod);
       sem_post(&hasItems);
       sem_post(&busy);
       
       
   }
}

void *consumer(void *arg) {

   while(TRUE) {
      
       sleep(rand()%5);

       sem_wait(&hasItems);
       sem_wait(&busy);
       
       if (!sharedList.empty()) {
           cout << "consuming: ";
           cout << sharedList.front() << endl;
           sharedList.pop_front();
       } else {
           cout << "not possible to consume" << endl;
       }
       sem_post(&busy);
   }
}

int main(int argc, char *argv[ ]) {
    pthread_t cons, prod;

    sem_init(&busy, 0, 0);
    sem_init(&hasItems, 0, 0);
   
    pthread_create(&cons, NULL, consumer, NULL);
    pthread_create(&prod, NULL, producer, NULL);
   
    
    pthread_exit(0);
}

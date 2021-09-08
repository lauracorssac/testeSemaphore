
#include    <pthread.h>
#include    <semaphore.h>
#include    <stdlib.h>
#include    <stdio.h>
#include    <unistd.h>
#include <iostream>
#include <list>
#include <string>

#include "NotificationManagerSimulator.hpp"
#include "ProfSessionManagerSimulator.hpp"

#define    TRUE 1

struct arg_struct {
    ProfSessionManagerSimulator *sessionManager;
    int notification;
};


ProfSessionManagerSimulator::ProfSessionManagerSimulator() {

    cout << "inicializando prof session" << endl;
    sem_init(&(this->freeCritialSession), 0, 1);
    sem_init(&(this->hasItems), 0, 0);

    ProfSessionManagerSimulator *args = (ProfSessionManagerSimulator *) malloc(sizeof(ProfSessionManagerSimulator *));
    args = this;

    //pthread_create(&(this->tid[0]), NULL, producer, (void *) args);
    pthread_create(&(this->tid[1]), NULL, consumer, (void *) args);
    //pthread_create(&(this->tid[2]), NULL, producer, (void *) args);

    cout << "return from pthread create" << endl;

    cout << "aqui" << endl;
}

void ProfSessionManagerSimulator::produceNewNotification(int notification) {

    struct arg_struct my_args;
    my_args.sessionManager = this;
    my_args.notification = notification;

    struct arg_struct *args = (struct arg_struct *) malloc(sizeof(struct arg_struct));
    *args = my_args;

    pthread_create(&(this->tid[notification]), NULL, this->producer, (void *) args);
}

void * ProfSessionManagerSimulator::producer(void *arg) {

    cout << "init producer thread" << endl;
    struct arg_struct *my_arg_struct = (struct arg_struct *) arg;
    ProfSessionManagerSimulator *_this = my_arg_struct->sessionManager;
    sleep(rand()%5);

    sem_wait(&((*_this).freeCritialSession));

    cout << "producing: " << my_arg_struct->notification << endl;
    _this->sharedList.push_back(my_arg_struct->notification);

    sem_post(&(_this->freeCritialSession));
    sem_post(&(_this->hasItems));

    free(arg);
    cout << "returning from producer" <<endl;
    return 0;

}

void *ProfSessionManagerSimulator::consumer(void *arg) {

    cout << "init consumer thread" << endl;
    ProfSessionManagerSimulator *_this = (ProfSessionManagerSimulator *) arg;

   while(TRUE) {
       cout << "dentro do while" << endl;
       sleep(rand()%5);
       sem_wait(&((*_this).hasItems));
       cout << "has items" << endl;
       sem_wait(&((*_this).freeCritialSession));
       cout << "SC is free" << endl;

       if (!_this->sharedList.empty()) { // this shouldn't be needed, but better safe than sorry
           int consumedItem = _this->sharedList.front();
           cout << "consuming: ";
           cout << consumedItem << endl;
           _this->sharedList.pop_front();
           NotificationManagerSimulator::sendNotification(consumedItem);
       } else {
           cout << "not possible to consume" << endl;
       }

       sem_post(&(_this->freeCritialSession));

   }

   free(arg);
   return 0;
}
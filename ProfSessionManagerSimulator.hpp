
#ifndef PROFSESSIONMANAGERSIMULATOR_HPP
#define PROFSESSIONMANAGERSIMULATOR_HPP

#include    <pthread.h>
#include    <semaphore.h>
#include    <stdlib.h>
#include    <stdio.h>
#include    <unistd.h>
#include <list>

using namespace std;

class ProfSessionManagerSimulator {

public:
    /* Initializes */
    ProfSessionManagerSimulator();
    static void *producer(void *arg);
    static void *consumer(void *arg);
    pthread_t tid[10];
    sem_t  hasItems, freeCritialSession;
    list<int> sharedList;
    void produceNewNotification(int notification);
};

#endif
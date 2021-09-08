#include    <pthread.h>
#include    <semaphore.h>
#include    <stdlib.h>
#include    <stdio.h>
#include    <unistd.h>
#include <iostream>
#include <list>
#define    N 2
#define    TRUE 1

using namespace std;

class MySecondClass {
    public:
        /* Initializes */
    MySecondClass();
    MySecondClass(int in, int out);
        static void *producer(void *arg);
        static void *consumer(void *arg);
    int in, out;
    pthread_t tid[3];
    sem_t  hasItems, freeCritialSession;
    list<int> sharedList;
};


MySecondClass::MySecondClass() {
    
}

MySecondClass::MySecondClass(int in, int out) {
    this->in = in;
    this->out = out;

    sem_init(&(this->freeCritialSession), 0, 1);
    sem_init(&(this->hasItems), 0, 0);

    MySecondClass *args = (MySecondClass *) malloc(sizeof(MySecondClass *));
    args = this;
    
    pthread_create(&(this->tid[0]), NULL, producer, (void *) args);
    pthread_create(&(this->tid[1]), NULL, consumer, (void *) args);
    pthread_create(&(this->tid[2]), NULL, producer, (void *) args);

    
    pthread_exit(0);
}

void * MySecondClass::producer(void *arg) {
    
    cout << "init producer thread" << endl;
    MySecondClass *_this = (MySecondClass *) arg;

    
   while(TRUE) {
       sleep(rand()%5);

       sem_wait(&((*_this).freeCritialSession));
       int prod = rand() % 100;
       cout << "producing: " << prod << endl;
       _this->sharedList.push_back(prod);

       sem_post(&(_this->freeCritialSession));
       sem_post(&(_this->hasItems));
       
   }
}

void *MySecondClass::consumer(void *arg) {
    
    cout << "init consumer thread" << endl;
    MySecondClass *_this = (MySecondClass *) arg;

   while(TRUE) {

       sleep(rand()%5);
       sem_wait(&((*_this).hasItems));
       sem_wait(&((*_this).freeCritialSession));
       
       if (!_this->sharedList.empty()) { // this shouldn't be needed, but better safe than sorry
           cout << "consuming: ";
           cout << _this->sharedList.front() << endl;
           _this->sharedList.pop_front();
       } else {
           cout << "not possible to consume" << endl;
       }
       
       sem_post(&(_this->freeCritialSession));
       
   }
}



int main(int argc, char *argv[ ]) {
    
    MySecondClass *myClass = new MySecondClass(1,0);
    //MyClass *myClass = new MyClass::MyClass();
}

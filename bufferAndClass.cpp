#include    <pthread.h>
#include    <semaphore.h>
#include    <stdlib.h>
#include    <stdio.h>
#include    <unistd.h>
#include <iostream>

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
    pthread_t tid[2];
    sem_t  empty, full, mutexC, mutexP;
    int buffer[2];
};


MySecondClass::MySecondClass() {
    
}
MySecondClass::MySecondClass(int in, int out) {
    this->in = in;
    this->out = out;


    sem_init(&(this->mutexC), 0, 1);
    sem_init(&(this->mutexP), 0, 1);
    sem_init(&(this->empty), 0, N);
    sem_init(&(this->full), 0, 0);
    
    MySecondClass *args = (MySecondClass *) malloc(sizeof(MySecondClass *));
    args = this;
    
    pthread_create(&(this->tid[0]), NULL, producer, (void *) args);
    pthread_create(&(this->tid[1]), NULL, consumer, (void *) args);
    
    cout << "alo" << endl;
    
    pthread_exit(0);
}


void * MySecondClass::producer(void *arg) {
    
    cout << "init producer thread" << endl;
    MySecondClass *_this = (MySecondClass *) arg;

    
   while(TRUE) {
       sleep(rand()%5);

       cout << "alo2" << endl;
       sem_wait(&((*_this).empty));
       cout << "alo3" << endl;
       sem_wait(&((*_this).mutexP));
       cout << "alo4" << endl;
    
       _this->buffer[_this->in] = rand() % 100;
       printf("Producing buffer[%d] = %d\n", _this->in, _this->buffer[_this->in]);
       _this->in= (_this->in +1) % N;

       sem_post(&(_this->mutexP));
       sem_post(&(_this->full));
       
   }
}

void *MySecondClass::consumer(void *arg) {
    
    cout << "init consumer thread" << endl;
    MySecondClass *_this = (MySecondClass *) arg;

   while(TRUE) {
       
       cout << "alo2 cons" << endl;
       sleep(rand()%5);
       sem_wait(&((*_this).full));
       cout << "alo3 cons" << endl;
       sem_wait(&((*_this).mutexC));
       cout << "alo4 cons" << endl;
       
       printf("Consuming buffer[%d] = %d\n", _this->out, _this->buffer[_this->out]);
       _this->out = (_this->out+1) % N;
       
       sem_post(&(_this->mutexC));
       sem_post(&(_this->empty));
       
   }
}



int main(int argc, char *argv[ ]) {
    
    MySecondClass *myClass = new MySecondClass(1,0);
    //MyClass *myClass = new MyClass::MyClass();
}

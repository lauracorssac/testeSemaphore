#include    <pthread.h>
#include    <semaphore.h>
#include    <stdlib.h>
#include    <unistd.h>
#include    <iostream>
#include    <list>

#define    TRUE 1
#define    N 2

using namespace std;

list<int> listaCompartilhada;

sem_t  vazio, cheio, mutexC, mutexP;

void *produtor(void *arg) {

   while(TRUE) {
       sleep(rand()%5);

       sem_wait(&vazio);
       sem_wait(&mutexP);
       int producao = rand() % 100;
       cout << "produzindo:" << producao << endl;
       listaCompartilhada.push_back(producao);

       sem_post(&mutexP);
       sem_post(&cheio);
       
   }
}

void *consumidor(void *arg) {

   while(TRUE) {
      sleep(rand()%5);

       sem_wait(&cheio);
       sem_wait(&mutexC);
       
       if (!listaCompartilhada.empty()) {
           cout << "consumindo: ";
           cout << listaCompartilhada.front() << endl;
           listaCompartilhada.pop_front();
       } else {
           cout << "não rolou consumir" << endl;
       }
       sem_post(&mutexC);
       sem_post(&vazio);
   }
}

int main(int argc, char *argv[ ]) {
    pthread_t cons, prod;

    sem_init(&mutexC, 0, 1);
    sem_init(&mutexP, 0, 1);
    sem_init(&vazio, 0, N);
    sem_init(&cheio, 0, 0);
    
    pthread_create(&prod, NULL, produtor, NULL);
    pthread_create(&cons, NULL, consumidor, NULL);
    
    pthread_exit(0);
}

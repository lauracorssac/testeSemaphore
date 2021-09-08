#include <iostream>
#include <list>
#include <pthread.h>
#include <unistd.h>

#include "NotificationManagerSimulator.hpp"
#include "ProfSessionManagerSimulator.hpp"

#define    TRUE 1

using namespace std;

int main(int argc, char *argv[ ]) {
    
    ProfSessionManagerSimulator *myClass = new ProfSessionManagerSimulator();
    cout << "SOCOOOORRROOOO" << endl;
    NotificationManagerSimulator *notificationManager = new NotificationManagerSimulator(myClass);
    notificationManager->newNotificationSentByUser(2);


    sleep(5);
    notificationManager->newNotificationSentByUser(3);
    sleep(5);
    notificationManager->newNotificationSentByUser(4);


    pthread_exit(NULL);
}

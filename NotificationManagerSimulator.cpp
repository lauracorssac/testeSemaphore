#include    <stdlib.h>
#include    <unistd.h>
#include <iostream>
#include <list>
#include <string>

#include "NotificationManagerSimulator.hpp"
#include "ProfSessionManagerSimulator.hpp"

NotificationManagerSimulator::NotificationManagerSimulator() { }

NotificationManagerSimulator::NotificationManagerSimulator(ProfSessionManagerSimulator *profSessionManager){

    cout << "inicializando notification manager" << endl;
    this->profSessionManager = profSessionManager;
}

void NotificationManagerSimulator::sendNotification(int notification) {
    cout << "sending notification: ";
    cout << to_string(notification) << endl;
}
void NotificationManagerSimulator::newNotificationSentByUser(int notification) {
    cout << "new notification sent by user" <<endl;
    this->profSessionManager->produceNewNotification(notification);
}

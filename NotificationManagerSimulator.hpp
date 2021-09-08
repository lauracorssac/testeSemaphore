#ifndef NOTIFICATIONMANAGERSIMULATOR_HPP
#define NOTIFICATIONMANAGERSIMULATOR_HPP

#include "ProfSessionManagerSimulator.hpp"

class NotificationManagerSimulator {
private:
    ProfSessionManagerSimulator *profSessionManager;

public:
    NotificationManagerSimulator();
    NotificationManagerSimulator(ProfSessionManagerSimulator *profSessionManager);

    //esse é chamado pela prof session
    static void sendNotification(int notification);

    //esse método chama o da Prof session
    void newNotificationSentByUser(int notification);

};

#endif
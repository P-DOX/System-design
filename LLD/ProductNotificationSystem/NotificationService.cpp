#include <bits/stdc++.h>
using namespace std;

class NotificationStrategy {
    public:
        virtual void sendNotification(string msg) = 0;
};

class EmailNotificationStrategy : public NotificationStrategy {
    public:
        void sendNotification(string msg) override {
            cout<<"Semding Email : "<<msg<<endl;
        }
};

class MessageNotificationStrategy : public NotificationStrategy {
    public:
        void sendNotification(string msg) override {
            cout<<"Semding Message : "<<msg<<endl;
        }
};

class NotificationService {
    public:
        NotificationStrategy* notificationStrategy;
        NotificationService(NotificationStrategy* strategy) : notificationStrategy(strategy) {}
        void sendNotification(string msg) {
            notificationStrategy->sendNotification(msg);
        }
};

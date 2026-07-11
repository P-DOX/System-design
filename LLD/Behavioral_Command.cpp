#include <bits/stdc++.h>
using namespace std;

class Device {
    public:
    virtual void turnON() = 0;
    virtual void turnOFF() = 0;
};

class TV : public Device {
    public:
        void turnON() override {
            cout<<"TV turning ON\n";
        }

        void turnOFF() override {
            cout<<"TV turning OFF\n";
        }
};

class Speaker : public Device {
    public:
        void turnON() override {
            cout<<"Speaker turning ON\n";
        }

        void turnOFF() override {
            cout<<"Speaker turning OFF\n";
        }
};

class Command {
    public:
        Device* device;
        Command(Device* d) : device(d) {}
        virtual void execute() = 0;
};

class turnONCommand : public Command {
    public:
        turnONCommand(Device* device) : Command(device) {}

        void execute() override {
            device->turnON();
        }
};

class turnOFFCommand : public Command {
    public:
        turnOFFCommand(Device* device) : Command(device) {}

        void execute() override {
            device->turnOFF();
        }
};

class RemoteController {
    public:
        Command* command;

        void setCommand(Command* command) {
            this->command = command;
        }

        void pressButton() {
            command->execute();
        }
};

int main() {
    Device* tv = new TV();
    Device* speaker = new Speaker();

    Command* tvON = new turnONCommand(tv);
    Command* tvOFF = new turnOFFCommand(tv);
    Command* speakerON = new turnONCommand(speaker);
    Command* speakerOFF = new turnOFFCommand(speaker);
    
    RemoteController* rc = new RemoteController();
    rc->setCommand(tvON);
    rc->pressButton();

    rc->setCommand(tvOFF);
    rc->pressButton();

    rc->setCommand(speakerON);
    rc->pressButton();

    rc->setCommand(speakerOFF);
    rc->pressButton();
}
#include <bits/stdc++.h>
using namespace std;

class Responsibility {
    public:
        Responsibility* nextResponsibility;
        Responsibility(Responsibility* nextResponsibility) : nextResponsibility(nextResponsibility) {}
        virtual void execute() = 0;
};

class LowResponsibility : public Responsibility {
    public:
        LowResponsibility(Responsibility* res) : Responsibility(res) {}
        void execute() override {
            cout<<"Executing LowResponsibility\n";
            if(nextResponsibility)
                nextResponsibility->execute();
        }
};

class MediumResponsibility : public Responsibility {
    public:
        MediumResponsibility(Responsibility* res) : Responsibility(res) {}
        void execute() override {
            cout<<"Executing MediumResponsibility\n";
            nextResponsibility->execute();
        }
};

class HighResponsibility : public Responsibility {
    public:
        HighResponsibility(Responsibility* res) : Responsibility(res) {}
        void execute() override {
            cout<<"Executing HighResponsibility\n";
            nextResponsibility->execute();
        }
};

int main() {

    Responsibility* r = new HighResponsibility(new MediumResponsibility(new LowResponsibility(nullptr)));
    r->execute();

}
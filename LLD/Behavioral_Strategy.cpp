#include <bits/stdc++.h>
using namespace std;

class Strategy {
    public:
        virtual void coverDistance() = 0;
};

class WalkingStrategy : public Strategy {
    public:
        void coverDistance() override {
            cout<<"coverDistance using walking strategy\n";
        }
};

class RunningStrategy : public Strategy {
    public:
        void coverDistance() override {
            cout<<"coverDistance using running strategy\n";
        }
};

class CrawlingStrategy : public Strategy {
    public:
        void coverDistance() override {
            cout<<"coverDistance using crawling strategy\n";
        }
};

class Person {
    private:
        Strategy* strategy;

    public:
        void setStrategy(Strategy* strategy) {
            this->strategy = strategy;
        }

        void move() {
            this->strategy->coverDistance();
        }
};

int main() {
    Strategy* s1 = new WalkingStrategy();
    Strategy* s2 = new RunningStrategy();
    Strategy* s3 = new CrawlingStrategy();
    
    Person* p1 = new Person();
    p1->setStrategy(s1);
    p1->move();

    p1->setStrategy(s2);
    p1->move();

    p1->setStrategy(s3);
    p1->move();    
}
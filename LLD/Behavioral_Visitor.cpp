#include <bits/stdc++.h>

using namespace std;
class Employee;
class Staff;

class Visitor {
    public:
        virtual void visit(Employee* e) = 0;
        virtual void visit(Staff* s) = 0;
};

class User {
    public:
        virtual void accept(Visitor* visitor) = 0;
} ;

class Employee : public User {
    public:
        string name;
        int age;

        Employee(string name, int age) : name(name), age(age) {}

        void accept(Visitor* visitor) override {
            visitor->visit(this);
        }
};

class Staff : public User {
    public:
        string name;
        int age;

        Staff(string name, int age) : name(name), age(age) {}

        void accept(Visitor* visitor) override {
            visitor->visit(this);
        }
};

class XMLDump : public Visitor {
    public:
        void visit(Employee* e) override {
            cout<<"<employee>"<<e->name<<" "<<e->age<<"<\\employee>"<<endl;
        }

        void visit(Staff* s) override {
            cout<<"<staff>"<<s->name<<" "<<s->age<<"<\\staff>"<<endl;
        }
};


int main() {
    Employee* e1 = new Employee("John", 34);
    Employee* e2 = new Employee("Mike", 54);

    Staff* s1 = new Staff("Kevin", 37);
    Staff* s2 = new Staff("Olga", 44);

    vector<User*>v = {e1, e2, s1, s2};
    Visitor* vis = new XMLDump();
    for(auto x : v) {
        x->accept(vis);
    }
}
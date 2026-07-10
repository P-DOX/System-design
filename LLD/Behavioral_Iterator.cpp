#include<bits/stdc++.h>
using namespace std;

class Employee;

class Iterator {
    public:
        virtual bool hasNext() = 0;
        virtual Employee* next() = 0;
        virtual int getCurrentIndex() = 0;
        virtual int getSize() = 0;
};

class Iterable {
    public:
        virtual Iterator* CreateIterator() = 0;
};

class Employee{
    public:
        string name;
        int salary;
        Employee(string name, int salary) : name(name), salary(salary) {}
};

class EmployeeIterator : public Iterator {
    public:
        int currIdx;
        vector<Employee*> eps;
        int size;

        EmployeeIterator(vector<Employee*> eps) {
            this->eps = eps;
            this->size = eps.size();
            this->currIdx = 0;
        }

        bool hasNext() override {
            if(currIdx >= size)
                return false;
            return true;
        }

        Employee* next() override {
            if(currIdx >= size) {
                cout<<"<Last Idx>\n";
                return nullptr;
            }
            else{
                return eps[currIdx++];
            }
        }

        int getCurrentIndex() override {
            return currIdx;
        }

        int getSize() override {
            return size;
        }
};

class Company : public Iterable {
    public : 
        vector<Employee*> eps;
        Company(vector<Employee*>eps) {
            this->eps = eps;
        }

        Iterator* CreateIterator() override {
            return new EmployeeIterator(eps);
        }
};

int main() {
    Employee* ep1 = new Employee("Rahul", 10000);
    Employee* ep2 = new Employee("Amit", 23000);
    Employee* ep3 = new Employee("Dileep", 50000);
    Employee* ep4 = new Employee("Vinay", 76000);
    Employee* ep5 = new Employee("Sejal", 34000);

    Company* cp = new Company({ep1, ep2, ep3, ep4, ep5});
    Iterator* it = cp->CreateIterator();
    cout<<"Size : "<<it->getSize()<<endl;

    while(it->hasNext()) {
        auto t = it->next();
        cout<<t->name<<" "<<t->salary<<endl;
    }


}
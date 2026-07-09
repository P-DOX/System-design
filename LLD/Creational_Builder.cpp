#include <bits/stdc++.h>

using namespace std;

class Student {
    public:
        string name;
        int id;
        string class_;
        int age;

        void display() {
            cout<<name<<" "<<class_<<" "<<id<<" "<<age<<endl;
        }
};

class StudentBuilder {
    private:
        Student* student;
    public:
        StudentBuilder() {
            student = new Student();
        }

        StudentBuilder* SetName(string name) {
            this->student->name = name;
            return this;
        }

        StudentBuilder* SetID(int id) {
            this->student->id = id;
            return this;
        }

        StudentBuilder* SetClass(string class_) {
            this->student->class_ = class_;
            return this;
        }

        StudentBuilder* SetAge(int age) {
            this->student->age = age;
            return this;
        }

        Student* build() {
            return student;
        }
};

int main() {
    Student* boy = StudentBuilder().SetAge(23)->SetClass("class 12th")->SetID(47)->SetName("Idiot Kumar")->build();
    boy->display();
}
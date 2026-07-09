#include <iostream>
using namespace std;

static int count = 0;
class Singleton {
    private:
        static Singleton* instance;
        Singleton() {
            cout<<"Constructor called "<<count++<<endl;
        }
    
    public:
        static Singleton* getInstance() {
            if(instance == NULL) {
                instance = new Singleton();
            }
            return instance;
        }
};

Singleton* Singleton::instance = nullptr;

int main() {
    cout<<"Singleton Design Pattern\n";

    // Cannot call private constructor
    // Singleton* obj = new Singleton();

    Singleton* obj1 = Singleton::getInstance();
    cout<<obj1<<endl;

    Singleton* obj2 = Singleton::getInstance();
    cout<<obj2<<endl;
}
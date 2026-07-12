#include <bits/stdc++.h>
#include "NotificationService.cpp"
#include "users.cpp"

using namespace std;
class Product {
    public:
        int id;
        string name;
        int qty;
        int min_th;
        Observable* backInStockTopic;
        Observable* lowInventoryTopic;
        Product(int id, string name, int qty) {
            this->id = id;
            this->name = name;
            this->qty = qty;
            this->min_th = 2;
            backInStockTopic = new Observable();
            lowInventoryTopic = new Observable();
        }

        void buy(int qty) {
            if(this->qty < qty) {
                cout<<"Not enough\n";
                return ;
            }

            this->qty -= qty;
            cout<<"Bought "<<this->name<<" "<<qty<<" | qty available : "<<this->qty<<endl;
            notify();
        }

        void refill(int qty) {
            bool flag = this->qty <= this->min_th;
            this->qty = qty;
            if(flag)
                notify();
        }

        void notify() {
            if(this->qty <= this->min_th) {
                string msg = "LowInventory for product " + this->name + "current qty " + to_string(this->qty);
                lowInventoryTopic->notify(msg);
            }
            else {
                string msg = "backInStock for product " + this->name + "current qty " + to_string(this->qty);
                backInStockTopic->notify(msg);
            }

        }
};

class Shop {
    public:
        int id;
        string name;
        vector<Product*> productList;
        vector<Staff*> staffList;
        vector<Customer*> customerList;
        Shop(int id, string name) : id(id), name(name) {
            Product* p1 = new Product(1, "Soap", 6);
            Product* p2 = new Product(2, "Towel", 3);
            Product* p3 = new Product(3, "Toffee", 6);
            Product* p4 = new Product(4, "Mouse", 3);
            Product* p5 = new Product(5, "Tea", 7);
            productList = {p1, p2, p3, p4, p5};

            Customer* c1 = new Customer(1, "Rahul C");
            Customer* c2 = new Customer(2, "Amit C");
            Customer* c3 = new Customer(3, "Rohit C");
            customerList = {c1, c2, c3};

            Staff* s1 = new Staff(1, "Dileep S");
            Staff* s2 = new Staff(2, "Divya S");
            Staff* s3 = new Staff(3, "Vinay S");
            staffList = {s1, s2, s3};

            p1->backInStockTopic->addObserver(c1);
            p1->backInStockTopic->addObserver(c2);

            p1->lowInventoryTopic->addObserver(s1);
        }

        vector<Product*> getProducts() {
            return productList;
        }

        vector<Customer*> getCustomers() {
            return customerList;
        }

        vector<Staff*> getStaffs() {
            return staffList;
        }  

        void setUp() {
            
        }
        
        void buyProduct(Product* p, int qty) {
            p->buy(qty);
        }

        void refillProduct(Product* p, int qty) {
            p->refill(qty);
        }

        void printEverything() {
            cout<<"<<PRODUCTS>>\n";
            for(auto p : productList) {
                cout<<p->id <<" "<<p->name<<" "<<p->qty<<endl;
            }
            cout<<"<<STAFFS>>\n";
            for(auto s : staffList) {
                cout<<s->id <<" "<<s->name<<endl;
            }
            cout<<"<<CUSTOMERS>>\n";
            for(auto c : customerList) {
                cout<<c->id <<" "<<c->name<<endl;
            }
        }
};
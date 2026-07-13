#include <bits/stdc++.h>
#include "Users.cpp"
#include "Inventory.cpp"
using namespace std;

class PaymentStrategy {
    public:
        virtual void pay(int amount) = 0;
};

class PaymentStrategyByCard : public PaymentStrategy {
    public:
        void pay(int amount) override {
            cout<<"Paid by Card\n";
        }
};

class PaymentStrategyByUPI : public PaymentStrategy {
    public:
        void pay(int amount) override {
            cout<<"Paid by UPI\n";
        }
};

class PaymentService {
    public:
        PaymentStrategy* strategy;
        PaymentService(PaymentStrategy* strategy) : strategy(strategy) {}

        void pay(int amount) {
            strategy->pay(amount);
            cout<<"Amount paid : "<<amount<<endl;
        }
};


class Invoice {
    public:
        int total_amount;
        int otherCharges;
        Invoice(int total_amount) : total_amount(total_amount), otherCharges(24) {}

        void generateInvoice(int id) {
            cout<<"Invoice generated for orderID <"<<id<<"> of amount : "<<(total_amount+ otherCharges)<<endl;
        }
};

class OrderSummary {
    public:
        int id;
        Customer* cus;
        map<Product*, int> orderList;
        Invoice* invoice;
        Store* st;

        OrderSummary(int id, Customer* cs, Store* st) {
            this->id = id;
            this->invoice = new Invoice(0);
            this->cus = cs;
            this->st = st;
        }

        void addItem(Product* p, int q) {
            orderList[p] += q;
            this->invoice->total_amount += (p->price * q);
        }
        void printOrderList() {
            for(auto it = orderList.begin(); it!= orderList.end(); it++) {
                cout<<it->first->name<<" price : "<<it->first->price<<" x "<<it->second<<" = "<<(it->first->price*it->second)<<endl;
            }
        }

        int getTotal() {
            this->printOrderList();
            this->invoice->generateInvoice(id);
            return this->invoice->total_amount;
        } 
};

class DeliveryService {
    public:
        DeliveryAgent* da;
        Customer* cus;
        OrderSummary* os;

        DeliveryService(DeliveryAgent* da, Customer* cus, OrderSummary* os) : da(da), cus(cus), os(os) {}

        void send() {
            cout<<"Order id: "<<os->id<<" delivered by "<<da->name<<" to customer : "<<cus->name<<endl;
        }
};

class ShoppingManagementService {
    public:
        int orderIdCount;
        map<int, OrderSummary*> orderList;
        PaymentService* ps;
        vector<DeliveryAgent*> das;

        ShoppingManagementService() {
            orderIdCount= 0;
            ps = new PaymentService(new PaymentStrategyByCard());
            das = {
                new DeliveryAgent(1, "DA-1"),
                new DeliveryAgent(2, "DA-2"),
                new DeliveryAgent(3, "DA-3"),
                new DeliveryAgent(4, "DA-4"),
                new DeliveryAgent(5, "DA-5")
            };
        }

        Store* getStoreToShopFrom(vector<Store*> stores, Customer* cs) {
            // can have multipel strategy to decide the best possible store to order from based on users location
            return stores[0];
        }

        void buyFromStore(Customer* cs, Store* st, Product* p, int q) {
            st->reserveProduct(p->id, q);
            st->buyProduct(p->id, q);
            if(orderList.find(cs->id) == orderList.end()) {
                OrderSummary* os = new OrderSummary(orderIdCount++, cs, st);
                orderList[cs->id] = os;
            }
            orderList[cs->id]->addItem(p, q);
        }

        void refillToStore(Store* st, int id, int q) {
            st->refillProduct(id, q);
        }

        DeliveryAgent* getDeliveryAgentForOrder(vector<DeliveryAgent*> das, OrderSummary* os) {
            return das[0];
        }

        DeliveryAgent* getDeliveryAgentForOrder(OrderSummary* os) {
            return getDeliveryAgentForOrder(das, os);
        }

        void payForOrder(Customer* cs) {
            OrderSummary* os = orderList[cs->id];
            int totalAmount = os->getTotal();
            ps->pay(totalAmount);
        }

        void assignDelivery(Customer* cs) {
            OrderSummary* os = orderList[cs->id];
            DeliveryAgent* da = getDeliveryAgentForOrder(os);
            DeliveryService* ds = new DeliveryService(da, cs, os);
            ds->send();
        }
};

class Application {
    public:
        vector<Location*> servicableLocation;
        vector<Customer*> customerList;
        vector<Store*> stores;
        ShoppingManagementService* sms;
        Application() {
            Customer* c1 = new Customer(1, "customer-1");
            Customer* c2 = new Customer(2, "customer-2");
            Customer* c3 = new Customer(3, "customer-3");
            this->customerList = {c1, c2, c3};
            this->servicableLocation = {new Location("12345")};
            Store* s = new Store(new Staff(1, "Staff-1"));
            this->stores = {s};
            this->sms = new ShoppingManagementService();
        }

        void placeOrder() {
            auto cs = customerList[0];
            Store* s = sms->getStoreToShopFrom(stores, cs);
            auto pl = s->getProductList();
            sms->buyFromStore(cs, s, pl[0], 3);
            sms->payForOrder(cs);
            sms->assignDelivery(cs);
        }
};


int main() {
    Application* ap = new Application();
    ap->placeOrder();
}
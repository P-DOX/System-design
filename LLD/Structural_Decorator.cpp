#include <bits/stdc++.h>
using namespace std;

class Pizza {
    public:
    virtual string getDescription() = 0;
    virtual int getPrice() = 0;
};

class BasePizza : public Pizza {
    public:
        string getDescription() override {
            return " <Base Pizza $5> ";
        }

        int getPrice() override {
            return 5;
        }
};

class PizzaDecorator : public Pizza {
    public:
        Pizza* base;
        PizzaDecorator(Pizza* bp) : base(bp) {}

        string getDescription() override {
            return base->getDescription();
        }

        int getPrice() override {
            return base->getPrice();
        }
};

class FarmFreshTopping : public PizzaDecorator {
    public:
        FarmFreshTopping(Pizza* bp) : PizzaDecorator(bp) {}

        string getDescription() override {
            return "< FarmFreshTopping $2>" + base->getDescription();
        }

        int getPrice() override {
            return 2 + base->getPrice();
        }
};

class MargheritaTopping : public PizzaDecorator {
    public:
        MargheritaTopping(Pizza* bp) : PizzaDecorator(bp) {}

        string getDescription() override {
            return "< MargheritaTopping $3>" + base->getDescription();
        }

        int getPrice() override {
            return 3 + base->getPrice();
        }
};

class ChieckenTopping : public PizzaDecorator {
    public:
        ChieckenTopping(Pizza* bp) : PizzaDecorator(bp) {}

        string getDescription() override {
            return "< ChieckenTopping $4>" + base->getDescription();
        }

        int getPrice() override {
            return 4 + base->getPrice();
        }
};


int main() {
    Pizza* p1 = new BasePizza();
    cout<<"Description : "<<p1->getDescription()<<endl;
    cout<<"Price : $"<<p1->getPrice()<<"\n\n";

    Pizza* p2 = new FarmFreshTopping(p1);
    cout<<"Description : "<<p2->getDescription()<<endl;
    cout<<"Price : $"<<p2->getPrice()<<"\n\n";

    Pizza* p3 = new ChieckenTopping(new MargheritaTopping(p2));
    cout<<"Description : "<<p3->getDescription()<<endl;
    cout<<"Price : $"<<p3->getPrice()<<"\n\n";


}
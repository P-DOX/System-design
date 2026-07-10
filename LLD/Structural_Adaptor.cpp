#include <bits/stdc++.h>
using namespace std;

class LegacyPrinter {
    public:
        void printDocument(string msg) {
            cout<<"Printed using Legacy printer <"<<msg<<"> \n";
        }
};

class Printer {
    public:
        virtual void print(string doc) = 0;
};

class Modernprinter : public Printer{
    public:
        void print(string doc) override {
            cout<<"Printed using Modern printer <"<<doc<<"> \n";
        }
};

class LegacyPrinterAdaptor : public Printer{
    public:
        LegacyPrinter* lPrinter;
        LegacyPrinterAdaptor(LegacyPrinter* lp) : lPrinter(lp) {}
        void print(string doc) override {
            lPrinter->printDocument(doc);
        }
};

class Client {
    public:
        Printer* printer;
        Client(Printer* p) : printer(p) {}
        void printDocument(string doc) {
            printer->print(doc);
        }
};


int main() {
    Printer* mp = new Modernprinter();
    Client* cl1 = new Client(mp);
    string doc = "Hello this is the test docuemnt!";
    cl1->printDocument(doc);

    LegacyPrinter* lp = new LegacyPrinter();
    Printer* lpp = new LegacyPrinterAdaptor(lp);
    Client* cl2 = new Client(lpp);
    cl2->printDocument(doc);

}
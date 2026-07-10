#include <bits/stdc++.h>
using namespace std;

class FileSystem {
    public:
        virtual void display() = 0;
};

class File : public FileSystem {
    public:
        string fname;
        int fsize;
        File(string name, int s) : fname(name), fsize(s) {}

        void display() override {
            cout<<"File : "<<fname<< "  Size : "<<fsize<<endl;
        }
};

class Directory : public FileSystem {
    public:
        string dname;
        vector<FileSystem*> fs;
        Directory(string name) : dname(name) {}

        void addDirectory(FileSystem* f) {
            fs.push_back(f);
        }

        void display() override {
            cout<<"---------------------------------------------------------\n";
            cout<<"Directory : "<<dname<<endl;
            for(auto d : fs) {
                d->display();
            }
            cout<<"---------------------------------------------------------\n";
        } 
};

int main() {
    File* f1 = new File("a.txt", 123);
    File* f2 = new File("b.txt", 456);

    Directory* d1 = new Directory("d1");
    d1->addDirectory(f1);
    d1->addDirectory(f2);

    Directory* d2 = new Directory("d2");
    File* f3 = new File("c.txt", 45677);
    d2->addDirectory(d1);
    d2->addDirectory(f3);

    d2->display();
}
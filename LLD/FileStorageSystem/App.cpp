#include <bits/stdc++.h>
#include "FileStorageService.cpp"
using namespace std;

class App {
    public:
        FileStorageService* fs;
        App() {
            fs = new FileStorageService();
        }

        LocalDirectory* getCurrentDir() {
            return fs->getCurrentDir();
        }

        void createFileInCurrDir(string fname, int fsize) {
            fs->createFileInCurrDir(fname, fsize);
        }

        void createDirInCurr(string fname) {
            fs->createDirInCurr(fname);
        }

        void printDir() {
            fs->printDir();
        }
};


int main() {

    App* app = new App();
    app->createFileInCurrDir("f1.txt", 23);
    app->createFileInCurrDir("f2.txt", 2345);
    app->createFileInCurrDir("f3.txt", 2323);
    app->createFileInCurrDir("f4.txt", 5623);
    app->createDirInCurr("folder");
    app->printDir();
}
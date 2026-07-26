#include <bits/stdc++.h>
using namespace std;

class LocalFileSystemNode {
    public:
        virtual void getFileInfo() = 0;
};

class LocalFile : public LocalFileSystemNode {
    public:
        string fname;
        int fsize;
        LocalFile(string fname, int fsize) : fname(fname), fsize(fsize) {}

        void getFileInfo() override {
            cout<<" Local File info : "<<fname<<" "<<fsize<<endl;
        }
};

class LocalDirectory : public LocalFileSystemNode {
    public:
        string fname;
        int fsize;
        vector<LocalFileSystemNode*> lst;

        LocalDirectory(string fname) : fname(fname) {
            fsize = 0;
            lst = {};
        }

        void getFileInfo() override {
            cout<<"Local Directory info : "<<fname<<" "<<fsize<<endl;
            for(auto l : lst) {
                l->getFileInfo();
            }
        }

        void createFile(string fname, int fsize) {
            lst.push_back(new LocalFile(fname, fsize));
            this->fsize += fsize;
            cout<<"Local File created in "<<this->fname<<" detail : "<<fname<<" : "<<fsize<<endl;
        }

        void createDir(string fname) {
            lst.push_back(new LocalDirectory(fname));
            cout<<"Local Dir created in "<<this->fname<<" detail : "<<fname<<endl;
        }
};

class Observer {
    public:
        virtual void update(string fname, int fsize) = 0;
};

class Observable {
    public:
        vector<Observer*> obLst;
        void addObserver(Observer* ob) {
            obLst.push_back(ob);
        }

        void removeObserver(Observer* ob) {
            erase(obLst, ob);
        }

        virtual void notify(string fname, int fsize = 0) = 0;
};

class LocalFileStorageService : public Observable {
    public:
        LocalDirectory* baseDir;
        LocalDirectory* currDir;
        LocalFileStorageService() {
            baseDir = new LocalDirectory("/");
            currDir = baseDir;
        }

        LocalDirectory* getCurrentDir() {
            return currDir;
        }

        void createDirInCurr(string fname) {
            currDir->createDir(fname);
            notify(fname);
        }

        void createFileInCurr(string fname, int fsize) {
            currDir->createFile(fname, fsize);
            notify(fname, fsize);
        }

        void notify(string fname, int fsize = 0) override {
            for(auto ob : obLst) {
                ob->update(fname, fsize);
            }
        }
};

class RemoteFileSystemNode {
    public:
        virtual void getFileInfo() = 0;
};

class RemoteFile : public RemoteFileSystemNode {
    public:
        string fname;
        int fsize;
        RemoteFile(string fname, int fsize) : fname(fname), fsize(fsize) {}

        void getFileInfo() override {
            cout<<" Remote File info : "<<fname<<" "<<fsize<<endl;
        }
};

class RemoteDirectory : public RemoteFileSystemNode {
    public:
        string fname;
        int fsize;
        vector<RemoteFileSystemNode*> lst;

        RemoteDirectory(string fname) : fname(fname) {
            fsize = 0;
            lst = {};
        }

        void getFileInfo() override {
            cout<<"Remote Directory info : "<<fname<<" "<<fsize<<endl;
            for(auto l : lst) {
                l->getFileInfo();
            }
        }

        void createFile(string fname, int fsize) {
            lst.push_back(new RemoteFile(fname, fsize));
            this->fsize += fsize;
            cout<<"Remote File created in "<<this->fname<<" detail : "<<fname<<" : "<<fsize<<endl;
        }

        void createDir(string fname) {
            lst.push_back(new RemoteDirectory(fname));
            cout<<"Remote Dir created in "<<this->fname<<" detail : "<<fname<<endl;
        }
};

class RemoteFileStorageService : public Observer {
    public:
        RemoteDirectory* baseDir;
        RemoteDirectory* currDir;
        RemoteFileStorageService() {
            baseDir = new RemoteDirectory("/");
            currDir = baseDir;
        }

        RemoteDirectory* getCurrentDir() {
            return currDir;
        }

        void createDirInCurr(string fname) {
            currDir->createDir(fname);
        }

        void createFileInCurr(string fname, int fsize) {
            currDir->createFile(fname, fsize);
        }

        void update(string fname, int fsize) override {
            cout<<"Notification received for "<<fname<<" : "<<fsize<<endl;
            if(fsize) {
                createFileInCurr(fname, fsize);
            }
            else {
                createDirInCurr(fname);
            }
        }
};

class FileStorageService {
    public:
        LocalFileStorageService* localService;
        RemoteFileStorageService* remoteService;

        FileStorageService() {
            localService = new LocalFileStorageService();
            remoteService = new RemoteFileStorageService();
            localService->addObserver(remoteService);
        }

        LocalDirectory* getCurrentDir() {
            return localService->getCurrentDir();
        }

        void createFileInCurrDir(string fname, int fsize) {
            localService->createFileInCurr(fname, fsize);
        }

        void createDirInCurr(string fname) {
            localService->createDirInCurr(fname);
        }

        void printDir() {
            cout<<"LOCAL\n";
            localService->baseDir->getFileInfo();
            cout<<"REMOTE\n";
            remoteService->baseDir->getFileInfo();
        }
};
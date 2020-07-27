#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "URLBreakdown.h"
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
using namespace std;

class MainWindow:public URLBreakdown
{
    private:
        string URL;
        int endVolume;
        string mangaName;
        int mangaVolume;
        int mangaNumber;
        int endNumber=0;

        string toSystem;
        ofstream output;
        bool bOut=0;

    public:
        MainWindow();
        void Download();
        virtual ~MainWindow();

    protected:
        int GoToSystem();
        int EndNumberSearch(string);
        void VolumeAndNumber();
        string SearchURL(string);
        void eraseString(string &,string);
        string SearchAddress(string);
};

#endif // MAINWINDOW_H

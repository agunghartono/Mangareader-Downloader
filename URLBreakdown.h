#ifndef URLBREAKDOWN_H
#define URLBREAKDOWN_H
#include <iostream>
#include <string>
using namespace std;

class URLBreakdown
{
public:
    URLBreakdown(){}
    URLBreakdown(string);
    void URLEntry(string);
    char *URLPrint(int nAr);
    virtual ~URLBreakdown();
    int size();

private:
    struct line
    {
        string node;
        line *ptr;
    };
    line *head=nullptr;

    string URL;
    string sTemp;

    void URLStoring(string);
    void URLDelete();
};

#endif // URLBREAKDOWN_H

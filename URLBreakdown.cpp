#include "URLBreakdown.h"

URLBreakdown::URLBreakdown(string URLin) //constructor
{
    URLEntry(URLin);
}

URLBreakdown::~URLBreakdown() //destructor
{
    URLDelete();
}

void URLBreakdown::URLEntry(string URLEnter) //public
{
    if(head)
    {
        URLDelete();
    }

    URL=URLEnter;
    unsigned int i=0;

    int prev=0;
    while(URL[i])
    {
        if (URL[i]=='/'||i==URL.size()-1)
        {
            if(URL[i+1]!='/')
            {
                sTemp=URL.substr(prev,i-prev+1);
                for (unsigned int a=sTemp.size();a>0;a--)
                {
                    if(sTemp[a-1]=='/') sTemp.erase(a-1,1);
                }
                URLStoring(sTemp);
                prev=i;
            }
        }
        i++;
    }
}

char *URLBreakdown::URLPrint(int nAr) //public
{
    line *pointer;

    if (!head) return nullptr;
    pointer=head;
    for (int a=0;a<nAr;a++)
    {
        pointer=pointer->ptr;

        if (!pointer) return nullptr;
    }
    return &pointer->node[0];
}

int URLBreakdown::size() //public
{
    int num=1;
    if (!head) return 0;
    else
    {
        line *pointer;
        pointer=head;
        while(pointer->ptr)
        {
            pointer=pointer->ptr;
            num++;
        }
    }
    return num;
}

void URLBreakdown::URLStoring(string store) //private
{
    line *newLine=new line;
    line *pointer;

    newLine->node=store;
    newLine->ptr=nullptr;

    if(!head)
    {
        head=newLine;
    }
    else
    {
        pointer=head;
        while(pointer->ptr)
        {
            pointer=pointer->ptr;
        }
        pointer->ptr=newLine;
    }
}

void URLBreakdown::URLDelete() //private
{
    if (head)
    {
        line *pointer=head;
        line *next;
        while (pointer)
        {
            next=pointer->ptr;
            delete pointer;
            pointer=next;
        }
        head=nullptr;
    }
}





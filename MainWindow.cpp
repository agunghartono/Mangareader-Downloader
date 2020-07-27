#include "MainWindow.h"

MainWindow::MainWindow()
{
    Download();
}

void MainWindow::Download()
{
    do //URL Entry
    {
        cout<<"URL: ";
        getline(cin,URL);
        URLEntry(URL);
    }while (size()<4&&size()>6);

    mangaVolume=atoi(URLPrint(3));//get mangaVolume

    if (URLPrint(4)=='\0') mangaNumber=1;//get mangaNumber
    else mangaNumber=atoi(URLPrint(4));

    do
    {
        cout<<"End Manga Volume: "; //endVolume Entry
        cin>>endVolume;
        cin.ignore();
    }while (endVolume<mangaVolume);

    mangaName=URLPrint(2); //get mangaName
    mangaName[0]=toupper(mangaName[0]);
    for (unsigned int i=0;i<mangaName.size();i++)
    {
        if (mangaName[i]=='-')
        {
            mangaName[i]=' '; mangaName[i+1]=toupper(mangaName[i+1]);
        }
    }


    int escape=0;
    while (!escape)
    {
        if (endVolume==mangaVolume)
        {
            while (endVolume==mangaVolume&&!escape)
            {
                escape=GoToSystem();
            } break;
        }else escape=GoToSystem();
    }
}

void MainWindow::VolumeAndNumber()
{
    if (mangaNumber>=endNumber)
    {
        mangaVolume++;
        mangaNumber=1;
        endNumber=0;
    } else
    {
        mangaNumber++;
    }
    URL="http://www.mangareader.net/";
    URL+=URLPrint(2);
    URL+="/";
    URL+=to_string(mangaVolume);
    if(mangaNumber!=1)
    {
        URL+="/";
        URL+=to_string(mangaNumber);
    }
}

int MainWindow::EndNumberSearch(string dir)
{
    string entry;
    ifstream input (dir);
    if (!input.fail())
    {
        while (input>>entry)
        {
            if(entry=="</select>") break;
        } input>>entry; input>>entry;
        input.close();
        eraseString(entry,"</div>");
        endNumber=atoi(entry.c_str());
        return 0;
    } else return 1;
}

int MainWindow::GoToSystem()
{
    int sreturn=0;
    toSystem = "aria2c -d \"D:\\MANGA\\"; //Download note
    toSystem += mangaName;
    toSystem += "\" -o note -x 5 ";
    toSystem += URL;
    sreturn=system(toSystem.c_str());

    if (!sreturn)
    {
        string sInput; //search URL image & print it
        sInput = "D:\\MANGA\\";
        sInput += mangaName;
        sInput += "\\note";

        if (!endNumber)
        {
            EndNumberSearch(sInput); //set endNumber
        }

        if (bOut==0) //set Output to print
        {
            string sOutput;
            sOutput = "D:\\MANGA\\";
            sOutput += mangaName;
            sOutput += "\\book.txt";
            output.open(sOutput);
            bOut=1;
        }
        output<<mangaNumber<<" "; //print first URL (bottom)
        output<<SearchURL(sInput)<<endl;

        mangaNumber++;
        output<<mangaNumber<<" ";
        output<<SearchAddress(sInput)<<endl; //renew URL -->print second URL (up)

        VolumeAndNumber();

        string deletenote="del \"";
        deletenote+=sInput;
        deletenote+="\"";
        system(deletenote.c_str());

    }


    return sreturn;
}

string MainWindow::SearchAddress(string dir)
{
    string entry;
    ifstream input (dir);
    if (!input.fail())
    {
        while (input>>entry)
        {
            if(entry=="document['pu']") break;
        } input>>entry; input>>entry;

        eraseString(entry,"\'");
        eraseString(entry,";");
        input.close();
        return entry;
    } else return "\0";
}

string MainWindow::SearchURL(string dir)
{
    string entry;
    ifstream input (dir);
    if (!input.fail())
    {
        while (input>>entry)
        {
            if(entry=="id=\"img\"") break;
        } input>>entry; input>>entry; input>>entry;

        eraseString(entry,"\"");
        eraseString(entry,"src=");
        input.close();
        return entry;
    } else return "\0";
}

void MainWindow::eraseString (string &data, string del)
{
    if (del.size()!=1)
    {
        unsigned int n=del.size();
        for (unsigned int i=data.size();i>0;i--)
        {
            if (data[i-1]==del[n-1]&& data[i-2]==del[n-2])
            {
                unsigned int m=i; unsigned int o=n;
                while (data[m-1]==del[o-1]&&o!=0)
                {
                    m--;o--;
                }
                if (o==0) {data.erase(m,n);}
            }
        }
    }
    if (del.size()==1)
    {
        for (unsigned int i=data.size();i>0;i--)
        {
            if(data[i-1]==del[0]) data.erase(i-1,1);
        }
    }
}

MainWindow::~MainWindow()
{
    //dtor
}

#include<iostream>
#include<fstream>
 
using namespace std;

class EncDec 
{
    private:
        string magic = "";

    public:
        
        EncDec();
        bool CreateFile(string);
        bool WriteFile(string);
        bool EncFile(string);
        bool DecFile(string);
        bool DeleteFile(string);

};

EncDec::EncDec()
{
    magic = "%$#$^&&^*%";
}

bool EncDec::CreateFile(string fname)
{
    fstream fcreate;
    fstream fcheck;

    fcheck.open(fname);

    if(fcheck)
    {
        fcheck.close();
        fcreate.close();
        return false;
    }
    else
    {
        fcreate.open(fname, ios::out);
        fcheck.close();
        fcreate.close(); 
        return true;
    }
}

bool EncDec::WriteFile(string fname)
{
    string data = "";
    fstream fcheck;
    fstream fwrite;

    fcheck.open(fname);

    if(fcheck)
    {
        cout<<endl<<"Enter the Data :"<<endl;
        getline(cin, data);
        getline(cin, data);

        fwrite.open(fname, ios::app);
        fwrite<<data+" ";
        fcheck.close();
        fwrite.close();

        return true;
    }
    else
    {
        fcheck.close();
        fwrite.close();
        return false;
    }
}

bool EncDec::EncFile(string fname)
{
    int i = 0;
    int j = 0;
    int countlines = 0;
    string *line = new string[1000];
    string str = "";
    string readmagic = "";
    string chkmagic = "";
    string checkenc = "";
    fstream fcheck;
    fstream fcwfile;
    
    fcheck.open(fname);

    if(fcheck)
    {
        ifstream inobj(fname);
        getline(inobj, readmagic);
        inobj.close();
        inobj.open(fname);

        while(getline(inobj, line[countlines]))
        {
            // cout<<countlines;
            // cout<<line[countlines]<<endl;
            countlines++;
        }
        
        fcheck.close();
        inobj.close();

        for(i = 0; i < 10; i++)
        {
            chkmagic[i] = readmagic[i];
        }

        for(i = 0; i < 10; i++)
        {
            if(chkmagic[i] != this->magic[i])
            {
                break;
            }
        }
        if(i == 10)
        {
            cout<<endl<<"File already encrypted !!!"<<endl;
            delete []line;
            return false;
        }

        for(i = 0; i < countlines; i++)
        {
            str = line[i];
            for(j = 0; j < str.length(); j++)
            {
                str[j] = str[j]+3;
            }

            // if(countlines == 1)
            // {
            //     fcwfile.open(fname, ios::out);
            //     fcwfile<<this->magic+str;
            // }
            if(i == 0)
            {
                fcwfile.open(fname, ios::out);
                fcwfile<<this->magic+str<<endl;
            }
            // else if(i == countlines-1)
            // {
            //     fcwfile<<str;
            // }
            else
            {
                fcwfile<<str<<endl;
            }
        }

        fcwfile.close();
        delete []line;
        return true;
    }
    else
    {
        delete []line;
        return false;
    }
}

bool EncDec::DecFile(string fname)
{
    int i = 0;
    int j = 0;
    int k = 0;
    int countlines = 0;
    string *line = new string[1000];
    string str = "";
    string chkmagic = "";
    char *withoutmagic = new char[50000];
    fstream cwfile;
    fstream fcheck;

    ifstream chkmyenc(fname);

    getline(chkmyenc, chkmagic);
    chkmyenc.close();

    fcheck.open(fname);

    if(fcheck)
    {
        for(i = 0; i < 10; i++)
        {
            if(chkmagic[i] != this->magic[i])
            {
                break;
            }
        }

        if(i == 10)
        {
            ifstream inobj(fname);

            while(getline(inobj, line[countlines]))
            {
                countlines++;
            }

            for(i = 0; i < countlines; i++)
            {
                str = line[i];

                if(i == 0)
                {
                    for(j = 0, k = 10; k < str.length(); j++, k++)
                    {
                        str[k] = str[k] - 3;
                        withoutmagic[j] = str[k];
                    }
                    cwfile.open(fname, ios::out);
                    cwfile<<withoutmagic<<endl;
                }
                else
                {
                    for(j = 0; j < str.length(); j++)
                    {
                        str[j] = str[j] - 3;
                    }
                    cwfile<<str<<endl;
                }
            }

            // for(i = 10, j = 0; i < str.length(); i++, j++)
            // {
            //     str[i] = str[i] - 7;
            //     withoutmagic[j] = str[i];
            // }

            // cwfile.open(fname, ios::out);
            // cwfile<<withoutmagic;
            // cwfile.close();

            delete []withoutmagic;
            delete []line;
            return true;
        }
        else
        {
            if(i != 10)
            {
                cout<<endl<<"File already decripted !!!"<<endl;
            }

            delete []withoutmagic;
            delete []line;
            fcheck.close();
            return false;
        }
    }
    else
    {
        cout<<endl<<"File does not exists !!!"<<endl;
        delete []withoutmagic;
        delete []line;
        return false;
    }
}

bool EncDec::DeleteFile(string fname)
{
    fstream fcheck;

    fcheck.open(fname);

    if(fcheck)
    {
        fcheck.close();
        remove(fname.c_str());
        return true;
    }
    else
    {
        return false;
    }
}

class StartEncDec
{
    public:

        void Start();
    
};

void StartEncDec::Start()
{   
    EncDec edobj;
    bool bRet = false;
    string filename;
    string data = "";
    char iChoice;
    cout<<endl<<"Hello Welcome to File Encryption and Decryption application..."<<endl<<endl<<"Enter 1 to Create a file"<<endl<<"Enter 2 to Write in a file"<<endl<<"Enter 3 to Encrypt a file"<<endl<<"Enter 4 to Decrypt a file"<<endl<<"Enter 5 to Delete a file"<<endl<<"Enter 6 to Exit an Application"<<endl<<">_";
    cin>>iChoice;

    switch(iChoice)
    {
        case '1':
            cout<<"Enter the file name to create a file : "<<endl;
            cin>>filename;
            bRet = false;

            bRet = edobj.CreateFile(filename);

            if(bRet == true)
            {
                cout<<endl<<"File Created Successfully..."<<endl;
            }
            else
            {
                cout<<endl<<"File already exists !!!"<<endl;
            }

            Start();
        break;

        case '2':
            cout<<"Enter the file name : "<<endl;
            cin>>filename;
            bRet = false;

            bRet = edobj.WriteFile(filename);

            if(bRet == true)
            {
                cout<<endl<<"Data written successfully into the file..."<<endl<<endl;
            }
            else
            {
                cout<<endl<<"File does not exists !!!"<<endl<<endl;
            }

            Start();
        break;

        case '3':
            cout<<"Enter the file name : "<<endl;
            cin>>filename;
            bRet = false;

            bRet = edobj.EncFile(filename);

            if(bRet == true)
            {
                cout<<endl<<"File Encryption Successful..."<<endl;
            }
            else
            {
                cout<<"File Encryption Unsuccessful !!!"<<endl;
            }

            Start();
        break;

        case '4':
            cout<<"Enter the file name : "<<endl;
            cin>>filename;
            bRet = false;

            bRet = edobj.DecFile(filename);

            if(bRet == true)
            {
                cout<<endl<<"File Decryption Successful..."<<endl;
            }
            else
            {
                cout<<"File Decryption Unsuccessful !!!"<<endl;
            }

            Start();
        break;

        case '5':
            cout<<"Enter the file name : "<<endl;
            cin>>filename;
            bRet = false;

            bRet = edobj.DeleteFile(filename);

            if(bRet == true)
            {
                cout<<endl<<"File deleted successfully..."<<endl;
            }
            else
            {
                cout<<endl<<"File does not exists !!!"<<endl;
            }

            Start();

        break;

        case '6':
            cout<<"Thank you for using our Application :)"<<endl;
            system("exit");
        break;

        default:
            cout<<endl<<"Invalid option selected !!!"<<endl<<endl;
            Start();
        break;
    }
}

int main()
{
    StartEncDec start;
    start.Start();

    return 0;
}

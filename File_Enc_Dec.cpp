#include<iostream>
#include<fstream>
using namespace std;

class EncDec 
{
    private:
        string magic = "";

    public:
        
        EncDec();
        bool createFile(string);
        bool writeFile(string);
        bool encFile(string);
        bool decFile(string);
        bool deleteFile(string);
};

EncDec::EncDec()
{
    this->magic = "%$#$^&&^*%";
}

/* 
##############################################################################
##
##  Function name : createFile
##  Input : string
##  Output : bool
##  Description : It is used to create a file.
##  Author : Vaibhav Tukaram Gaikwad
##  Date : 26-10-2022
##
##############################################################################
*/

bool EncDec::createFile(string fname)
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

/* 
##############################################################################
##
##  Function name : writeFile
##  Input : string
##  Output : bool
##  Description : It is used to write into the file.
##  Author : Vaibhav Tukaram Gaikwad
##  Date : 26-10-2022
##
##############################################################################
*/

bool EncDec::writeFile(string fname)
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

/* 
##############################################################################
##
##  Function name : encFile
##  Input : string
##  Output : bool
##  Description : It is used to encrypt a file.
##  Author : Vaibhav Tukaram Gaikwad
##  Date : 26-10-2022
##
##############################################################################
*/

bool EncDec::encFile(string fname)
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
                str[j] = str[j]-5;
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

/* 
##############################################################################
##
##  Function name : decFile
##  Input : string
##  Output : bool
##  Description : It is used to decrypt an encrypted file.
##  Author : Vaibhav Tukaram Gaikwad
##  Date : 26-10-2022
##
##############################################################################
*/

bool EncDec::decFile(string fname)
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
                        str[k] = str[k] + 5;
                        withoutmagic[j] = str[k];
                    }
                    cwfile.open(fname, ios::out);
                    cwfile<<withoutmagic<<endl;
                }
                else
                {
                    for(j = 0; j < str.length(); j++)
                    {
                        str[j] = str[j] + 5;
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

/* 
##############################################################################
##
##  Function name : deleteFile
##  Input : string
##  Output : bool
##  Description : It is used to delete a file.
##  Author : Vaibhav Tukaram Gaikwad
##  Date : 26-10-2022
##
##############################################################################
*/

bool EncDec::deleteFile(string fname)
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

        void start();
    
};

/* 
##############################################################################
##
##  Function name : start
##  Input : None
##  Output : None
##  Description : It is used to start file encryption decryption application.
##  Author : Vaibhav Tukaram Gaikwad
##  Date : 26-10-2022
##
##############################################################################
*/

void StartEncDec::start()
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

            bRet = edobj.createFile(filename);

            if(bRet == true)
            {
                cout<<endl<<"File Created Successfully..."<<endl;
            }
            else
            {
                cout<<endl<<"File already exists !!!"<<endl;
            }

            start();
        break;

        case '2':
            cout<<"Enter the file name : "<<endl;
            cin>>filename;
            bRet = false;

            bRet = edobj.writeFile(filename);

            if(bRet == true)
            {
                cout<<endl<<"Data written successfully into the file..."<<endl<<endl;
            }
            else
            {
                cout<<endl<<"File does not exists !!!"<<endl<<endl;
            }

            start();
        break;

        case '3':
            cout<<"Enter the file name : "<<endl;
            cin>>filename;
            bRet = false;

            bRet = edobj.encFile(filename);

            if(bRet == true)
            {
                cout<<endl<<"File Encryption Successful..."<<endl;
            }
            else
            {
                cout<<"File Encryption Unsuccessful !!!"<<endl;
            }

            start();
        break;

        case '4':
            cout<<"Enter the file name : "<<endl;
            cin>>filename;
            bRet = false;

            bRet = edobj.decFile(filename);

            if(bRet == true)
            {
                cout<<endl<<"File Decryption Successful..."<<endl;
            }
            else
            {
                cout<<"File Decryption Unsuccessful !!!"<<endl;
            }

            start();
        break;

        case '5':
            cout<<"Enter the file name : "<<endl;
            cin>>filename;
            bRet = false;

            bRet = edobj.deleteFile(filename);

            if(bRet == true)
            {
                cout<<endl<<"File deleted successfully..."<<endl;
            }
            else
            {
                cout<<endl<<"File does not exists !!!"<<endl;
            }

            start();

        break;

        case '6':
            cout<<"Thank you for using our Application :)"<<endl;
            system("exit");
        break;

        default:
            cout<<endl<<"Invalid option selected !!!"<<endl<<endl;
            start();
        break;
    }
}

int main()
{
    StartEncDec start;
    start.start();

    return 0;
}
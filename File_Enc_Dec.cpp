#include<iostream>
#include<fstream>

using namespace std;

class EncDec 
{
    private:
        string magic = "";

    public:
        
        EncDec()
        {
            magic = "%$#$^&&^*%";
        }

        bool CreateFile(string fname)
        {
            fstream fcreate;
            fstream fcheck;

            fcheck.open(fname);

            if(fcheck)
            {
                return false;
            }
            else
            {
                fcreate.open(fname, ios::out);  
                return true;
            }
        }

        bool WriteFile(string fname)
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

                return true;
            }
            else
            {
                return false;
            }
        }

        bool EncFile(string fname)
        {
            int i = 0;
            string str = "";
            string chkmagic = "";
            string checkenc = "";
            fstream fcheck;
            
            fcheck.open(fname);

            if(fcheck)
            {
                ifstream inobj(fname);
                while(getline(inobj, str))
                {
                    getline(inobj, str);
                }

                fcheck.close();
                inobj.close();

                for(i = 0; i < 10; i++)
                {
                    chkmagic[i] = str[i];
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
                    return false;
                }

                remove(fname.c_str());

                for(i = 0; i < str.length(); i++)
                {
                    str[i] = str[i]+7;
                }

                fstream fcwfile;

                fcwfile.open(fname, ios::app);
                fcwfile<<this->magic+str;

                return true;
            }
            else
            {
                return false;
            }

        }

        bool DecFile(string fname)
        {
            int i = 0;
            int j = 0;
            string str = "";
            char *withoutmagic = new char[5000000];
            fstream cwfile;

            ifstream chkmyenc(fname);

            getline(chkmyenc, str);
            chkmyenc.close();

            for(i = 0; i < 10; i++)
            {
                if(str[i] != this->magic[i])
                {
                    break;
                }
            }

            if(i == 10)
            {
                for(i = 10, j = 0; i < str.length(); i++, j++)
                {
                    str[i] = str[i] - 7;
                    withoutmagic[j] = str[i];
                }

                remove(fname.c_str());
  
                cwfile.open(fname, ios::out);
                cwfile<<withoutmagic;

                delete []withoutmagic;

                return true;
            }
            else
            {
                cout<<endl<<"File already decripted !!!"<<endl;
                delete []withoutmagic;
                return false;
            }
        }
};

class StartEncDec
{
    public:

    void Start()
    {   
        EncDec edobj;
        bool bRet = false;
        string filename;
        string data = "";
        char iChoice;
        cout<<endl<<"Hello Welcome to File Encryption and Decryption application...\n\nEnter 1 to Create a file\nEnter 2 to Write in a file\nEnter 3 to Encrypt a file\nEnter 4 to Decrypt a file\nEnter 5 to Exit an Application\n>_";
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
                    cout<<"File Created Successfully"<<endl;
                }
                else
                {
                    cout<<"File already exists"<<endl;
                }

                Start();
            break;

            case '2':
                cout<<"Enter the file name to write data into the file : "<<endl;
                cin>>filename;
                bRet = false;

                bRet = edobj.WriteFile(filename);

                if(bRet == true)
                {
                    cout<<"Data written successfully into the file."<<endl<<endl;
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
                cout<<"Thank you for using our Application :)"<<endl;
                system("exit");
            break;

            default:
                cout<<endl<<"Invalid option selected !!!"<<endl<<endl;
                Start();
            break;
        }
    }
};
 
int main()
{
    StartEncDec start;
    start.Start();

    return 0;
}

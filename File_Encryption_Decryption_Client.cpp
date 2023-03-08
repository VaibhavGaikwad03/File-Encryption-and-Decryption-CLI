#include "encdec.hpp"
using std::cerr;
using std::string;

int main(void)
{
    bool bFlag = true;
    int iChoice = 0, iRet = 0;
    EncryptionDecryption encdec;
    char chChoice = '\0';
    string strFileName, strData, strPass;

    cout << "\nHello Welcome,";

    while (bFlag)
    {
        cout << "\nSelect one of the following options : \n";
        cout << "\n1. Create File\n2. Write File\n3. Encrypt File\n4. Decrypt File\n5. Delete File\n6. Exit\n>_";
        cin >> iChoice;

        switch (iChoice)
        {
        case 1:

            cout << "\nEnter a file name to create the file : \n";
            cin.ignore();
            getline(cin, strFileName);

            iRet = encdec.create_file(strFileName);

            if (iRet == -1)
                cerr << "\nERROR : File already exists!\n";

            else
                cout << "\nFile successfully created.\n";

            break;

        case 2:

            cout << "\nEnter the name of the file you would like to write to : \n";
            cin.ignore();
            getline(cin, strFileName);

            if (!encdec.is_exists(strFileName))
            {
                cerr << "\nERROR : File does not exists!\n";
                continue;
            }

            cout << "\nEnter the data you would like to write : \n";
            getline(cin, strData);

            iRet = encdec.write_file(strFileName, strData, 1);

            if (iRet == -2)
            {
                cerr << "\nERROR : the file could not be opened.\n";
                continue;
            }

            cout << endl
                 << iRet << " bytes have been written to the file named \"" << strFileName << "\"\n";

            break;

        case 3:

            cout << "\nEnter the file name to encrypt the data from the file : \n";
            cin.ignore();
            getline(cin, strFileName);

            if(!encdec.is_exists(strFileName))
            {
                cerr << "\nERROR : File does not exists!\n";
                continue;
            }

            
            cout << "\nPlease set the password (The password should contain strictly eight characters.) : \n";
            
            while(strPass.length() != 8)
            {
                getline(cin, strPass);

                iRet = encdec.encrypt_data(strFileName, strPass);

                if (iRet == -1)
                {
                    cerr << "\nWarning : The password should contain strictly eight characters.\n";
                    continue;
                }
                strPass.clear();
                break;
            }

            if (iRet == -3)
            {
                cerr << "\nERROR : File already encrypted!\n";
                continue;
            }

            cout << "\nData encrypted successfully.\n";

            break;

        case 4:

            cout << "\nEnter the file name to decrypt the data from the file : \n";
            cin.ignore();
            getline(cin, strFileName);

            if (!encdec.is_exists(strFileName))
            {
                cerr << "\nERROR : File does not exists!\n";
                continue;
            }

            cout << "\nEnter the password to decrypt the file : \n";
            getline(cin, strPass);

            iRet = encdec.decrypt_data(strFileName, strPass);

            strPass.clear();

            if (iRet == -2)
            {
                cerr << "\nERROR : File already decrypted!\n";
                continue;
            }

            if (iRet == -3)
            {
                cerr << "\nERROR : Incorrect password. Please try again.\n";
                continue;
            }

            cout << "\nData decrypted successfully.\n";

            break;

        case 5:

            cout << "\nEnter the file name to delete : \n";
            cin.ignore();
            getline(cin, strFileName);

            if (!encdec.is_exists(strFileName))
            {
                cerr << "\nERROR : File does not exists!\n";
                continue;
            }

            cout << "\nAre you sure you want to delete "
                 << "\"" << strFileName << "\"?(y/n)\n";
            cin >> chChoice;

            if (chChoice == 'N' || chChoice == 'n')
                continue;
            else if (chChoice == 'Y' || chChoice == 'y')
            {
                iRet = encdec.delete_file(strFileName);

                if (iRet == -2)
                {
                    cerr << "\nERROR : We're unable to delete the file at this time. Please try again later.\n";
                    continue;
                }

                cout << "\nFile deleted successfully.\n";
            }
            else
                cout << "\nInvalid option selected!\n";
            break;

        case 6:

            cout << "\nThank you for using our application!\n";
            bFlag = false;

            break;

        default:
            cout << "\nInvalid option selected!\n";
            break;
        }
    }

    return 0;
}
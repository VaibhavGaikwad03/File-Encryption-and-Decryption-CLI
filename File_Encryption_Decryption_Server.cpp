#include "customheader.hpp"
#include <cstdio>
#include <fstream>
#define MAXLINES 1000
using std::ifstream;
using std::ios;
using std::ofstream;
using std::streampos;

EncryptionDecryption::EncryptionDecryption() : m_strCheck("`i^]jn`o"), m_iCountLines(0), m_strPassword("") {}

int EncryptionDecryption::create_file(const string strFileName)
{
    if (is_exists(strFileName))
        return -1; // file already exists

    ofstream fcreate(strFileName);
    fcreate.close();

    return 0;
}

int EncryptionDecryption::write_file(const string strFileName, const string strData, const int iAppend, const int iNewLine)
{
    if (!is_exists(strFileName))
        return -1; // file does not exists

    ofstream write;

    if (iAppend == 0)
        write.open(strFileName);
    else
        write.open(strFileName, ios::app);

    if (!write.is_open())
    {
        write.close();
        return -2; // file could not be opened
    }

    streampos currentpos = write.tellp();

    if (iNewLine == 0)
        write << strData + " ";
    else
        write << strData << endl;

    streampos finalpos = write.tellp();

    write.flush();
    write.close();

    return static_cast<int>(finalpos - currentpos - 1);
}

int EncryptionDecryption::encrypt_data(const string strFileName)
{
    int iCnt1 = 0, iCnt2 = 0;
    string *strData = NULL;
    string strLine = "";

    if (!is_exists(strFileName))
        return -1; // file does not exists

    if (check_enc_dec(strFileName))
        return -2; // file already encrypted

    set_password();

    strData = read_file(strFileName);

    for (iCnt1 = 0; iCnt1 < m_iCountLines; iCnt1++)
    {
        strLine = strData[iCnt1];

        for (iCnt2 = 0; iCnt2 < strLine.length(); iCnt2 += 2)
            strLine[iCnt2] -= 5;
        for (iCnt2 = 1; iCnt2 < strLine.length(); iCnt2 += 2)
            strLine[iCnt2] += 3;

        if (iCnt1 == 0)
        {
            write_file(strFileName, m_strCheck + m_strPassword + strLine, 0, 1);
            continue;
        }
        write_file(strFileName, strLine, 1, 1);
    }
    m_strPassword.clear();
    return 0;
}

int EncryptionDecryption::decrypt_data(const string strFileName, const string strPassword)
{
    int iCnt1 = 0, iCnt2 = 0;
    string *strData = NULL;
    string strLine = "";

    if (!is_exists(strFileName))
        return -1; // file does not exists

    if (!check_enc_dec(strFileName))
        return -2; // file already decrypted

    if (!check_password(strFileName, strPassword))
        return -3; // wrong password

    strData = read_file(strFileName);

    for (iCnt1 = 0; iCnt1 < m_iCountLines; iCnt1++)
    {
        strLine = strData[iCnt1];

        for (iCnt2 = 0; iCnt2 < strLine.length(); iCnt2 += 2)
            strLine[iCnt2] += 5;
        for (iCnt2 = 1; iCnt2 < strLine.length(); iCnt2 += 2)
            strLine[iCnt2] -= 3;

        if (iCnt1 == 0)
        {
            write_file(strFileName, strLine.substr(18), 0, 1);
            continue;
        }

        write_file(strFileName, strLine, 1, 1);
    }
    return 0;
}

void EncryptionDecryption::set_password()
{
    int iCnt = 0;

    while (m_strPassword.length() != 8)
    {
        cout << "\nPlease set the password (The password should contain strictly eight characters.) : \n";
        cin >> m_strPassword;
    }

    for (iCnt = 0; iCnt < m_strPassword.length(); iCnt += 2)
        m_strPassword[iCnt] += 3;
    for (iCnt = 1; iCnt < m_strPassword.length(); iCnt += 2)
        m_strPassword[iCnt] -= 3;
}

bool EncryptionDecryption::check_password(const string strFileName, const string strPassword)
{
    int iCnt = 0;
    string strCheckPass = "";

    ifstream checkpass(strFileName);
    getline(checkpass, strCheckPass);
    checkpass.close();

    strCheckPass = strCheckPass.substr(10, 8);

    for (iCnt = 0; iCnt < strCheckPass.length(); iCnt += 2)
        strCheckPass[iCnt] -= 3;
    for (iCnt = 1; iCnt < strCheckPass.length(); iCnt += 2)
        strCheckPass[iCnt] += 3;

    if (strCheckPass == strPassword)
        return true;
    return false;
}

bool EncryptionDecryption::check_enc_dec(const string strFileName)
{
    string strCheckEncDec = "";

    ifstream checkencdec(strFileName);
    getline(checkencdec, strCheckEncDec);
    checkencdec.close();

    strCheckEncDec = strCheckEncDec.substr(0, 10);

    if (strCheckEncDec == m_strCheck)
        return true;
    return false;
}

string *EncryptionDecryption::read_file(const string strFileName)
{
    int iCnt = 0;

    static string strReadFile[MAXLINES];

    ifstream readfile(strFileName);

    while (getline(readfile, strReadFile[iCnt]))
        iCnt++;

    m_iCountLines = iCnt;

    readfile.close();

    return strReadFile;
}

bool EncryptionDecryption::is_exists(const string strFileName)
{
    ifstream fcheck(strFileName);

    if (fcheck.is_open())
    {
        fcheck.close();
        return true;
    }
    fcheck.close();
    return false;
}

int EncryptionDecryption::delete_file(const string strFileName)
{
    if (!is_exists(strFileName))
        return -1; // file does not exists

    if (remove(strFileName.c_str()))
        return -2; // can't delete file
    return 0;
}
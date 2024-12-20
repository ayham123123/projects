
#include <fstream>
#include "hashtbl.h"
#include <iostream>
using namespace std;

//--------------------------------------------------------------------
//                         login.cpp
//
//  program that reads in username/login pairs and then
//  performs authentication of usernames.
//--------------------------------------------------------------------

// This will be the data stored in the HashTbl (class T)

struct Password
{
    void setKey(string newKey) { username = newKey; }
    string getKey() const { return username; }

    // This hash converts a string to an integer
    int hash(const string str) const
    {
        int val = 0;

        for (unsigned int i = 0; i < str.length(); i++)
            val += str[i];
        return val;
    }
    string username, password;
};

int main()
{
    HashTbl<Password, string> passwords(10);
    Password tempPass;
    string name;      // User-supplied name
    string pass;      // User-supplied password

    //*********************************************************
    // Step 1: Read in the password file
    //*********************************************************
    ifstream passFile("password.txt");

    if (!passFile)
    {
        cout << "Unable to open 'password.txt'!" << endl;
        exit(0);
    }

    passFile >> tempPass.username;
    while (!passFile.eof() && !passwords.isFull())
    {
        passFile >> tempPass.password;
        passwords.insert(tempPass); 
    }

    cout << "Printing the hash table:..." << endl;
    passwords.showStructure(); 

    //*********************************************************
    // Step 2: Prompt for a Login and Password and check if valid
    //*********************************************************
    cout << "Login: ";
    while (cin >> name)  // To quit, type CTRL Z in Visual C++
    {
        bool userFound = passwords.retrieve(name, tempPass);

        cout << "Password: ";
        cin >> pass;

        if (userFound && tempPass.password == pass)
            cout << "Authentication successful" << endl;
        else
            cout << "Authentication failure" << endl;

        cout << "Login: ";
    }
    cout << endl;
}

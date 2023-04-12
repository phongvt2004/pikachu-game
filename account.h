#include "header.h"


// đăng nhập
bool login(char username[], char password[], int &index, string &error, bool &hasRecord, Record &record) {
    Account * account;
    int numAccount;
    read_account(account, numAccount);
    bool hasUser = false;
    for (int i = 0; i < numAccount; i++) {
        if(strcmp(account[i].username, username) == 0) {
            hasUser = true;
            if(strcmp(account[i].password, password) == 0) {
                hasRecord = account[i].hasRecord;
                record = account[i].record;
                index = i;
                return true;
            }
            else {
                error = "Wrong password";
                return false;
            }
        }
    }
    if(!hasUser) {
        error = "User doesn't exist";
        return false;
    }
    return false;
}


// đăng kí
bool signup(char username[20], char password[20],  int &index, string &error) {
    Account * account;
    int numAccount;
    read_account(account, numAccount);
    bool hasUser = false;
    for (int i = 0; i < numAccount; i++) {
        if(strcmp(account[i].username, username) == 0) {
            hasUser = true;
        }
    }
    if(numAccount == 0) {
        account = new Account[1];
    }
    if(hasUser) {
        error = "Username exists";
        return false;
    } else {
        strcpy(account[numAccount].username,username);
        strcpy(account[numAccount].password,password);
        account[numAccount].hasRecord = false;
        index = numAccount;
        numAccount++;
        save_account(account, numAccount);
    }
    delete [] account;
    return true;
}
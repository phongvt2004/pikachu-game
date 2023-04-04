#include "savefile.h"

void save_record(Account * account,int index, int numAccount, Board * board, Cell curr, int points) {
    Record record;
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            record.board[i][j] = board -> cell[i][j].content;
        }
    }
    record.col = board -> col;
    record.row = board -> row;
    record.curr_x = curr.x;
    record.curr_y = curr.y;
    record.points = points;
    account[index].record = record;
    ofstream fOut;
    fOut.open("account.bin", ios::binary);
    for(int i = 0; i < numAccount; i++) {
        fOut.write((char *)&account[i], sizeof(Account));
    }
    fOut.close();
}

void read_account(Account * &account, int &numAccount) {
    ifstream fIn;
    fIn.open("account.bin", ios::binary);
    fIn.seekg(0, ios::end);
    cout << fIn.tellg() << endl;
    cout << sizeof(Account) << endl;
    numAccount = fIn.tellg() / sizeof(Account); // size of file in bytes
    fIn.seekg(0, ios::beg);
    account = new Account[numAccount+1];
    if(numAccount == 0) {
        account = NULL;
        return;
    }
    for(int i = 0; i < numAccount; i++) {
        fIn.read(reinterpret_cast<char*>(&account[i]), sizeof(Account));

    }
    // delete [] account;
    fIn.close();
}

void save_account(Account * account, int numAccount) {
    ofstream fOut;
    fOut.open("account.bin", ios::binary | ios::trunc);
    for(int i = 0; i < numAccount; i++) {
        fOut.write(reinterpret_cast<char*>(&account[i]), sizeof(Account));
    }
    fOut.close();
}

// int main() {
//     Account * account;
//     int numAccount;
//     read_account(account, numAccount);
//     cout << numAccount << endl;
//     if(numAccount != 0) {
//         for(int i = 0; i < numAccount; i++) {
//             cout << "username: " << account[i].username << endl;
//             cout << "password: " << account[i].password << endl;
//             cout << "points: " << account[i].record.points << endl;
//             cout << "----------------------" << endl;
//         }
//     } 
//     else {
//         account = new Account[1];
//     }
//     cout << "username: ";
//     cin >> account[numAccount].username;
//     cout << "password: ";
//     cin.ignore();
//     cin >> account[numAccount].password;
//     cout << "points: ";
//     cin.ignore();
//     cin >> account[numAccount].record.points;
//     numAccount++;
//     save_account(account, numAccount);
//     delete [] account;
// }
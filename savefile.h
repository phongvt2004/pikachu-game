#include "header.h"

// lưu record mới
void save_record(Account *account, int index, int numAccount, Board *board, Cell curr, int points, int lives)
{
    Record record;
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            record.board[i][j] = board->cell[i][j].content;
        }
    }
    record.col = board->col;
    record.row = board->row;
    record.curr_x = curr.x;
    record.curr_y = curr.y;
    record.points = points;
    record.lives = lives;
    account[index].record = record;
    ofstream fOut;
    fOut.open("account.bin", ios::binary);
    for (int i = 0; i < numAccount; i++)
    {
        fOut.write((char *)&account[i], sizeof(Account));
    }
    fOut.close();
}

// lấy dữ liệu user
void read_account(Account *&account, int &numAccount)
{
    ifstream fIn;
    fIn.open("account.bin", ios::binary);
    fIn.seekg(0, ios::end);
    numAccount = fIn.tellg() / sizeof(Account); // size of file in bytes
    fIn.seekg(0, ios::beg);
    account = new Account[numAccount + 1];
    if (numAccount == 0)
    {
        account = NULL;
        return;
    }
    for (int i = 0; i < numAccount; i++)
    {
        fIn.read(reinterpret_cast<char *>(&account[i]), sizeof(Account));
    }
    // delete [] account;
    fIn.close();
}


//lưu dữ liệu user

void save_account(Account *account, int numAccount)
{
    ofstream fOut;
    fOut.open("account.bin", ios::binary | ios::trunc);
    for (int i = 0; i < numAccount; i++)
    {
        fOut.write(reinterpret_cast<char *>(&account[i]), sizeof(Account));
    }
    fOut.close();
}


//lấy dữ liệu người chơi
void read_players(Players *&players, int &numPlayers)
{
    ifstream fIn;
    fIn.open("players.bin", ios::binary);
    fIn.seekg(0, ios::end);
    numPlayers = fIn.tellg() / sizeof(Players); // size of file in bytes
    fIn.seekg(0, ios::beg);
    players = new Players[numPlayers + 1];
    if (numPlayers == 0)
    {
        players = NULL;
        return;
    }
    for (int i = 0; i < numPlayers; i++)
    {
        fIn.read(reinterpret_cast<char *>(&players[i]), sizeof(Players));
    }
    fIn.close();
}

//lưu dữ liệu người chơi

void save_players(Players *players, int numPlayers)
{
    ofstream fOut;
    fOut.open("players.bin", ios::binary | ios::trunc);
    for (int i = 0; i < numPlayers; i++)
    {
        fOut.write(reinterpret_cast<char *>(&players[i]), sizeof(Players));
    }
    fOut.close();
}
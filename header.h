#pragma once
#include<iostream>
#include<fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <string.h>
#define COL 10
#define ROW 6
using namespace std;

struct Cell {
    char content;
    int x,y;
};

struct Board {
    Cell ** cell;
    int col, row;
};

struct Player {
    char username[20];
    int points;
};

struct Record {
    char board[ROW][COL];
    int col, row;
    int curr_x, curr_y;
    int points;
};

struct Account {
    char username[20];
    char password[20];
    bool hasRecord;
    Record record;
};

struct Players {
    char username[20];
    int maxPoints;
}
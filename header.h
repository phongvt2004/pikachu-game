#pragma once
#include<iostream>
#include<fstream>
#include <cstdlib>
#include <ctime>
#include <string>
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
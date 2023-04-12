#pragma once
#include "header.h"
#include "graphics.h"

//viết header của game
void generateHeader(int x, int y) {
    ifstream fIn;
    fIn.open("header.txt");
    SetColor(0, 3);
    string temp;
    for(int i = 0; i < 5; i++) {
        gotoXY(x,i+y);
        getline(fIn, temp);
        cout << temp << endl;
    }
    SetColor(0, 12);
    for(int i = 6; i < 11; i++) {
        gotoXY(x+22,i+y);
        getline(fIn, temp);
        cout << temp << endl;
    }
    SetColor(0, 7);
}

//vẽ các lựa chọn
void generateOption(int x, int y, string text, int color) {
    SetColor(0,color);
    gotoXY(x,y);
    cout << " ";
    for(unsigned int i = 0; i < text.length() + 4; i++) {
        cout <<"-";
    }
    cout << " ";
    cout << endl;
    gotoXY(x,y+1);
    cout << "|  " << text <<  "  |"<<endl;
    gotoXY(x,y+2);
    cout << " ";
    for(int i = 0; i < text.length() + 4; i++) {
        cout <<"-";
    }
    cout << " ";
    SetColor(0,7);
}

//tính độ dài của chữ
int text_length(char text[20]) {
    int i = 0;
    while(text[i] != '\0') {
        i++;
    }
    return i;
}

//vẽ tên các leader trong leaderboard
void generateLeader(int x, int y, char text[20], int color) {
    SetColor(0,color);
    gotoXY(x,y);
    cout << " ";
    for(unsigned int i = 0; i < text_length(text) + 4; i++) {
        cout <<"-";
    }
    cout << " ";
    cout << endl;
    gotoXY(x,y+1);
    cout << "|  " << text <<  "  |"<<endl;
    gotoXY(x,y+2);
    cout << " ";
    for(int i = 0; i < text_length(text) + 4; i++) {
        cout <<"-";
    }
    cout << " ";
    SetColor(0,7);
}

//tính độ dài của số
int number_length(int n) {
    int i = 0;
    while(n > 0) {
        n /= 10;
        i++;
    }
    return i;
}

//vẽ điểm số trong leaderboard
void generatePoint(int x, int y, int point, int color) {
    SetColor(0,color);
    gotoXY(x,y);
    cout << " ";
    for(unsigned int i = 0; i < number_length(point) + 4; i++) {
        cout <<"-";
    }
    cout << " ";
    cout << endl;
    gotoXY(x,y+1);
    cout << "|  " << point <<  "  |"<<endl;
    gotoXY(x,y+2);
    cout << " ";
    for(int i = 0; i < number_length(point) + 4; i++) {
        cout <<"-";
    }
    cout << " ";
    SetColor(0,7);
}

//vẽ phần info trong game
void generateGameInfo(char username[20], int x, int y, int points, int lives) {
    SetColor(14, 3);
    gotoXY(x,y);
    cout << " Username: " << username << " ";
    gotoXY(x+35,y);
    cout << " Points: " << points << " ";
    gotoXY(x+50,y);
    cout << " Lives: " << lives << " ";
    SetColor(14, 7);
}

//vẽ bảng chơi game
void generateBoard(Board * board, int x, int y, Cell * curr, bool hasStart, Cell start, bool suggest, Cell sugStart, Cell sugEnd) {
    for(int i = 0; i < board -> row; i++) {
        for(int j = 0; j < board -> col; j++) {
            if(board ->cell[i][j].content == ' ') {
                continue;
            }
            SetColor(8, 11);
            gotoXY(x+j*10,y+i*4);
            cout << " --------- ";
            gotoXY(x+j*10,y+i*4+1);
            cout << "|";
            if((curr -> x == i and curr -> y == j) or (hasStart and start.x == i and start.y == j))
                SetColor(15, 0);
            if(suggest and ((sugStart.x == i and sugStart.y == j) or (sugEnd.x == i and sugEnd.y == j)))
                SetColor(10, 0);
            cout << "         ";
            SetColor(8, 11);
            cout << "|";
            gotoXY(x+j*10,y+i*4+2);
            cout << "|";
            if((curr -> x == i and curr -> y == j) or (hasStart and start.x == i and start.y == j))
                SetColor(15, 0);
            if(suggest and ((sugStart.x == i and sugStart.y == j) or (sugEnd.x == i and sugEnd.y == j)))
                SetColor(10, 0);
            cout << "    ";
            cout << board->cell[i][j].content;
            cout<<"    ";
            SetColor(8, 11);
            cout <<"|";
            gotoXY(x+j*10,y+i*4+3);
            cout << "|";
            if((curr -> x == i and curr -> y == j) or (hasStart and start.x == i and start.y == j))
                SetColor(15, 0);
            if(suggest and ((sugStart.x == i and sugStart.y == j) or (sugEnd.x == i and sugEnd.y == j)))
                SetColor(10, 0);
            cout << "         ";
            SetColor(8, 11);
            cout << "|";
            gotoXY(x+j*10,y+i*4+4);
            cout << " --------- ";
            SetColor(0, 7);
        }
    }
}


//vẽ chữ khi game kết thúc
void endgame(bool lose, int x, int y) {
    ifstream fIn;
    fIn.open("endgame.txt");
    for(int i = 0; i < 15; i++) {
        gotoXY(i <= 9 ? x : x - 5,y+i);
        string temp;
        getline(fIn, temp);
        if(!lose) continue;
        SetColor(0,6);
        cout << temp << endl;
    }
    if(lose) return;
    SetColor(0,12);
    for(int i = 0; i < 5; i++) {
        gotoXY(x,y+i);
        string temp;
        getline(fIn, temp);
        cout << temp << endl;
    }
    fIn.close();
}


// vẽ background
void background(int bg, int x, int y) {
    ifstream fIn;
    fIn.open("background.txt");
    SetColor(0,3);
    for(int i = 0; i < 26; i++) {
        gotoXY(x,y+i);
        string temp;
        getline(fIn, temp);
        if(bg == 2) continue;
        cout << temp << endl;
    }
    if(bg == 1) return;
    for(int i = 0; i < 25; i++) {
        gotoXY(x,y+i);
        string temp;
        getline(fIn, temp);
        cout << temp << endl;
    }
    fIn.close();
}


//vẽ hình từ file
void printfile(string filename, int x, int y) {
    ifstream fIn;
    fIn.open(filename.c_str());
    SetColor(0,3);
    int i = 0;
    while(!fIn.eof()) {
        gotoXY(x,y+i);
        string temp;
        getline(fIn, temp);
        cout << temp << endl;
        i++;
    }
    fIn.close();
}
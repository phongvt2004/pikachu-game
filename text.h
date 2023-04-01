#pragma once
#include "header.h"
#include "graphics.h"

void generateHeader(int x, int y, int color) {
    
    textcolor(color);
    gotoXY(x,0+y);
    cout << "J5!     :YJ.    !5!   ?JJJYJJJJ:  ^?JYYJ!.  ~J.    .J~  7?  ~5~     J!   .7JJYYJ!" << endl;
    gotoXY(x,1+y);
    cout << "###:    P#&.   ~&J&~  :^:~@Y:^^ .5G!:.:~PP. J@.    .@J  GB  J@#Y    &Y  7#J^:.:~P5" << endl;
    gotoXY(x,2+y);
    cout << "#JYG   J57&.  :#? ?#:    .@?    ?@:         ?@7!!!!7@J  PG  J#:PG^  #Y :@?         " << endl;
    gotoXY(x,3+y);
    cout << "#J BJ ~B.7&.  G#777#B.   :@?    Y&.         ?@?7777?@J  PG  J&  ?#? #Y ~@!   ~5Y5B!" << endl;
    gotoXY(x,4+y);
    cout << "&J ^&!B~ ?&. 5#~~!~~BG   :@?    :#Y.    ?#^ J&.    .&J  GG  J&.  ^BP&Y  5B^     !@7" << endl;
    gotoXY(x,5+y);
    cout << "G?  ?#?  7B.!#^     :#?  .B7     :YPYJY55~  ?B.    .B?  5P  ?B.    Y&?   !55YJY55?." << endl;
    gotoXY(x,6+y);
    for(int i=0;i< 82; i++) cout << "-";
    cout << endl;
    gotoXY(x+18,7+y);
    cout << "  .7JYYYJ!      ~5!    757     .JY: :YJJJJJJ?." << endl;
    gotoXY(x+18,8+y);
    cout << "7#J^:.:~P5    ^#J&!    G&&~    Y#@^ !@!" << endl;
    gotoXY(x+18,9+y);
    cout << "@?           .BJ 7&^   GP7#.  7G!@^ ~@7^~~~~:" << endl;
    gotoXY(x+18,10+y);
    cout << "@~   !5Y5B~  P&777##:  GP PP :#^^@^ ~@Y?????~" << endl;
    gotoXY(x+18,11+y);
    cout << "PB^     !@! Y#~~!~~GB. GP .#?P? ~@^ !@^"<<endl;
    gotoXY(x+18,12+y);
    cout << " 755YJY55?.~#~     :BJ 55  ~#5  ^#^ ~#5YYYYYY^" << endl;
    textcolor(7);
}

void generateOption(int x, int y, string text, int color) {
    textcolor(color);
    gotoXY(x,y);
    cout << " ";
    for(int i = 0; i < text.length() + 4; i++) {
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
    textcolor(7);
}

void generateBoard(Board * board, int x, int y, Cell * curr, bool hasStart, Cell start) {

    for(int i = 0; i < board -> row; i++) {
        gotoXY(x,y+i*4);

        for(int j = 0; j < board -> col; j++) {
                cout << " ---------";
        }
        cout << endl;
        gotoXY(x,y+i*4+1);
        for(int j = 0; j < board -> col; j++) {
            if (j == board -> col-1) {
                cout << "|";
                if((curr -> x == i and curr -> y == j) or (hasStart and start.x == i and start.y == j))
                    SetColor(15, 0);
                cout << "         ";
                SetColor(0, 7);
                cout << "|";
            }
            else {
                cout << "|";
                if((curr -> x == i and curr -> y == j) or (hasStart and start.x == i and start.y == j))
                    SetColor(15, 0);
                cout << "         ";
                SetColor(0, 7);
            }
        }
        cout << endl;
        gotoXY(x,y+i*4+2);
        for(int j = 0; j < board -> col; j++) {
            if (j == board -> col-1) {
                cout << "|";
                if((curr -> x == i and curr -> y == j) or (hasStart and start.x == i and start.y == j))
                    SetColor(15, 0);
                cout << "    ";
                cout << board->cell[i][j].content;
                cout<<"    ";
                SetColor(0, 7);
                cout <<"|";
            }
            else {
                cout << "|";
                if((curr -> x == i and curr -> y == j) or (hasStart and start.x == i and start.y == j))
                    SetColor(15, 0);
                cout << "    ";
                cout << board->cell[i][j].content;
                cout << "    ";
                SetColor(0, 7);
            }
        }
        cout << endl;
        gotoXY(x,y+i*4+3);
        for(int j = 0; j < board -> col; j++) {
            if (j == board -> col-1) {
                cout << "|";
                if((curr -> x == i and curr -> y == j) or (hasStart and start.x == i and start.y == j))
                    SetColor(15, 0);
                cout << "         ";
                SetColor(0, 7);
                cout << "|";
            }
            else {
                cout << "|";
                if((curr -> x == i and curr -> y == j) or (hasStart and start.x == i and start.y == j))
                    SetColor(15, 0);
                cout << "         ";
                SetColor(0, 7);
            }
        }
        cout << endl;
        // for(int j = 0; j < board.col; j++) {
        //     cout << "|  " << board.cell[i][j].content <<"  |" << endl;
        // }
        gotoXY(x,y+i*4+4);
        if(i == board -> row - 1) {
            for(int j = 0; j < board -> col; j++) {
                cout << " ---------";
            }
        }
    }
}
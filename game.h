#include "header.h"
#include "graphics.h"
#include "home.h"
#include "text.h"
#include "match.h"

void game_start(Board * &board) {
    board -> col = COL;
    board -> row = ROW;
    board -> cell = new Cell * [board -> row];
    for (int i = 0; i < board -> row; i++) {
        board -> cell[i] = new Cell[board -> col];
    }
    for(int i = 0; i < board -> row; i++) {
        for(int j = 0; j < board -> col; j++) {
            board -> cell[i][j].content = (char) ('A' + rand() % 6);
            board -> cell[i][j].x = i;
            board -> cell[i][j].y = j;
        }
    }
}

void play_game(Board *&board) {
    Cell * curr = new Cell;
    curr->x = 0;
    curr->y = 0;
    int key;
    Cell start, end;
    bool hasStart = false;
    while(true) {
        generateBoard(board,0, 1, curr, hasStart, start);
        key = _getch();
        cout << key << endl;
        if(key == 119) curr -> x = curr -> x > 0 ? curr -> x - 1 : ROW-1;
        else if(key == 115) curr -> x = curr -> x < ROW-1 ? curr -> x + 1 : 0;
        else if(key == 97) curr -> y = curr -> y > 0 ? curr -> y - 1 : COL-1;
        else if(key == 100) curr -> y = curr -> y < COL - 1 ? curr -> y + 1 : 0;
        else if(key == '\r' or key == '\n') {
            if(hasStart) {
                end = *curr;
                hasStart = false;
                if(checkMatch(board, start, end)) {
                    board->cell[start.x][start.y].content = ' ';
                    board->cell[end.x][end.y].content = ' ';
                };
            }
            else {
                start = *curr;
                hasStart = true;
            }
        } else if(key == 27) break;
    }
    delete curr;
    curr = NULL;
}

void game() {
    Board * board = new Board;
    game_start(board);
    play_game(board);
    for (int i = 0; i < board -> row; i++) {
        delete [] board -> cell[i];
    }
    delete [] board -> cell;
    board -> cell = NULL;
    delete board;
    board = NULL;
}
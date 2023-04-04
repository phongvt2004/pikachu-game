#include "header.h"
#include "graphics.h"
#include "home.h"
#include "text.h"
#include "match.h"
#include "savefile.h"
#include "account.h"

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

bool checkMove(Board * board, Cell &start, Cell &end) {
    Cell currStart, currEnd;
    for(int i = 0; i < board->row; i++) {
        for(int j = 0; j < board->col; j++) {
            if(board->cell[i][j].content == ' ') continue;
            currStart = board->cell[i][j];
            for(int m = i; m < board->row; m++) {
                for(int n = j+1; n < board->col; n++) {
                    if(board->cell[m][n].content == ' ') continue;
                    currEnd = board->cell[m][n];
                    if(checkMatch(board, currStart, currEnd)) {
                        start = currStart;
                        end = currEnd;
                        return true;
                    }
                }
            }
        }
    }
    return false;
}


void play_game(Board *&board) {
    Cell * curr = new Cell;
    curr->x = 0;
    curr->y = 0;
    int key;
    Cell start, end;
    Cell sugStart, sugEnd;
    bool hasStart = false;
    bool suggest = false;
    bool clear = false;
    bool hasAccount = false;
    int points = 0;
    int choice = 0;
    int index;
    bool hasRecord = false;
    Record record;
    accountSession:
        ClearScreen();
        do {
            account(choice);
            cout << endl;
            key = _getch();
            if(key == 119) choice = choice > 0 ? choice - 1 : 2;
            else if(key == 115) choice = choice < 2 ? choice + 1 : 0;
        } while (key != '\n' and key != '\r' and key != 27);
        if(key == 27) return;
        ClearScreen();
        char username[20];
        string error;
        bool success = true;
        hasAccount = false;
        if(choice == 0) {
            do {
                ClearScreen();
                if(!success) {
                    gotoXY(50, 17);
                    cout << error << endl;
                    key = _getch();
                    if(key == 27) goto accountSession;
                }
                gotoXY(50, 13);
                cout << "Username: ";
                cin.getline(username,19);
                char password[20];
                gotoXY(50, 15);
                cout << "password: ";
                cin.getline(password,19);
                success = login(username,password,index,error, hasRecord, record);
                cout << "success" << success << endl;
            }
            while(!success);
            hasAccount = success;
            cout << "ok";
            if(hasAccount) {
                choice = 0;
                playOption:
                ClearScreen();
                do {
                    userPlay(choice);
                    cout << endl;
                    key = _getch();
                    if(key == 119) choice = choice > 0 ? choice - 1 : 1;
                    else if(key == 115) choice = choice < 1 ? choice + 1 : 0;
                } while (key != '\n' and key != '\r' and key != 27);
                if(key == 27) goto accountSession;
                else if(choice == 0) {
                    if(!hasRecord) {
                        ClearScreen();
                        gotoXY(55, 15);
                        cout << "No record";
                        cin.get();
                        goto playOption;
                    }
                    else {
                        board -> col = record.col;
                        board -> row = record.row;
                        points = record.points;
                        curr->x = record.curr_x;
                        curr->y = record.curr_y;
                        curr->content = record.board[curr->x][curr->y];
                        gotoXY(1,1);
                        cout << board -> col << endl;
                        for (int i = 0; i < board -> row; i++) {
                            for (int j = 0; j < board -> col; j++) {
                                board -> cell[i][j].content = record.board[i][j];
                                board -> cell[i][j].x = i;
                                board -> cell[i][j].y = j;
                            }
                        }
                        ClearScreen();
                    }
                } 
            }
        }else if(choice == 1) {
            do {
                if(!success) {
                    cout << error << endl;
                    key = _getch();
                    if(key == 27) break;
                }
                cout << "Username: ";
                cin.getline(username,19);
                char password[20];
                cout << "password: ";
                cin.getline(password,19);
                success = signup(username,password, index,error);
            }
            while(!success);
            bool hasAccount = success;
        } else {
        cout << "Username: ";
        cin.getline(username,19);
    }
    while(true) {
        // clean(0,1,110,26);
        if(clear) {
            ClearScreen();
            clear = false;
        }
        generateBoard(board,0, 1, curr, hasStart, start, suggest, sugStart, sugEnd);
        suggest = false;
        key = _getch();
        int move = 0;
        if(key == 119) {
            do {
                curr -> x = curr -> x > 0 ? curr -> x - 1 : ROW-1;
                *curr = board->cell[curr->x][curr->y];
                move++;
                if(move > ROW) break;
            } while(curr->content == ' ');
            if(move > ROW) {
                for(int i = 0; i < board->row; i++) {
                    for(int j = 0; j < board->col; j++) {
                        if(hasStart and start.x == i and start.y == j) continue;
                        if(board->cell[i][j].content != ' ') *curr = board->cell[i][j];
                    }
                }
            }
        }    
        else if(key == 115) {
            do {
                curr -> x = curr -> x < ROW-1 ? curr -> x + 1 : 0;
                *curr = board->cell[curr->x][curr->y];
                move++;
                if(move > ROW) break;
            } while(curr->content == ' ');
            if(move > ROW) {
                for(int i = 0; i < board->row; i++) {
                    for(int j = 0; j < board->col; j++) {
                        if(hasStart and start.x == i and start.y == j) continue;
                        if(board->cell[i][j].content != ' ') *curr = board->cell[i][j];
                    }
                }
            }
        }    
        else if(key == 97) {
            do {
                curr -> y = curr -> y > 0 ? curr -> y - 1 : COL-1;
                *curr = board->cell[curr->x][curr->y];
                move++;
                if(move > COL) break;
            } while(curr->content == ' ');
            if(move > COL) {
                for(int i = 0; i < board->row; i++) {
                    for(int j = 0; j < board->col; j++) {
                        if(hasStart and start.x == i and start.y == j) continue;
                        if(board->cell[i][j].content != ' ') *curr = board->cell[i][j];
                    }
                }
            }
        }    
        else if(key == 100) {
            do {
                curr -> y = curr -> y < COL - 1 ? curr -> y + 1 : 0;
                *curr = board->cell[curr->x][curr->y];
                move++;
                if(move > COL) break;
            } while(curr->content == ' ');
            if(move > COL) {
                for(int i = 0; i < board->row; i++) {
                    for(int j = 0; j < board->col; j++) {
                        if(hasStart and start.x == i and start.y == j) continue;
                        if(board->cell[i][j].content != ' ') *curr = board->cell[i][j];
                    }
                }
            }
        }
        else if(key == 104) {
            suggest = checkMove(board, sugStart, sugEnd);
        }    
        else if(key == '\r' or key == '\n') {
            if(hasStart) {
                end = *curr;
                hasStart = false;
                if(checkMatch(board, start, end)) {
                    board->cell[start.x][start.y].content = ' ';
                    board->cell[end.x][end.y].content = ' ';
                    points += 100;
                    clear = true;
                };
            }
            else {
                start = *curr;
                hasStart = true;
            }
        } else if(key == 27) {
            if(hasAccount) {
                Account * account;
                int numAccount;
                
                read_account(account, numAccount);
                account->hasRecord = true;
                save_record(account, index, numAccount, board, *curr, points);
                delete [] account;
            }
            break;
        }
        
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


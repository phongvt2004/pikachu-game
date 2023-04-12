#pragma once
#include "header.h"
#include "graphics.h"
#include "option.h"
#include "text.h"
#include "match.h"
#include "savefile.h"
#include "account.h"
#include "leaderboard.h"


//khởi tạo bảng
void game_start(Board * &board, int col, int row) {
    srand(time(0));
    char arr1[col * row];
    board -> col = col;
    board -> row = row;
    board -> cell = new Cell * [board -> row];
    for (int i = 0; i < board -> row; i++) {
        board -> cell[i] = new Cell[board -> col];
    }
    for (int i = 0; i < (col*row)/2; i++){
        arr1[i] = arr1[i + (col*row)/2] = (char) ('A' + (rand() % 10));
    }
    int k = 0;
    for(int i = 0; i < board -> row; i++) {
        for(int j = 0; j < board -> col; j++) {
            board -> cell[i][j].content = (char) arr1[k];
            k++;
            board -> cell[i][j].x = i;
            board -> cell[i][j].y = j;
        }
    }
    for (int i = 0; i < row; i++){
        for (int j = 0; j < col; j++){
            int m = rand() % row;
            int n = rand() % col;
            char temp = board -> cell[i][j].content;
            board -> cell[i][j].content = board -> cell[m][n].content;
            board -> cell[m][n].content = temp;
        }
    }
}

//kiểm tra xem còn nước đi không nếu có trả về 2 ô có thể match
bool checkMove(Board * board, Cell &start, Cell &end) {
    Cell currStart, currEnd;
    for(int i = 0; i < board->row; i++) {
        for(int j = 0; j < board->col; j++) {
            if(board->cell[i][j].content == ' ') continue;
            currStart = board->cell[i][j];
            for(int m = i; m < board->row; m++) {
                for(int n = m == i ? j+1 : 0; n < board->col; n++) {
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

//kiểm tra xem còn ô nào không
bool game_finish(Board * board) {
    for (int i = 0; i < board -> row; i++){
        for (int j = 0; j < board -> col; j++){
            if(board -> cell[i][j].content != ' ') return false;
        }
    }
    return true;
}


//bắt đầu chơi game
void play_game(Board *&board) {
    Cell * curr = new Cell; // con trỏ hiện tại
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
    int lives = 3;
    int choice = 0;
    int index;
    bool hasRecord = false;
    Record record;
    // xử lí phần account: đăng nhập , đăng kí, không tạo tài khoản
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
        cin.ignore();
        if(choice == 0) {
            do {
                if(!success) {
                    gotoXY(50, 17);
                    cout << error << endl;
                    key = _getch();
                    if(key == 27) goto accountSession;
                    ClearScreen();
                }
                gotoXY(50, 13);
                cout << "Username: ";
                cin.getline(username,19);
                char password[20];
                gotoXY(50, 15);
                cout << "password: ";
                cin.getline(password,19);
                success = login(username,password,index,error, hasRecord, record);
            }
            while(!success);
            hasAccount = success;
            if(hasAccount) {
                choice = 0;
                // nếu có tài khoản thì có thể chọn chơi ván mới hoặc tiếp tục ván cũ
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
                        lives = record.lives;
                        curr->x = record.curr_x;
                        curr->y = record.curr_y;
                        curr->content = record.board[curr->x][curr->y];
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
                    gotoXY(50, 17);
                    cout << error << endl;
                    key = _getch();
                    if(key == 27) goto accountSession;
                    ClearScreen();
                }
                gotoXY(50, 13);
                cout << "Username: ";
                cin.getline(username,19);
                char password[20];
                gotoXY(50, 15);
                cout << "password: ";
                cin.getline(password,19);
                success = signup(username,password, index,error);
            }
            while(!success);
            bool hasAccount = success;
        } else {
        do {
            ClearScreen();
            if(!success) {
                gotoXY(50, 17);
                cout << "Username exists" << endl;
                key = _getch();
                if(key == 27) goto accountSession;
            }
            gotoXY(50, 13);
            cout << "Username: ";
            cin.getline(username,19);
            success = checkUsername(username);
        } while(!success);

    }
    bool lose = false;
    ClearScreen();
    int bg = 1;
    // Bắt đầu vẽ ingame và chơi
    background(bg, 15,3);
    while(true) {
        Cell start_temp, end_temp;
        //đảo lại bảng nếu không còn nước đi
        while(!checkMove(board, start_temp, end_temp)) {
            srand(time(0));
            for (int i = 0; i < board->row; i++){
                for (int j = 0; j < board->col; j++){
                    int m = rand() % board->row;
                    int n = rand() % board->col;
                    char temp = board -> cell[i][j].content;
                    board -> cell[i][j].content = board -> cell[m][n].content;
                    board -> cell[m][n].content = temp;
                }
            }
        }
        if(clear) {
            ClearScreen();
            clear = false;
            background(bg, 15,3);
        }
        generateGameInfo(username, 5, 1, points, lives);
        generateBoard(board, 10, 3, curr, hasStart, start, suggest, sugStart, sugEnd);
        suggest = false;
        key = _getch();
        int move = 0;
        bool found = false;
        int i = curr->x;
        int j = curr->y;
        if(key == 119) {
            do {
                i = i > 0 ? i - 1 : board->row-1;
                move = 0;
                while(move <= board->col) {
                    if(board->cell[i][j].content != ' ') {
                        found = true;
                        break;
                    }
                    j = j > 0 ? j - 1 : board->col-1;
                    move++;
                }
                if(found) {
                    *curr = board->cell[i][j];
                    break;
                }
            } while(true);
        }    
        else if(key == 115) {
            do {
                i = i < board->row-1 ? i + 1 : 0;
                move = 0;
                while(move <= board->col) {
                    if(board->cell[i][j].content != ' ') {
                        found = true;
                        break;
                    }
                    j = j < board->col-1 ? j + 1 : 0;
                    move++;
                }
                if(found) {
                    *curr = board->cell[i][j];
                    break;
                }
            } while(true);
        }    
        else if(key == 97) {
            do {
                j = j > 0 ? j - 1 : board->col-1;
                move = 0;
                while(move <= board->row) {
                    if(board->cell[i][j].content != ' ') {
                        found = true;
                        break;
                    }
                    i = i > 0 ? i - 1 : board->row-1;
                    move++;
                }
                if(found) {
                    *curr = board->cell[i][j];
                    break;
                }
            } while(true);
        }    
        else if(key == 100) {
            do {
                j = j < board->col - 1 ? j + 1 : 0;
                move = 0;
                while(move <= board->row) {
                    if(board->cell[i][j].content != ' ') {
                        found = true;
                        break;
                    }
                    i = i < board->row - 1 ? i + 1 : 0;
                    move++;
                }
                if(found) {
                    *curr = board->cell[i][j];
                    break;
                }
            } while(true);
        } else if(key == 98) {
            bg = bg == 1 ? 2 : 1;
            clear = true;
        }
        else if(key == 104) {
            points -= 200;
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
                    //Nếu có 2 ô match thì check finish
                    if(game_finish(board)) break;
                } else {
                    // Chọn sai thì trừ mạng, mạng bằng 0 game over
                    lives--;
                    if(lives == 0) {
                        lose = true;
                        break;
                    }
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
                save_record(account, index, numAccount, board, *curr, points, lives);
                updateAccountPlayers(username, points);
                delete [] account;
            } else {
                addPlayers(username, points);
            }
            delete curr;
            curr = NULL;
            ClearScreen();
            break;
        }
        gotoXY(0,10);
        
    }
    ClearScreen();
    if(lose or !game_finish(board)) {
        endgame(true, 20, 5);
    } else {
        endgame(false, 30, 10);
    }
    _getch();
}

// xử lí chơi game
void game() {
    Board * board = new Board;
    int col, row;
    //Cho user custom row, column nhưng tổng cố cell phải chẵn và dương, row và col không dc vượt qua define ROW COL
    do {
        ClearScreen();
        gotoXY(50,10);
        cout << "Number of rows(max 6): ";
        cin >> row;
        gotoXY(50,11);
        cout << "Number of columns(max 10): ";
        cin >> col;
    } while (col*row%2!=0 or row > ROW or col*row <=0 or col > COL);
    game_start(board, col, row);
    play_game(board);
    for (int i = 0; i < board -> row; i++) {
        delete [] board -> cell[i];
    }
    delete [] board -> cell;
    board -> cell = NULL;
    delete board;
    board = NULL;
}


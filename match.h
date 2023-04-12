#include "header.h"

//kiểm tra giữa 2 điểm theo chiều ngang có bị chặn không
bool checkLineX(char ** board, int y1, int y2, int x) {
    if(y1 > y2) {
        for(int i = y2+1; i < y1; i++) {
            if(board[x][i] != ' ') return false;
        }
        return true;
    } else if(y1 < y2) {
        for(int i = y1+1; i < y2; i++) {
            if(board[x][i] != ' ') return false;
        }
        return true;
    }
    return false;
}


//kiểm tra giữa 2 điểm theo chiều dọc có bị chặn không
bool checkLineY(char ** board, int x1, int x2, int y) {
    if(x1 > x2) {
        for(int i = x2+1; i < x1; i++) {
            if(board[i][y] != ' ') return false;
        }
        return true;
    } else if(x1 < x2) {
        for(int i = x1+1; i < x2; i++) {
            if(board[i][y] != ' ') return false;
        }
        return true;
    }
    return false;
}


//kiểm tra match kiểu I
bool IMatching(char ** board, Cell start, Cell end) {
    if(start.x == end.x and start.y == end.y) return false;
    if(start.x != end.x and start.y != end.y) return false;
    if(start.x == end.x) return (checkLineX(board, start.y, end.y, start.x) and board[start.x][start.y] == board[end.x][end.y]);
    else if(start.y == end.y) return (checkLineY(board, start.x, end.x, start.y)and board[start.x][start.y] == board[end.x][end.y]);
    return false;
}

//kiểm tra match kiểu L
bool LMatching(char ** board, Cell start, Cell end) {
    if(start.x == end.x or start.y == end.y) return false;
    return (
        (checkLineX(board, start.y, start.y < end.y ? end.y+1 : end.y-1, start.x)
        and checkLineY(board, start.x, end.x, end.y)
        and board[start.x][start.y] == board[end.x][end.y])
        or
        (checkLineY(board, start.x, start.x < end.x ? end.x + 1 : end.x - 1, start.y)
        and checkLineX(board, start.y, end.y, end.x)
        and board[start.x][start.y] == board[end.x][end.y])
    );
}


//kiểm tra match kiểu U
bool UMatching(char ** board, Cell start, Cell end, int row, int col) {
    if(start.x == end.x and start.y == end.y) return false;
    if(IMatching(board, start, end)) return false;
    bool condition;
    for(int i = start.y+1; i <= col; i++) {
        condition = checkLineX(board, start.y, i, start.x) and (i != col ? checkLineY(board, start.x < end.x ? start.x-1: start.x+1, start.x < end.x ? end.x+1 : end.x-1, i) : true) and checkLineX(board, end.y, i, end.x);
        if(condition and board[start.x][start.y] == board[end.x][end.y]) return true;
    }
    for(int i = start.y-1; i >= -1; i--) {
        condition = checkLineX(board, start.y, i, start.x) and (i != -1 ? checkLineY(board, start.x < end.x ? start.x-1: start.x+1, start.x < end.x ? end.x+1 : end.x-1, i) : true) and checkLineX(board, end.y, i, end.x);
        if(condition and board[start.x][start.y] == board[end.x][end.y]) return true;
    }
    for(int i = start.x+1; i <= row; i++) {
        condition = checkLineY(board, start.x, i, start.y) and (i != row ? checkLineX(board, start.y < end.y ? start.y-1: start.y+1, start.y < end.y ? end.y+1 : end.y-1, i) : true) and checkLineY(board, end.x, i, end.y);
        if(condition and board[start.x][start.y] == board[end.x][end.y]) return true;
    }
    for(int i = start.x-1; i >= -1; i--) {
        condition = checkLineY(board, start.x, i, start.y) and (i != -1 ? checkLineX(board, start.y < end.y ? start.y-1: start.y+1, start.y < end.y ? end.y+1 : end.y-1, i) : true) and checkLineY(board, end.x, i, end.y);
        if(condition and board[start.x][start.y] == board[end.x][end.y]) return true;
    }
    return false;
    
}


//kiểm tra match kiểu Z
bool ZMatching(char ** board, Cell start, Cell end) {
    if(start.x == end.x or start.y == end.y) return false;
    bool condition;
    if(start.y < end.y) {
        for(int i = start.y+1; i < end.y; i++) {
            condition = checkLineX(board, start.y, i, start.x) and checkLineY(board, start.x < end.x ? start.x-1: start.x+1, start.x < end.x ? end.x+1 : end.x-1, i) and checkLineX(board, end.y, i, end.x);
            if(condition and board[start.x][start.y] == board[end.x][end.y]) return true;
        }
    } else if(start.y > end.y) {
        for(int i = start.y-1; i > end.y; i--) {
            condition = checkLineX(board, start.y, i, start.x) and checkLineY(board, start.x < end.x ? start.x-1: start.x+1, start.x < end.x ? end.x+1 : end.x-1, i) and checkLineX(board, end.y, i, end.x);
            if(condition and board[start.x][start.y] == board[end.x][end.y]) return true;
        }
    }
    if(start.x < end.x) {
        for(int i = start.x+1; i < end.x; i++) {
            condition = checkLineY(board, start.x, i, start.y) and checkLineX(board, start.y < end.y ? start.y-1: start.y+1, start.y < end.y ? end.y+1 : end.y-1, i) and checkLineY(board, end.x, i, end.y);
            if(condition and board[start.x][start.y] == board[end.x][end.y]) return true;
        }
    } else if(start.x > end.x) {
        for(int i = start.x-1; i > end.x; i--) {
            condition = checkLineY(board, start.x, i, start.y) and checkLineX(board, start.y < end.y ? start.y-1: start.y+1, start.y < end.y ? end.y+1 : end.y-1, i) and checkLineY(board, end.x, i, end.y);
            if(condition and board[start.x][start.y] == board[end.x][end.y]) return true;
        }
    }
    return false;
    
}

//kiểm tra xem 2 ô có match không
bool checkMatch(Board *board, Cell start, Cell end) {
    if(start.content != end.content) return false;
    char ** newBoard = new char * [board->row];
    // chuyển từ cell** sang char ** để dễ kiểm tra
    for (int i = 0; i < board->row; i++) {
        newBoard[i] = new char[board->col];
    }
    for (int i = 0; i < board->row; i++) {
        for (int j = 0; j < board->col; j++) {
            newBoard[i][j] = board -> cell[i][j].content;
        }
    }
    bool match = IMatching(newBoard, start, end) || LMatching(newBoard, start, end) || UMatching(newBoard, start, end, board->row, board->col) || ZMatching(newBoard, start, end);
    // deallocate pointers
    for (int i = 0; i < board->row; i++) {
        delete [] newBoard[i];
        newBoard[i] = NULL;
    }
    delete [] newBoard;
    newBoard = NULL;
    return match;
}
#include "match.h"
struct Point {
    int x, y;
};

void removePoint(char ** board, Point point) {
    board[point.x][point.y] = ' ';
}

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

bool IMatching(char ** board, Cell start, Cell end) {
    if(start.x == end.x and start.y == end.y) return false;
    if(start.x != end.x and start.y != end.y) return false;
    if(start.x == end.x) return (checkLineX(board, start.y, end.y, start.x) and board[start.x][start.y] == board[end.x][end.y]);
    else if(start.y == end.y) return (checkLineY(board, start.x, end.x, start.y)and board[start.x][start.y] == board[end.x][end.y]);
    return false;
}

bool LMatching(char ** board, Cell start, Cell end) {
    if(start.x == end.x or start.y == end.y) return false;
    return (
        (checkLineX(board, start.y, end.y, start.x)
        and checkLineY(board, start.x, end.x, end.y)
        and board[start.x][start.y] == board[end.x][end.y])
        or
        (checkLineX(board, start.y, end.y, end.x)
        and checkLineY(board, start.x, end.x, start.y)
        and board[start.x][start.y] == board[end.x][end.y])
    );
}

bool UMatching(char ** board, Cell start, Cell end) {
    if(start.x == end.x and start.y == end.y) return false;
    if(IMatching(board, start, end)) return false;
    bool condition;
    for(int i = start.y+1; i <= ROW; i++) {
        condition = checkLineX(board, start.y, i, start.x) and (i != ROW ? checkLineY(board, start.x-1, end.x+1, i) : true) and checkLineX(board, end.y, i, end.x);
        if(condition and board[start.x][start.y] == board[end.x][end.y]) return true;
    }
    for(int i = start.y-1; i >= -1; i--) {
        condition = checkLineX(board, start.y, i, start.x) and (i != -1 ? checkLineY(board, start.x-1, end.x+1, i) : true) and checkLineX(board, end.y, i, end.x);
        if(condition and board[start.x][start.y] == board[end.x][end.y]) return true;
    }
    for(int i = start.x+1; i <= ROW; i++) {
        condition = checkLineY(board, start.x, i, start.y) and (i != ROW ? checkLineX(board, start.y-1, end.y+1, i) : true) and checkLineY(board, end.x, i, end.y);
        if(condition and board[start.x][start.y] == board[end.x][end.y]) return true;
    }
    for(int i = start.x-1; i >= -1; i--) {
        condition = checkLineY(board, start.x, i, start.y) and (i != -1 ? checkLineX(board, start.y-1, end.y+1, i) : true) and checkLineY(board, end.x, i, end.y);
        if(condition and board[start.x][start.y] == board[end.x][end.y]) return true;
    }
    return false;
    
}

bool ZMatching(char ** board, Cell start, Cell end) {
    if(start.x == end.x or start.y == end.y) return false;
    bool condition;
    if(start.y < end.y) {
        for(int i = start.y+1; i < end.y; i++) {
            condition = checkLineX(board, start.y, i, start.x) and checkLineY(board, start.x-1, end.x+1, i) and checkLineX(board, end.y, i, end.x);
            if(condition and board[start.x][start.y] == board[end.x][end.y]) return true;
        }
    } else if(start.y > end.y) {
        for(int i = start.y-1; i > end.y; i--) {
            condition = checkLineX(board, start.y, i, start.x) and checkLineY(board, start.x-1, end.x+1, i) and checkLineX(board, end.y, i, end.x);
            if(condition and board[start.x][start.y] == board[end.x][end.y]) return true;
        }
    }
    if(start.x < end.x) {
        for(int i = start.x+1; i < end.x; i++) {
            condition = checkLineY(board, start.x, i, start.y) and checkLineX(board, start.y-1, end.y+1, i) and checkLineY(board, end.x, i, end.y);
            if(condition and board[start.x][start.y] == board[end.x][end.y]) return true;
        }
    } else if(start.x > end.x) {
        for(int i = start.x-1; i > end.x; i--) {
            condition = checkLineY(board, start.x, i, start.y) and checkLineX(board, start.y-1, end.y+1, i) and checkLineY(board, end.x, i, end.y);
            if(condition and board[start.x][start.y] == board[end.x][end.y]) return true;
        }
    }
    return false;
    
}

bool checkMatch(Board *board, Cell start, Cell end) {
    if(start.content != end.content) return false;
    char ** newBoard = new char * [ROW];
    for (int i = 0; i < ROW; i++) {
        newBoard[i] = new char[COL];
    }
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            newBoard[i][j] = board -> cell[i][j].content;
        }
    }
    bool match = IMatching(newBoard, start, end) || LMatching(newBoard, start, end) || UMatching(newBoard, start, end) || ZMatching(newBoard, start, end);
    cout << IMatching(newBoard, start, end) << endl;
    cout << LMatching(newBoard, start, end) << endl;
    cout << UMatching(newBoard, start, end) << endl;
    cout << ZMatching(newBoard, start, end) << endl;
    return match;
}
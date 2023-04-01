#include "game.h"

int main() {
    srand(time(NULL));
    SetWindowSize(120, 30);
    SetScreenBufferSize(120, 40);
    DisableResizeWindow();
    // DisableCtrButton(false, true, true);
    ShowCur(false);
    Board * board = new Board;
    
    for (int i = 0; i < board -> row; i++) {
        delete [] board -> cell[i];
    }
    delete [] board -> cell;
    board -> cell = NULL;
    delete board;
    board = NULL;
    return 0;
}
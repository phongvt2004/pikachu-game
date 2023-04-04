#include "header.h"
#include "graphics.h"
#include "home.h"
#include "game.h"

int main() {
    SetWindowSize(400, 30);
    SetScreenBufferSize(400, 30);
    DisableResizeWindow();
    DisableCtrButton(false, true, true);
    ShowCur(false);
    int key;
    int choice = 0;
    header();
    PlaySound(TEXT("test.wav"), NULL, SND_ASYNC);
    do {
        option(choice);
        cout << endl;
        key = _getch();
        if(key == 119) choice = choice > 0 ? choice - 1 : 3;
        else if(key == 115) choice = choice < 3 ? choice + 1 : 0;
    } while (key != '\n' and key != '\r' and key != 27);
    if(key == 27) return 0;
    else if(key == '\n' || key == '\r') {
        ClearScreen();
        if(choice == 3) return 0;
        else if(choice == 0) {
            game();
        } else if(choice == 1) {
            PlaySound(NULL, NULL, SND_ASYNC);
            system("pause");
        }
    }
    return 0;
}
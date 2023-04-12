#include "header.h"
#include "graphics.h"
#include "option.h"
#include "game.h"

int main() {
    //set lại các thuộc tính của console
    SetWindowSize(120, 30);
    SetScreenBufferSize(120, 30);
    DisableResizeWindow();
    DisableCtrButton(false, true, true);
    ShowCur(false);
    int key;
    int choice = 0;
    int music = 1;
    bool playMusic = true;
    //phát nhạc mode async
    PlaySound(TEXT("music1.wav"), NULL, SND_ASYNC);
    home:
    ClearScreen();
    //in phần header
    generateHeader(19,1);
    do {
        option(choice);
        cout << endl;
        key = _getch();
        if(key == 119) choice = choice > 0 ? choice - 1 : 4;
        else if(key == 115) choice = choice < 4 ? choice + 1 : 0;
    } while (key != '\n' and key != '\r' and key != 27);
    if(key == 27) return 0;
    else if(key == '\n' || key == '\r') {
        ClearScreen();
        //exit
        if(choice == 4) return 0;
        else if(choice == 0) {
            game();
            goto home;
        //how to play
        } else if(choice == 1) {
            string howtoplay = "how_to_play.txt";
            printfile(howtoplay,20,3);
            system("pause");
        //leaderboard
        } else if(choice == 2) {
            Players * players;
            int numPlayers;
            getLeaderboard(players, numPlayers);
            string leaderboard = "leaderboard.txt";
            printfile(leaderboard,23,3);
            if(numPlayers == 0) {
                gotoXY(50,9);
                cout << "No player available";
            } else {
                for(int i = 0; i < min(5,numPlayers); i++) {
                    generateLeader(40, 9 + i*3, players[i].username, 7);
                    generatePoint(62, 9 + i*3, players[i].maxPoints, 7);
                }
            }
            _getch();
            ClearScreen();
            goto home;
        //music
        } else if(choice == 3) {
            choice = 0;
            do {
                musicOption(choice);
                cout << endl;
                key = _getch();
                if(key == 119) choice = choice > 0 ? choice - 1 : 3;
                else if(key == 115) choice = choice < 3 ? choice + 1 : 0;
            } while (key != '\n' and key != '\r' and key != 27);
            if(key == 27) goto home;
            else {
                if(choice == 0) {
                    if(playMusic) {
                        PlaySound(NULL, NULL, SND_ASYNC);
                        playMusic = false;
                    }
                    else {
                        PlaySound(TEXT(music == 1 ? "music1.wav" : "music2.wav"), NULL, SND_ASYNC);
                        playMusic = true;
                    }
                } else if(choice == 1) {
                    if(music != 1)  {
                        PlaySound(TEXT("music1.wav"), NULL, SND_ASYNC);
                        music = 1;
                    }
                } else {
                    if(music != 2) {
                        PlaySound(TEXT("music2.wav"), NULL, SND_ASYNC);
                        music = 1;
                    }
                }
                goto home;
            }
        }
    }
    return 0;
}
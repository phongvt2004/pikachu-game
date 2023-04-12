#include "header.h"

// kiểm tra xem username tồn tại trong players và accounts chưas
bool checkUsername(char username[20]) {
    Players * players;
    int numPlayers;
    read_players(players,numPlayers);
    if(numPlayers != 0) {
        for(int i = 0; i < numPlayers; i++) {
            if(strcmp(players[i].username,username) == 0) {
                delete [] players;
                return false;
            }
        }
        delete [] players;
    }
    Account * account;
    int numAccount;
    read_account(account, numAccount);
    if(numAccount == 0) return true;
    for (int i = 0; i < numAccount; i++) {
        if(strcmp(account[i].username, username) == 0) {
            delete [] account;
            return false;
        }
        delete [] players;
        return true;
    }
}


// thêm players
void addPlayers(char username[20], int points) {
    Players * players;
    int numPlayers;
    read_players(players,numPlayers);
    if(numPlayers == 0) players = new Players[1];
    strcpy(players[numPlayers].username, username);
    players[numPlayers].maxPoints = points;
    numPlayers++;
    save_players(players, numPlayers);
    delete [] players;
}

//update điểm của players có account
void updateAccountPlayers(char username[20], int points) {
    Players * players;
    int numPlayers;
    bool hasPlayer = false;
    read_players(players,numPlayers);
    if(numPlayers == 0) {
        players = new Players[1];
        strcpy(players[numPlayers].username, username);
        players[numPlayers].maxPoints = points;
        numPlayers++;
    } else {
        for(int i = 0; i < numPlayers; i++) {
            if(strcmp(players[i].username,username) == 0) {
                hasPlayer = true;
                players[i].maxPoints = max(players[i].maxPoints,points);
                break;
            }
        }
        if(!hasPlayer) {
            _getch();
            strcpy(players[numPlayers].username, username);
            players[numPlayers].maxPoints = points;
            numPlayers++;
        }
    }
    save_players(players, numPlayers);
    delete [] players;
}

//so sánh 2 players
bool compareTwoPlayers(Players a, Players b)
{
    return (a.maxPoints > b.maxPoints);
}

//lấy danh sách và sắp xem điểm từ cao đến thấp
void getLeaderboard(Players * &players, int &numPlayers) {
    read_players(players,numPlayers);
    if(numPlayers == 0) return;
    sort(players, players+numPlayers, compareTwoPlayers);
}
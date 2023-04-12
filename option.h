#pragma once
#include "header.h"
#include "text.h"

//vẽ các option ở home
void option(int choice) {
    string options[5] = {
        "Play",
        "How to play",
        "High score",
        "Music",
        "Exit"
    };
    for(int i = 0; i < 5; i++) {
        if(i == choice)
            generateOption((120 - (options[i].length() + 6)) / 2, 14 + i*3, options[i], 2);
        else
            generateOption((120 - (options[i].length() + 6)) / 2, 14 + i*3, options[i], 7);
    }
}

//vẽ các option account
void account(int choice) {
    string options[3] = {
        "Login",
        "Register",
        "Play without account"
    };
    for(int i = 0; i < 3; i++) {
        if(i == choice) 
            generateOption((120 - (options[i].length() + 6)) / 2, 8 + i*3, options[i], 2);
        else
            generateOption((120 - (options[i].length() + 6)) / 2, 8 + i*3, options[i], 7);
    }
}

//vẽ option trong login
void userPlay(int choice) {
    string options[2] = {
        "Play last game",
        "Play new game"
    };
    for(int i = 0; i < 2; i++) {
        if(i == choice) 
            generateOption((120 - (options[i].length() + 6)) / 2, 10 + i*3, options[i], 2);
        else
            generateOption((120 - (options[i].length() + 6)) / 2, 10 + i*3, options[i], 7);
    }
}


//vẽ các option music
void musicOption(int choice) {
    string options[3] = {
        "Play/Mute sound",
        "Sound 1",
        "Sound 2"
    };
    for(int i = 0; i < 3; i++) {
        if(i == choice) 
            generateOption((120 - (options[i].length() + 6)) / 2, 10 + i*3, options[i], 2);
        else
            generateOption((120 - (options[i].length() + 6)) / 2, 10 + i*3, options[i], 7);
    }
}
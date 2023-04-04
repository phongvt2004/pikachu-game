#pragma once
#include "header.h"
#include "text.h"

void header() {
    generateHeader(19,1,6);
}

void option(int choice) {
    string options[5] = {
        "Play",
        "How to play",
        "High score",
        "Setting",
        "Exit"
    };
    for(int i = 0; i < 5; i++) {
        if(i == choice) 
            generateOption((120 - (options[i].length() + 6)) / 2, 15 + i*3, options[i], 2);
        else
            generateOption((120 - (options[i].length() + 6)) / 2, 15 + i*3, options[i], 7);
    }
}

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
#pragma once
#include "header.h"
#include "text.h"

void header() {
    generateHeader(19,1,6);
}

void option(int choice) {
    string options[4] = {
        "Play",
        "How to play",
        "High score",
        "Exit"
    };
    for(int i = 0; i < 4; i++) {
        if(i == choice) 
            generateOption((120 - (options[i].length() + 6)) / 2, 15 + i*3, options[i], 2);
        else
            generateOption((120 - (options[i].length() + 6)) / 2, 15 + i*3, options[i], 7);
    }
}
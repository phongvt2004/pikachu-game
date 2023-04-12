#include "header.h"
#include <conio.h>

int main() {
    int key;
    do {
        key = _getch();
        cout << "key: " << key << endl;
    } while (key != 27);
    return 0;
}
#include "header.h"
#include "graphics.h"
using namespace std;

int main()
{
    int key;
    do {
        key = _getch();
        cout << "ok" << endl;
        cout << key << endl;
    } while (key != 27);

    return 0;
}
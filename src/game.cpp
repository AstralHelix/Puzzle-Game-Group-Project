// Name: TBD
// Date:
// E-mail:
// Overview: Room switching, progress tracker, and exit code entry.

#include <iostream>
#include "game.h"
#include "puzzles.h"
using namespace std;

void runGame()
{
    // TODO: replace this placeholder with the room-switching menu,
    //       progress tracker, and exit code check.
    cout << "[Game placeholder - running each puzzle in order]" << endl;

    int code1 = puzzle1();
    int code2 = puzzle2();
    int code3 = puzzle3();
    int code4 = puzzle4();

    cout << "Code numbers collected: "
         << code1 << code2 << code3 << code4 << endl;
}

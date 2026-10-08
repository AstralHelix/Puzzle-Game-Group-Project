// Name: TBD
// Date:
// E-mail:
// Overview: Room switching, progress tracker, and exit code entry.

#include "game.h"
#include "puzzles.h"
#include <iostream>
using namespace std;

//TODO: Progress Tracker - track user progress through the escape room.


// Base class - runs the state and returns the next state
class State {
public:
    // Virtual Destructor - Kill the state machine when nullptr
    virtual ~State() {}

    virtual State* run() = 0;
};

// Puzzleroom is a state that allows the user to select what puzzle they will play
class PuzzleRoom : public State {
public:
    State* run() override;
};

// Puzzle selection from the
class ActivePuzzle : public State {
private:
    int index; // puzzle selection
public:
    ActivePuzzle(int index) : index(index) {}
    State* run() override
};

//TODO: Add Room states - clueroom, intro, escape, code entry states



State* PuzzleRoom::run() {
    cout << "1-3- pick a puzzle, q- quit: ";
    string choice;

    if (choice == "1") return new PuzzleState(0);
    if (choice == "2") return new PuzzleState(1);
    if (choice == "3") return new PuzzleState(2);
    if (choice == "q") return nullptr;

    //TODO: REFINE INPUT VALIDATION
    else return nullptr;
}

State* PuzzleState::run() {
    int digit = -1;
    if (index==0) digit = puzzle1();
    if (index==1) digit = puzzle2();
    if (index==2) digit = puzzle3();


    cout << "Puzzle " << index + 1 << "returned:" << digit << endl;
    return new PuzzleRoom();



}

void runGame()
{
    State* current = new PuzzleRoom();

    while (current != nullptr) {
        State* next = current->run();
        delete current;
        current = next;
    }


    // // TODO: replace this placeholder with the room-switching menu,
    // //       progress tracker, and exit code check.
    // cout << "[Game placeholder - running each puzzle in order]" << endl;

    // int code1 = puzzle1();
    // int code2 = puzzle2();
    // int code3 = puzzle3();
    // int code4 = puzzle4();

    // cout << "Code numbers collected: " << code1 << code2 << code3 << code4 << endl;
}

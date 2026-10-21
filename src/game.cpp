// Name: TBD
// Date:
// E-mail:
// Overview: Room switching, progress tracker, and exit code entry.

#include "game.h"
#include "puzzles.h"
#include <iostream>
using namespace std;

const int NUM_PUZZLES = 3;

//Progress Tracker
struct Progress {
    bool solved[NUM_PUZZLES] = {false, false, false};
    int digits[NUM_PUZZLES] = {0, 0, 0};
};


// Base class - runs the state and returns the next state
class State {
public:
    // Virtual Destructor - Kill the state machine when nullptr
    virtual ~State() {}

    virtual State* run(Progress& progress) = 0;
};

//Intro - explains the game, sends player to the clue room
class Intro : public State {
public:
    State* run(Progress& progress) override;
};

// Clue Room shows the digits found so far, leads to Puzzle Room or Escape Door
class ClueRoom : public State {
public:
    State* run(Progress& progress) override;
};

// Puzzle Room prompts player for puzzle selection
class PuzzleRoom : public State {
public:
    State* run(Progress& progress) override;
};

// Active Puzzle runs the currently selected puzzle from PuzzleRoom
class ActivePuzzle : public State {
private:
    int index; // puzzle selection
public:
    ActivePuzzle(int index) : index(index) {}
    State* run(Progress& progress) override;
};

// Code Entry allows the player to enter the code.
class CodeEntry : public State {
public:
    State* run(Progress& progress) override;
};

// Escaped state occurs when player enters correct code
class Escaped : public State {
public:
    State* run(Progress &progress) override;
};

//
State* Intro::run(Progress& progress) {
    cout << "I don't know if we should be in here... This place looks like it hasn't been visited in years." << endl;
    cout << "But hey, we came all this way, why stop now? But whatever you do don't let that door clo.... *CLICK*" << endl;
    cout << "Great looks like we're stuck. I see a keypad, but how could we find the code." << endl;
    cout << "Hey! There's another room here - and it looks like it leads to more area's with puzzles" << endl;
    cout << "It looks like we'll need to complete the puzzles to get out of here!" << endl;

    return new ClueRoom();
}

State* ClueRoom::run(Progress& progress) {
    cout << "\n[ClueRoom] Digits Found: ";
    for (int i = 0; i < NUM_PUZZLES; i++){
        if (progress.solved[i]) cout << progress.digits[i];
        else cout << "-";
    }

    cout << endl << "p - puzzle room, d - exit door, q - quit: ";
    string choice;

    if (!(cin >> choice)) return nullptr;

    if (choice=="p" || choice == "P") return new PuzzleRoom();
    if (choice=="d" || choice =="D") return new CodeEntry();
    if (choice=="q" || choice=="Q") return nullptr;

    cout << "Invalid Choice." << endl;
    return new ClueRoom();
}


State* PuzzleRoom::run(Progress& progress) {
    cout << "1-3- pick a puzzle, q- quit: ";
    string choice;

    if (choice == "1") return new ActivePuzzle(0);
    if (choice == "2") return new ActivePuzzle(1);
    if (choice == "3") return new ActivePuzzle(2);
    if (choice == "q") return nullptr;

    //TODO: REFINE INPUT VALIDATION
    else return nullptr;
}

State* ActivePuzzle::run(Progress& progress) {
    int digit = -1;
    if (index==0) digit = puzzle1();
    if (index==1) digit = puzzle2();
    if (index==2) digit = puzzle3();


    cout << "Puzzle " << index + 1 << "returned:" << digit << endl;
    return new PuzzleRoom();

}

State* CodeEntry::run(Progress &progress) {
    cout << "\n[Exit Door] Enter the " << NUM_PUZZLES << "-digit code: ";
    string entered;
    if (!(cin >> entered)) return nullptr;

    string code = "";
    bool allSolved = true;

    for (int i=0; i < NUM_PUZZLES; i++) {
        if (!progress.solved[i]) allSolved = false;
        code += to_string(progress.digits[i]);
    }

    if (allSolved && entered == code) return new Escaped();

    cout << "Looks like we're stuck for a bit longer. Let's go back and check out work..." << endl;
    return new ClueRoom();
}

State* Escaped::run(Progress& progress) {
    cout << "The door is opening! Let's go touch grass!" << endl;
    return nullptr;
}

void runGame()
{
    Progress progress;
    State* current = new Intro();

    while (current != nullptr) {
        State* next = current->run(progress);
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

// Name: Austin Zimmerman
// Date: 10.25.26
// E-mail: AZIMMERMAN3@DMACC.EDU
// Overview: Room switching, progress tracker, and exit code entry.

#include "game.h"
#include "puzzles.h"
#include <iostream>
#include <stdexcept>
#include <string>
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

//Run Intro
State* Intro::run(Progress& progress) {
    cout << "I don't know if we should be in here... This place looks like it hasn't been visited in years." << endl;
    cout << "But hey, we came all this way, why stop now? But whatever you do don't let that door clo.... *CLICK*" << endl;
    cout << "Great looks like we're stuck. I see a keypad, but how could we find the code." << endl;
    cout << "Hey! There's another room here - and it looks like it leads to more area's with puzzles" << endl;
    cout << "It looks like we'll need to complete the puzzles to get out of here!" << endl;

    return new ClueRoom();
}

//Run Clueroom - get choice,
State* ClueRoom::run(Progress& progress) {
    cout << "\n[ClueRoom] Digits Found: ";
    for (int i = 0; i < NUM_PUZZLES; i++){
        if (progress.solved[i]) cout << progress.digits[i];
        else cout << "-";
    }

    cout << endl << "p - puzzle room, d - exit door, q - quit: ";
    string choice;

    if (!(cin >> choice)) return new PuzzleRoom();

    if (choice=="p" || choice == "P") return new PuzzleRoom();
    if (choice=="d" || choice =="D") return new CodeEntry();
    if (choice=="q" || choice=="Q") return nullptr;

    cout << "Invalid Choice." << endl;
    return new ClueRoom();
}


State* PuzzleRoom::run(Progress& progress) {
    cout << "1-3 - pick a puzzle, c - clue room, q - quit: ";
    string choice;

    if (choice == "1") return new ActivePuzzle(0);
    if (choice == "2") return new ActivePuzzle(1);
    if (choice == "3") return new ActivePuzzle(2);
    if (choice == "c" || choice == "C") return new ClueRoom();
    if (choice == "q" || choice == "Q") return nullptr;

    else return new PuzzleRoom();
}

State* ActivePuzzle::run(Progress& progress) {

    if (progress.solved[index]) {
        cout << "Puzzle " << index + 1 << " is already solved. It's digit is " << progress.digits[index] << "." << endl;
        return new PuzzleRoom();
    }



    int digit = -1;
    if (index==0) digit = puzzle1();
    if (index==1) digit = puzzle2();
    if (index==2) digit = puzzle3();


    if (digit >=0) {
        progress.solved[index] = true;
        progress.digits[index] = digit;
        cout << "Puzzle " << index + 1 << " solved. Digit: " << digit << endl;
    }

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

    try {
        while (current != nullptr) {
            State* next = current->run(progress);
            delete current;
            current = next;
        }
    } catch (const runtime_error& e) {
        delete current;
        cout << "\nInput Closed. Exiting Game." << endl;
    }
}

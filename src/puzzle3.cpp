// Name: Zachary Martin
// Date: 10/25/2026
// E-mail: zamartin1@dmacc.edu
// Overview: Puzzle #3 - Number Sequence. A glowing panel shows the pattern
//           5, 10, 20, 40, ? and the player must enter the next number.
//           The puzzle repeats until the player answers correctly, gives a
//           hint after 3 wrong answers, and then returns this puzzle's
//           code number (8) to the main game.

#include <iostream>
#include <limits>
#include <stdexcept>
#include "puzzles.h"
using namespace std;

int puzzle3()
{
    const int CORRECT_ANSWER = 80;  // each number doubles: 40 x 2 = 80
    const int CODE_NUMBER = 8;      // digit this puzzle adds to the exit code
    const int HINT_ATTEMPTS = 3;    // wrong answers before the hint shows

    bool puzzleSolved = false;
    int attempts = 0;
    int guess = 0;

    cout << endl;
    cout << "In the corner of the dungeon, a stone panel begins to glow." << endl;
    cout << "Numbers burn into its surface one at a time:" << endl;
    cout << endl;
    cout << "    5, 10, 20, 40, ?" << endl;
    cout << endl;
    cout << "A voice rumbles from behind the wall: \"What number comes next?\"" << endl;

    while (!puzzleSolved)
    {
        cout << "Enter the next number: ";

        // Handle input that is not a whole number
        if (!(cin >> guess))
        {
            // Group rule: if input is closed, throw so the game can exit
            // cleanly instead of looping forever
            if (cin.eof())
            {
                throw runtime_error("Puzzle input was closed.");
            }
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please enter a number." << endl;
            continue;   // bad input does not count as an attempt
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        attempts++;

        if (guess == CORRECT_ANSWER)
        {
            cout << "Correct! Puzzle solved." << endl;
            cout << "The panel slides open and reveals the number "
                 << CODE_NUMBER << "." << endl;
            cout << "Remember it - it is part of the code to escape this dungeon." << endl;
            puzzleSolved = true;
        }
        else
        {
            cout << "Incorrect. The panel flickers and the numbers burn again. Try again." << endl;

            // Show the hint once the player has missed 3 times
            if (attempts == HINT_ATTEMPTS)
            {
                cout << "Hint: Look at how each number changes to become the next one." << endl;
            }
        }
    }

    return CODE_NUMBER;   // hand the code number back to the main game
}

/*
 * Data Testing
 * ------------
 * Tested by building the whole game with g++ -std=c++17 (all files in src)
 * and playing through to Puzzle 3.
 *
 * Test 1 - Correct answer on the first try: 80
 *   Expected: "Correct! Puzzle solved.", reveals 8, returns 8.
 *   Result: PASS
 *
 * Test 2 - Wrong answers: 50, 60, 45, then 80
 *   Expected: "Incorrect" each time, the hint appears right after the 3rd
 *   wrong answer (only once), then 80 solves it.
 *   Result: PASS
 *
 * Test 3 - Invalid input: "abc", then 80
 *   Expected: "Please enter a number.", not counted as an attempt, no crash,
 *   then 80 solves it.
 *   Result: PASS
 *
 * Test 4 - Input closed (Ctrl+D / Ctrl+Z) at the prompt
 *   Expected: runtime_error thrown instead of an endless loop, matching
 *   the group's agreed rule for closed input.
 *   Result: PASS
 */

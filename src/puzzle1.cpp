// Name: Sabrina
// Date: 10/10/2026
// E-mail: slreed6@dmacc.edu
// Overview: Puzzle #1. Displays a math problem, repeats until the
//           player answers correctly, then returns this puzzle's
//           code number.


#include <iostream>
#include <string>
#include <stdexcept>
#include <cctype>
#include "puzzles.h"
using namespace std;

int puzzle1()
{
    //setting the correct answer and then attempts to 0
    const int CORRECT_ANSWER = 9;   //  here is the equation and answer 7 * 6 = 42; 42 - 15 = 27; 27 / 3 = 9
    int attempts = 0;

    cout << endl;
    cout << "Torchlight flickers across the damp dungeon walls. Deep in the" << endl;
    cout << "shadows, a ghostly jailer rattles his chains and hisses:" << endl;
    cout << endl;
    cout << "  \"Every night for 6 nights, 7 lost souls were chained in this cell." << endl;
    cout << "   Then 15 of them crumbled to dust." << endl;
    cout << "   The souls that remain are split equally among 3 cursed cells." << endl;
    cout << "   How many souls haunt each cell?\"" << endl;
    cout << endl;

    while (true)
    {
        cout << "Whisper your answer into the dark: ";

        string line;

        // if the input stream closes (EOF), exit instead of looping forever
        if (!getline(cin, line))
        {
            cout << endl << "The jailer hears only silence..." << endl;
            return -1;   // -1 means the puzzle was not solved
        }

        int guess = 0;

        // handling incorrect user input
        try
        {
            size_t pos = 0;
            guess = stoi(line, &pos);

            // reject trailing characters like "9abc" (trailing spaces are allowed)
            while (pos < line.size() && isspace(static_cast<unsigned char>(line[pos])))
                pos++;
            if (pos != line.size())
                throw invalid_argument("trailing characters");
        }
        catch (const invalid_argument&)
        {
            cout << "The jailer only understands whole numbers." << endl;
            continue;
        }
        catch (const out_of_range&)
        {
            cout << "That number is too vast for even the dead to count." << endl;
            continue;
        }

        attempts++;

        //once the player gives the correct number, leave the loop
        if (guess == CORRECT_ANSWER)
            break;

        //checks whether the answer is correct or not and will give a hint if they've tried 3 times
        cout << "The torches gutter and the jailer cackles. Wrong!" << endl;

        if (attempts == 3)
        {
            cout << "A cold whisper drifts past: \"Multiply, subtract the "
                 << "dust, then divide.\"" << endl;
        }
    }

    cout << "The chains fall silent. A hand etches a number on the wall: "
         << CORRECT_ANSWER << endl;
    cout << "Remember it - it is part of the code to escape this dungeon." << endl;

    return CORRECT_ANSWER;   // the solved answer is the code number
}

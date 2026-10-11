// Name: Sabrina
// Date: 10/10/2026
// E-mail: slreed6@dmacc.edu
// Overview: Puzzle #1. Displays a math problem, repeats until the
//           player answers correctly, then returns this puzzle's
//           code number.


#include <iostream>
#include <limits>
#include "puzzles.h"
using namespace std;
 
int puzzle1()
{
	//setting the correct answer and then guesses and attempts to 0 
    const int CORRECT_ANSWER = 9;   //  here is the equation and answer 7 * 6 = 42; 42 - 15 = 27; 27 / 3 = 9
    int guess = 0;
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
 
    do
    {
        cout << "Whisper your answer into the dark: ";
 
        // handling incorrect user input
        if (!(cin >> guess))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "The jailer only understands whole numbers." << endl;
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        attempts++;
 		//checks whether the answer is correct or not and will give a hint if they've tried 3 times
        if (guess != CORRECT_ANSWER)
        {
            cout << "The torches gutter and the jailer cackles. Wrong!" << endl;
 
            if (attempts == 3)
            {
                cout << "A cold whisper drifts past: \"Multiply, subtract the "
                     << "dust, then divide.\"" << endl;
            }
        }
        //once the player gives the correct number it will return the correct answer to the game play
    } while (guess != CORRECT_ANSWER);
 
    cout << "The chains fall silent. A hand etches a number on the wall: "
         << CORRECT_ANSWER << endl;
    cout << "Remember it - it is part of the code to escape this dungeon." << endl;
 
    return CORRECT_ANSWER;   // the solved answer is the code number
}
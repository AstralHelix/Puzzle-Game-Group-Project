/*
 * Name: Leopold Relatic
 * Date: 10/08/2026
 * Program Overview: Puzzle #2 - Two of Three.
 * Players solve two numerical sequences selected by
 * their first initial, then combine their answers
 * to unlock the final stage.
 */

#include <cctype>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>

using namespace std;

namespace {

const int VARIATION_COUNT = 5;
const int SEQUENCE_LENGTH = 4;
const int ESCAPE_CODE_DIGIT = 7;
const int HINT_THRESHOLD = 2;
const int ANSWER_THRESHOLD = 4;

// Stores both sequences, their answers, and their hints.
struct PuzzleVariation {
    int firstSequence[SEQUENCE_LENGTH];
    int secondSequence[SEQUENCE_LENGTH];
    int firstAnswer;
    int secondAnswer;
    const char* firstHint;
    const char* secondHint;
};

// Five predefined puzzle variations.
const PuzzleVariation VARIATIONS[VARIATION_COUNT] = {
    {
        {3, 6, 9, 12},
        {2, 4, 8, 16},
        15, 32,
        "Each number increases by three.",
        "Each number is twice the previous number."
    },
    {
        {5, 10, 15, 20},
        {4, 7, 10, 13},
        25, 16,
        "Each number increases by five.",
        "Each number increases by three."
    },
    {
        {2, 5, 8, 11},
        {1, 4, 9, 16},
        14, 25,
        "Each number increases by three.",
        "These numbers are perfect squares."
    },
    {
        {20, 17, 14, 11},
        {1, 2, 4, 8},
        8, 16,
        "Each number decreases by three.",
        "Each number is twice the previous number."
    },
    {
        {4, 8, 12, 16},
        {2, 6, 18, 54},
        20, 162,
        "Each number increases by four.",
        "Each number is three times the previous number."
    }
};

// Reads a whole number and handles invalid input.
int getPuzzleAnswer()
{
    int answer;

    while (true) {
        if (cin >> answer) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return answer;
        }

        if (cin.eof()) {
            // Stop rather than loop endlessly if input is closed.
            throw runtime_error("Puzzle input was closed.");
        }

        cout << "A valid whole number is needed: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Selects a variation using the first letter of the name.
int selectVariation(char initial)
{
    if (initial >= 'A' && initial <= 'E') {
        return 0;
    }
    else if (initial >= 'F' && initial <= 'K') {
        return 1;
    }
    else if (initial >= 'L' && initial <= 'P') {
        return 2;
    }
    else if (initial >= 'Q' && initial <= 'U') {
        return 3;
    }

    return 4;
}

// Displays the sequence and its missing final value.
void displaySequence(const int sequence[])
{
    for (int i = 0; i < SEQUENCE_LENGTH; ++i) {
        cout << sequence[i] << ", ";
    }

    cout << "?\n";
}

// Displays a hint or answer based on incorrect attempts.
void displayGhostHint(int failures, const char* hint,
                      int correctAnswer)
{
    if (failures >= ANSWER_THRESHOLD) {
        cout << "The ghosts grow weary of your struggle.\n";
        cout << "A voice whispers: The answer is "
             << correctAnswer << ".\n";
    }
    else if (failures >= HINT_THRESHOLD) {
        cout << "A faint whisper echoes through the room...\n";
        cout << "\"" << hint << "\"\n";
    }
}

// Runs Puzzle #2 and returns its escape-code digit.
int puzzle2()
{
    bool stageOneSolved = false;
    bool stageTwoSolved = false;
    bool puzzleSolved = false;

    int stageOneFailures = 0;
    int stageTwoFailures = 0;
    int finalStageFailures = 0;

    string playerName;
    int answer;

    cout << "\n====================================\n";
    cout << "       PUZZLE 2: TWO OF THREE\n";
    cout << "====================================\n";
    cout << "Two sequences guard the final lock.\n";
    cout << "Should you fail, they might whisper the answer.\n";
    cout << "Remember both answers if you wish to leave alive!\n";

    // Get a name beginning with a letter.
    while (true) {
        cout << "\nSpeak your name: ";

        if (!getline(cin >> ws, playerName)) {
            throw runtime_error("Puzzle input was closed.");
        }

        if (!playerName.empty() &&
            isalpha(static_cast<unsigned char>(playerName[0]))) {
            break;
        }

        cout << "There are countless whispers of numbers, "
             << "a letter might bring them forth.\n";
    }

    char initial = static_cast<char>(
        toupper(static_cast<unsigned char>(playerName[0]))
        );

    int variationIndex = selectVariation(initial);
    const PuzzleVariation& selected = VARIATIONS[variationIndex];

    cout << "\nWelcome, " << playerName << "!\n";
    cout << "The walls shift into a " << variationIndex + 1
         << ". Your puzzle awaits.\n";

    // Stage 1: Solve the first sequence.
    while (!stageOneSolved) {
        cout << "\n--- Stage 1: The First Sequence ---\n";
        displaySequence(selected.firstSequence);
        cout << "Enter the missing number: ";

        answer = getPuzzleAnswer();

        if (answer == selected.firstAnswer) {
            cout << "Correct! The first seal breaks.\n";
            cout << "Remember what brought you here.\n";
            stageOneSolved = true;
        }
        else {
            ++stageOneFailures;

            cout << "The Ghosts Laugh At You. Try again.\n";

            displayGhostHint(stageOneFailures,
                             selected.firstHint,
                             selected.firstAnswer);
        }
    }

    // Stage 2: Solve the second sequence.
    while (!stageTwoSolved) {
        cout << "\n--- Stage 2: Two Fingers Remain ---\n";
        displaySequence(selected.secondSequence);
        cout << "Enter the missing number: ";

        answer = getPuzzleAnswer();

        if (answer == selected.secondAnswer) {
            cout << "Correct! The second seal breaks.\n";
            cout << "Two answers now rest in your memory.\n";
            stageTwoSolved = true;
        }
        else {
            ++stageTwoFailures;

            cout << "The Ghosts Cry In Agony. Try again.\n";

            displayGhostHint(stageTwoFailures,
                             selected.secondHint,
                             selected.secondAnswer);
        }
    }

    // Stage 3: Combine both answers.
    const int finalAnswer =
        selected.firstAnswer + selected.secondAnswer;

    while (!puzzleSolved) {
        cout << "\n--- Stage 3: One Hand Remains ---\n";
        cout << "Two answers spoken, one lock in the distance.\n";
        cout << "Unite what broke the seals, and the path shall open.\n";
        cout << "Enter the final answer: ";

        answer = getPuzzleAnswer();

        if (answer == finalAnswer) {
            cout << "\nThey rejoice!\n";
            cout << "The final lock clicks open.\n";
            cout << "Your escape-code digit is "
                 << ESCAPE_CODE_DIGIT << ".\n";

            puzzleSolved = true;
        }
        else {
            ++finalStageFailures;

            cout << "They Beg to Differ. Try again.\n";

            displayGhostHint(
                finalStageFailures,
                "Combine the two numbers that opened the seals.",
                finalAnswer
                );
        }
    }

    return ESCAPE_CODE_DIGIT;
}
}
// Temporary launcher for standalone testing.
int main()
{
    puzzle2();
    return 0;
}
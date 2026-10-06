# Escape Room Puzzle Game

A C++ text adventure. The player switches between two rooms: a **clue room** with the
exit door, and a **puzzle room** where the math puzzles happen. Each solved puzzle
reveals one number of the exit code. Solve all four, enter the code, and escape.

## Team

| Member | Responsibility | File |
|---|---|---|
| TBD | Puzzle #1 | `src/puzzle1.cpp` |
| TBD | Puzzle #2 | `src/puzzle2.cpp` |
| TBD | Puzzle #3 | `src/puzzle3.cpp` |
| TBD | Puzzle #4 | `src/puzzle4.cpp` |
| TBD | Rooms, progress tracker, exit code | `src/game.cpp` |

## Project structure

```
escape-room-game/
├── include/
│   ├── puzzles.h      shared puzzle function declarations
│   └── game.h         game setup declarations
├── src/
│   ├── main.cpp       starts the game
│   ├── game.cpp       rooms, progress tracker, exit code
│   ├── puzzle1.cpp
│   ├── puzzle2.cpp
│   ├── puzzle3.cpp
│   └── puzzle4.cpp
├── docs
├── CMakeLists.txt
└── README.md
```

## Puzzle rules (so everything fits together)

- Each puzzle is one function in its own file: `int puzzleN()`.
- It runs until the player solves it, then **returns its code number**.
- It must not end the program or call the other puzzles.
- Only edit your own file. Ask before changing `puzzles.h` or `game.h`.

## How to build and run

With g++:
```
g++ -std=c++17 -Iinclude src/*.cpp -o escape
./escape
```

With CMake:
```
cmake -S . -B build
cmake --build build
./build/escape
```

## How we work in GitHub

1. Pull the latest code before you start: `git pull`
2. Make a branch for your part: `git checkout -b puzzle2-zach`
3. Commit as you go: `git add src/puzzle2.cpp` then `git commit -m "Add sequence puzzle"`
4. Push your branch: `git push -u origin puzzle2-zach`
5. Open a **Pull Request** on GitHub into `main`, and have one teammate review it.
6. Make sure the program still builds before merging.

Never push straight to `main`.

## Timeline

- Base program: within ~2 weeks
- Testing as pieces are merged
- Final due: Module 8

//
// Created by gatyw on 5/4/2023.
//

#include "Driver.h"
#include "Space.h"
#include <iostream>

using namespace std;

int Driver::getStartInput() {
    cout << "Action: N)ew game, run in D)ebug mode, Q)uit: ";
    char action;
    cin >> action;
    cout << endl;
    if((char)tolower(action) == 'n') {
        board = new GameBoard();
        player = board->playerSetup();
    } else if((char)tolower(action) == 'd') {
        debug = true;
        board = new GameBoard();
        player = board->playerSetup();
    } else if((char)tolower(action) == 'q') {
        return 0;
    } else {
        cout << "Unrecognized command." << endl;
        getStartInput();
    }
    return 1;
}

int Driver::getInput() {
    if(debug) {
        printBoard();
    }
    player->printInfo();
    player->surveySurroundings();
    cout << "Action: M)ove, S)hoot, H)elp, Q)uit: ";
    char action;
    cin >> action;
    if((char)tolower(action) == 'm') {
        bool valid = false;
        while(!valid) {
            valid = inputAction(true);
        }
    } else if((char)tolower(action) == 's') {
        bool valid = false;
        while(!valid) {
            valid = inputAction(false);
        }
    } else if ((char)tolower(action) == 'h') {
        printHelp();
    } else if ((char)tolower(action) == 'q') {
        return 0;
    } else {
        cout << "Unrecognized command." << endl;
        getInput();
    }
    return 1;
}

bool Driver::inputAction(bool moveOrShoot) {
    cout << "Direction: N)orth, E)ast, S)outh, W)est: ";
    char direction;
    cin >> direction;
    cout << endl;
    char d = (char)(tolower(direction));
    return player->action(d, moveOrShoot);
}

void Driver::printHelp() {
    cout << "Rules list:" << endl;
    cout << "1. You will be alerted when you are within 2 spaces of the Wumpus" << endl;
    cout << "2. You will be warned when you are within 1 space of the Wumpus" << endl;
    cout << "3. You will be warned when you are within 1 space of a pit or a swam of bats" << endl;
    cout << "4. You will be notified when you are at the edge of the map" << endl;
    cout << "5. You start with 3 arrows that you can use to kill the Wumpus" << endl;
    cout << "6. There are 3-4 more arrows around the map that you can collect" << endl;
    cout << "7. There are 4 keys on the map that you can collect" << endl;
    cout << "8. If you have collected all 4 keys and find the cave exit, you can flee" << endl;
    cout << "9. You can win the game by either killing the Wumpus or fleeing the cave\n" << endl;
    cout << "Map symbols in debug mode:" << endl;
    cout << "H: hero (player)" << endl;
    cout << "W: Wumpus" << endl;
    cout << "B: bats" << endl;
    cout << "P: pit" << endl;
    cout << "A: arrow" << endl;
    cout << "K: key" << endl;
    cout << "E: exit" << endl;
    cout << ".: empty space" << endl;
    cout << "\n" << endl;
}

void Driver::printBoard() {
    for(int r = 0; r < 6; ++r) {
        for(int c = 0; c < 6; ++c) {
            cout << board->get(r, c)->token << " ";
        }
        cout << endl;
    }
}

Driver::~Driver() = default;

Driver::Driver() = default;

int main() {
    Driver driver = Driver();
    int running = driver.getStartInput();
    while(running == 1) {
        running = driver.getInput();
        if(driver.player->gameOver) {
            running = 0;
            if(driver.player->won) {
                cout << "You won!" << endl;
            } else {
                cout << "You lost!" << endl;
            }
        }
    }
    return 0;
}
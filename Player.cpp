//
// Created by gatyw on 5/4/2023.
//

#include "Player.h"
#include "Space.h"
#include "GameBoard.h"
#include <iostream>

using namespace std;

bool Player::moveDir(int dir) {
    Space* n = currentSpace->getNeighbor(dir);
    if(!n) {
        cout << "You run into a wall!" << endl;
    } else {
        moveTo(n);
        if(n->hasHazard()) {
            if(n->hasBats()) {
                cout << "You got carried to a new position by a swarm of bats! ";
                moveTo(n->getHazard()->movePlayer());
                n->remove();
            } else if(n->isPit()) {
                cout << "You fell to your death in a pit!" << endl;
                gameOver = true;
            } else if(n->hasWumpus()) {
                cout << "You were eaten by the wumpus!" << endl;
                gameOver = true;
            }
        } else if(n->hasCollectible()) {
            if(n->hasKey()) {
                cout << "You picked up a key! ";
                numKeys++;
            } else { //safe to assume it's an arrow
                cout << "You picked up an arrow! ";
                numArrows++;
            }
        } else if(n->isExit()) {
            if(numKeys == 4) {
                cout << "You found a door, and opened it with your keys!" << endl;
                gameOver = true;
                won = true;
            }
        }
    }
    cout << endl;
    return true;
}

void Player::printInfo() {
    cout << "You have " << numArrows << " arrows remaining. You have collected " << numKeys << " out of 4 keys." << endl;
}

bool Player::checkForBats() {
    for(int d = 0; d < 4; ++d) {
        if(currentSpace->getNeighbor(d)) {
            if(currentSpace->getNeighbor(d)->hasBats()) {
                return true;
            }
        }
    }
    return false;
}

bool Player::checkForPit() {
    for(int d = 0; d < 4; ++d) {
        if(currentSpace->getNeighbor(d)) {
            if(currentSpace->getNeighbor(d)->isPit()) {
                return true;
            }
        }
    }
    return false;
}

int Player::checkForWumpus() {
    for(int d = 0; d < 4; ++d) {
        if(currentSpace->getNeighbor(d)) {
            if(currentSpace->getNeighbor(d)->hasWumpus()) {
                return 1;
            }
            if(currentSpace->getNeighbor(d)->getNeighbor(d)) {
                if(currentSpace->getNeighbor(d)->getNeighbor(d)->hasWumpus()) {
                    return 2;
                }
            }
        }
    }
    return 0;
}

void Player::surveySurroundings() {
    string batsString;
    string wumpusString;
    string exitString;
    string pitString;
    string wallsString;
    if(currentSpace->isExit()) {
        if(numKeys != 4) {
            exitString = "You found a door, but it's locked! ";
        }
    } else {
        if(currentSpace->isEdge()) {
            wallsString = "You feel the cave wall next to you. ";
        }
    }
    if(checkForWumpus() == 1) {
        wumpusString = "You smell the overwhelming stench of the Wumpus! ";
    } else if(checkForWumpus() == 2) {
        wumpusString = "You smell a faint whiff of the Wumpus. ";
    }
    if(checkForPit()) {
        pitString = "You feel a draft. ";
    }
    if(checkForBats()) {
        batsString = "You hear flapping nearby. ";
    }
    if((exitString + wallsString + batsString + pitString + wumpusString).empty()) {
        cout << "You can barely see a few feet in front of you, but you sense nothing nearby." << endl;
    } else {
        cout << exitString << wallsString << batsString << pitString << wumpusString << endl;
    }
}

bool Player::shootDir(int dir) {
    if(numArrows < 1) {
        cout << "You're out of arrows!" << endl;
    } else {
        Space* n = currentSpace->getNeighbor(dir);
        if(!n) {
            cout << "Your arrow hit the wall!" << endl;
        } else {
            if(n->hasWumpus()) {
                cout << "You killed the wumpus!" << endl;
                gameOver = true;
                won = true;
            } else {
                cout << "Your arrow whistled into emptiness!" << endl;
            }
        }
        numArrows--;
    }
    return true;
}

bool Player::actionN(bool moveOrShoot) {
    if(moveOrShoot) { //if move
        moveDir(0);
    } else { //else shoot
        shootDir(0);
    }
    return true;
}

bool Player::actionE(bool moveOrShoot) {
    if(moveOrShoot) { //if move
        moveDir(1);
    } else { //else shoot
        shootDir(1);
    }
    return true;
}

bool Player::actionS(bool moveOrShoot) {
    if(moveOrShoot) { //if move
        moveDir(2);
    } else { //else shoot
        shootDir(2);
    }
    return true;
}

bool Player::actionW(bool moveOrShoot) {
    if(moveOrShoot) { //if move
        moveDir(3);
    } else { //else shoot
        shootDir(3);
    }
    return true;
}

bool Player::action(char dir, bool moveOrShoot) {
    if(dir == 'n') {
        actionN(moveOrShoot);
    } else if(dir == 'e') {
        actionE(moveOrShoot);
    } else if(dir == 's') {
        actionS(moveOrShoot);
    } else if(dir == 'w') {
        actionW(moveOrShoot);
    } else {
        cout << "Unrecognized direction." << endl;
        return false;
    }
    return true;
}

void Player::moveTo(Space* s) {
    currentSpace->remove();
    currentSpace = s;
    currentSpace->playerEnter();
}

Player::~Player() = default;

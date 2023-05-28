//
// Created by gatyw on 5/4/2023.
//

#ifndef LAB_6_7_DRIVER_H
#define LAB_6_7_DRIVER_H

#include "GameBoard.h"
#include "Player.h"

//note to self: I'm thinking that gameBoard can function as a driver
class Driver {
public:
    Driver();
    ~Driver();
    void printBoard();
    int getInput();
    bool inputAction(bool moveOrShoot);
    int getStartInput();
    void printHelp();
    GameBoard* board;
    Player* player;
private:
    bool debug = false;
    bool running = false;
};

#endif //LAB_6_7_DRIVER_H

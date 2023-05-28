//
// Created by gatyw on 5/4/2023.
//

#include "GameBoard.h"
#include "Bats.h"
#include "Hazard.h"
#include "Pit.h"
#include "Player.h"
#include "Space.h"
#include "Wumpus.h"

using namespace std;

GameBoard::GameBoard() {
    std::srand(time(0));
    setup();
}

void GameBoard::boardSetup() {
    //6x6 game board
    for(int r = 0; r < 6; ++r) {
        for(int c = 0; c < 6; ++c) {
            auto* temp = new Space(r, c);
            board[r][c] = temp;
        }
    }
}

void GameBoard::neighborSetup() {
    for(int r = 0; r < 6; ++r) {
        for(int c = 0; c < 6; ++c) {
            if(r > 0) {
                board[r][c]->addNeighbor(0, board[r-1][c]);
            }
            if(c < 5) {
                board[r][c]->addNeighbor(1, board[r][c+1]);
            }
            if(r < 5) {
                board[r][c]->addNeighbor(2, board[r+1][c]);
            }
            if(c > 0) {
                board[r][c]->addNeighbor(3, board[r][c-1]);
            }
        }
    }
}

void GameBoard::exitSetup() {
    //0 for rows, 1 for cols
    int exitDim = rand() % 2 + 1;
    //0 for left/top, 1 for right/bottom
    int exitSide = rand() % 2 + 1;
    int exitSpace = rand() % 6;
    if(exitDim == 0) {
        if(exitSide == 0) {
            board[0][exitSpace]->setIsExit(true);
        } else {
            board[5][exitSpace]->setIsExit(true);
        }
    } else {
        if(exitSide == 0) {
            board[exitSpace][0]->setIsExit(true);
        } else {
            board[exitSpace][5]->setIsExit(true);
        }
    }
}

void GameBoard::collectibleSetup() {
    //keys
    for(int k = 0; k < 4; ++k) {
        bool placed = false;
        while(!placed) {
            int x = rand() % 6;
            int y = rand() % 6;
            if(board[x][y]->isEmpty()) {
                board[x][y]->addKey();
                placed = true;
            }
        }
    }

    //arrows
    int numArrows = 2 + (rand() % 2);
    for(int a = 0; a < numArrows; ++a) {
        bool placed = false;
        while(!placed) {
            int x = rand() % 6;
            int y = rand() % 6;
            if(board[x][y]->isEmpty()) {
                board[x][y]->addArrow();
                placed = true;
            }
        }
    }
}

void GameBoard::hazardSetup() {
    //wumpus
    bool placed = false;
    while(!placed) {
        int x = rand() % 6;
        int y = rand() % 6;
        if(board[x][y]->isEmpty()) {
            auto* w = new Wumpus(board[x][y]);
            board[x][y]->addHazard(w, 0);
            placed = true;
        }
    }

    //pits
    for(int i = 0; i < 2; ++i) {
        placed = false;
        while(!placed) {
            int x = rand() % 6;
            int y = rand() % 6;
            if(board[x][y]->isEmpty()) {
                auto* p = new Pit(board[x][y]);
                board[x][y]->addHazard(p, 2);
                placed = true;
            }
        }
    }

    //bats
    for(int i = 0; i < 2; ++i) {
        placed = false;
        while(!placed) {
            int x = rand() % 6;
            int y = rand() % 6;
            if(board[x][y]->isEmpty()) {
                Space* batsSpace;
                bool batsPlaced = false;
                while(!batsPlaced) {
                    int bx = rand() % 6;
                    int by = rand() % 6;
                    if(board[bx][by]->isEmpty()) {batsSpace = board[bx][by]; batsPlaced = true;}
                }
                auto* b = new Bats(board[x][y], batsSpace);
                board[x][y]->addHazard(b, 1);
                placed = true;
            }
        }
    }
}

Player* GameBoard::playerSetup() {
    bool placed = false;
    while(!placed) {
        int x = rand() % 6;
        int y = rand() % 6;
        if(board[x][y]->isEmpty()) {
            player = new Player(board[x][y], 0, 3);
            board[x][y]->playerEnter();
            placed = true;
        }
    }
    return player;
}

void GameBoard::setup() {
    boardSetup();
    neighborSetup();
    exitSetup();
    collectibleSetup();
    hazardSetup();
}

GameBoard::~GameBoard() = default;

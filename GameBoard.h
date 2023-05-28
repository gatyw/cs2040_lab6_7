//
// Created by gatyw on 5/4/2023.
//

#ifndef LAB_6_7_GAMEBOARD_H
#define LAB_6_7_GAMEBOARD_H

class Player;
class Wumpus;
class Space;
#include <vector>

class GameBoard {
public:
    GameBoard();
    ~GameBoard();
    void setup();
    void boardSetup();
    void neighborSetup();
    Player* playerSetup();
    void exitSetup();
    void collectibleSetup();
    void hazardSetup();
    Space* get(int x, int y) {return board[x][y];}
private:
    //std::vector<std::vector<Space*>> board;
    Space *board[6][6];
    Player* player;
    Wumpus* wumpus;
};

#endif //LAB_6_7_GAMEBOARD_H

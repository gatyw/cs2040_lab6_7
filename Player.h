//
// Created by gatyw on 5/4/2023.
//

#ifndef LAB_6_7_PLAYER_H
#define LAB_6_7_PLAYER_H

class GameBoard;
class Space;
#include <iostream>

using namespace std;

class Player {
public:
    Player(Space* s, int k, int a) {
        currentSpace = s;
        numKeys = k;
        numArrows = a;
    }
    ~Player();

    //for the following 4 methods: move = true, shoot = false
    bool actionN(bool moveOrShoot);
    bool actionE(bool moveOrShoot);
    bool actionS(bool moveOrShoot);
    bool actionW(bool moveOrShoot);
    bool action(char dir, bool moveOrShoot);
    void printInfo();
    void surveySurroundings();
    int checkForWumpus();
    bool checkForBats();
    bool checkForPit();
    bool moveDir(int dir);
    bool shootDir(int dir);
    void moveTo(Space* s);
    bool won = false;
    bool gameOver = false;
private:
    Space* currentSpace;
    int numArrows;
    int numKeys;
};

#endif //LAB_6_7_PLAYER_H

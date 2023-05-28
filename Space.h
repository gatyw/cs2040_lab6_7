//
// Created by gatyw on 5/4/2023.
//

#ifndef LAB_6_7_SPACE_H
#define LAB_6_7_SPACE_H

#include "Hazard.h"

class Space {
public:
    Space(int x, int y);
    ~Space();
    bool hasHazard() {if(hazard) {return true;} else {return false;}};
    bool isEmpty() {if(!hasCollectible() && !hasHazard() && !isExit()) {return true;} else {return false;}}
    //hazard types: 0 = wumpus, 1 = bats, 2 = pit
    bool addHazard(Hazard* h, int type) {
        if(isEmpty()) {
            hazard = h;
            token = h->token;
            if(type == 0) {wumpus = true;} else if(type == 1) {bats = true;} else {pit = true;}
            return true;
        } else {return false;}};
    void remove() {token = '.';}
    bool hasCollectible() {return arrow || key;}
    bool hasArrow() {return arrow;}
    bool hasKey() {return key;}
    bool isExit() {return exit;};
    void setIsExit(bool val) {exit = val; token = 'E';}
    void addKey() {key = true; token = 'K';}
    void removeKey() {key = false; remove();}
    void addArrow() {arrow = true; token = 'A';}
    void removeArrow() {arrow = false; remove();}
    void addNeighbor(int dir, Space* n) {neighbors[dir] = n;}
    bool hasWumpus() {return wumpus;}
    bool hasBats() {return bats;}
    bool isPit() {return pit;}
    Space* getNeighbor(int dir) {return neighbors[dir];}
    void playerEnter() {token = 'H';}
    Hazard* getHazard() {return hazard;}
    bool isEdge() {return (posX == 0 || posX == 5 || posY == 0 || posY == 5);}
    char token = '.';
private:
    int posX;
    int posY;
    bool exit = false;
    bool arrow = false;
    bool key = false;
    bool wumpus = false;
    bool bats = false;
    bool pit = false;
    Space** neighbors = new Space*[4]();
    Hazard* hazard = nullptr;
};

#endif //LAB_6_7_SPACE_H

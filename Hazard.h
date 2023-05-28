//
// Created by gatyw on 5/4/2023.
//

#ifndef LAB_6_7_HAZARD_H
#define LAB_6_7_HAZARD_H

#include <string>
class Space;
//#include "Space.h"

class Hazard {
public:
    Hazard(Space* s) {space = s; token = '.';};
    ~Hazard();

    virtual Space* movePlayer() {return space;};
    char token;
private:
    Space* space;
};

#endif //LAB_6_7_HAZARD_H

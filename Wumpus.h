//
// Created by gatyw on 5/4/2023.
//

#ifndef LAB_6_7_WUMPUS_H
#define LAB_6_7_WUMPUS_H

#include "Hazard.h"

class Wumpus : public Hazard {
public:
    using Hazard::Hazard;
    Wumpus(Space* s) : Hazard(s) {token = 'W';};
    ~Wumpus();
};

#endif //LAB_6_7_WUMPUS_H

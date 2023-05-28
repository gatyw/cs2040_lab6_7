//
// Created by gatyw on 5/4/2023.
//

#ifndef LAB_6_7_PIT_H
#define LAB_6_7_PIT_H

#include "Hazard.h"

class Pit: public Hazard {
public:
    using Hazard::Hazard;
    Pit(Space* s) : Hazard(s) {token = 'P';};
    ~Pit();
};

#endif //LAB_6_7_PIT_H

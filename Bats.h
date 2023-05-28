//
// Created by gatyw on 5/4/2023.
//

#ifndef LAB_6_7_BATS_H
#define LAB_6_7_BATS_H

#include <string>
#include "Hazard.h"

class Bats : public Hazard {
public:
    using Hazard::Hazard;
    Bats(Space *s, Space* m) : Hazard(s) {
        moveTo = m;
        token = 'B';
    };
    ~Bats();
    Space* movePlayer() override {return moveTo;};
private:
    Space* moveTo;
};

#endif //LAB_6_7_BATS_H

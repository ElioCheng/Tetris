#ifndef LEVEL0_H
#define LEVEL0_H

#include <string>
#include <vector>
#include "Level.h"
using namespace std;

class Level0 : public Level {
    int index;
    vector<char> sequence;
public:
    Level0(string name);
    Block * generateBlock() override;
};

#endif //LEVEL0_H

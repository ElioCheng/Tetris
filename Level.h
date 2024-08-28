#ifndef LEVEL_H
#define LEVEL_H

#include <string>
using namespace std;

class Block;

class Level {
public:
    Block * createBlock(char name);
    virtual Block * generateBlock() = 0;
    virtual ~Level() = 0;
};

#endif 

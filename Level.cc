#include "Level.h"
#include "IBlock.h"
#include "JBlock.h"
#include "LBlock.h"
#include "OBlock.h"
#include "SBlock.h"
#include "TBlock.h"
#include "ZBlock.h"
#include "StarBlock.h"

using namespace std;

Block * Level::createBlock(char name) {
    if (name == 'I') {
        return new IBlock;
    } else if (name == 'J') {
        return new JBlock;
    } else if (name == 'L') {
        return new LBlock;
    } else if (name == 'O') {
        return new OBlock;
    } else if (name == 'S') {
        return new SBlock;
    } else if (name == 'T') {
        return new TBlock;
    } else if (name == 'Z') {
        return new ZBlock;
    } else if (name == '*') {
        return new StarBlock;
    } else {
        return nullptr;
    }
}

Level::~Level() = default;

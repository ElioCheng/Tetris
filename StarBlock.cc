#include "StarBlock.h"
using namespace std;

StarBlock::StarBlock() : name('*'), heavyBlock(false)  {
    Xcoordinate.resize(1);
    Ycoordinate.resize(1);
}

StarBlock::~StarBlock() {}

StarBlock* StarBlock::getPtr() {
    return new StarBlock(*this);
}

bool StarBlock::getState() {
    return heavyBlock;
}

void StarBlock::setState(bool state) {
    heavyBlock = state;
}

char StarBlock::getType() {
    return name;
}

void StarBlock::set(string judge, int index, int num) {
    if (judge == "X") {
        Xcoordinate[index] = num;
    } else if (judge == "Y") {
        Ycoordinate[index] = num;
    }
}

int StarBlock::get(string judge, int index) {
    if (judge == "X") {
        return Xcoordinate[index];
    } else if (judge == "Y") {
        return Ycoordinate[index];
    }
    return 0;
}

bool StarBlock::exist(int Xvalue, int Yvalue) {
    for (int i = 0; i < 1; i++) {
        if(Xcoordinate[i] == Xvalue && Ycoordinate[i] == Yvalue) {
            return true;
        }
    }
    return false;
}

Block* StarBlock::getCopy(Block* copy) {
    for (int i = 0; i < 1; i++) {
        int x = this->get("X", i);
        copy->set("X", i , x);
        int y = this->get("Y", i);
        copy->set("Y", i , y);
        bool state = this->getState();
        copy->setState(state);
    }
    return copy;
}

void StarBlock::CW() {
    return;
}

#include "OBlock.h"
using namespace std;

OBlock::OBlock() : name('O'), heavyBlock(false)  {
    Xcoordinate.resize(4);
    Ycoordinate.resize(4);
    rotate = 0;
}

OBlock::~OBlock() {}

bool OBlock::getState() {
    return heavyBlock;
}

void OBlock::setState(bool state) {
    heavyBlock = state;
}

void OBlock::set(string judge, int index, int num) {
    if (judge == "X") {
        Xcoordinate[index] = num;
    } else if (judge == "Y") {
        Ycoordinate[index] = num;
    }
}

int OBlock::get(string judge, int index) {
    if (judge == "X") {
        return Xcoordinate[index];
    } else if (judge == "Y") {
        return Ycoordinate[index];
    }
    return 0;
}

bool OBlock::exist(int Xvalue, int Yvalue) {
    for (int i = 0; i < 4; i++) {
        if(Xcoordinate[i] == Xvalue && Ycoordinate[i] == Yvalue) {
            return true;
        }
    }
    return false;
}

char OBlock::getType() {
    return name;
}

Block* OBlock::getCopy(Block* copy) {
    for (int i = 0; i < 4; i++) {
        int x = this->get("X", i);
        copy->set("X", i , x);
        int y = this->get("Y", i);
        copy->set("Y", i , y);
        bool state = this->getState();
        copy->setState(state);
    }
    return copy;
}

void OBlock::CW() {
    // no rotation for O block
}

OBlock* OBlock::getPtr() {
    return new OBlock(*this);
}

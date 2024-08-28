#include "IBlock.h"
using namespace std;

IBlock::IBlock() : name('I'), heavyBlock(false) {
    rotate = 0;
    Xcoordinate.resize(4);
    Ycoordinate.resize(4);
}

IBlock::~IBlock() {}

char IBlock::getType() {
    return name;
}

bool IBlock::getState() {
    return heavyBlock;
}

void IBlock::setState(bool state) {
    heavyBlock = state;
}

void IBlock::set(string judge, int index, int num) {
    if (judge == "X") {
        Xcoordinate[index] = num;
    } else if (judge == "Y") {
        Ycoordinate[index] = num;
    }
}

int IBlock::get(string judge, int index) {
    if (judge == "X") {
        return Xcoordinate[index];
    } else if (judge == "Y") {
        return Ycoordinate[index];
    }
    return 0;
}

bool IBlock::exist(int Xvalue, int Yvalue) {
    for (int i = 0; i < 4; i++) {
        if(Xcoordinate[i] == Xvalue && Ycoordinate[i] == Yvalue) {
            return true;
        }
    }
    return false;
}

Block* IBlock::getCopy(Block* copy) {
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

void IBlock::CW() {
    int x = 17;
    int y = 10;
    for (int i = 0; i < 4; i++) {
        int newx = Xcoordinate[i];
        int newy = Ycoordinate[i];
        if (newx < x) {
            x = newx;
        }
        if (newy < y) {
            y = newy;
        }
    }
    if (rotate == 0 && x - 3 >= 0) {
        for (int i = 0; i < 4; i++) {
            set("X", i, x - i);
            set("Y", i, y);
        }
        rotate++;
    } else if (rotate == 1 && y + 3 <= 10) {
        for (int i = 0; i < 4; i++) {
            set("X", i, x);
            set("Y", i, y + i);
        }
        rotate++;
    } else if (rotate == 2 && x + 3 <= 17) {
        for (int i = 0; i < 4; i++) {
            set("X", i, x + i);
            set("Y", i, y + 3);
        }
        rotate++;
    } else if (rotate == 3 && y - 3 >= 0) {
        for (int i = 0; i < 4; i++) {
            set("X", i, x + 3);
            set("Y", i, y - i);
        }
        rotate = 0;
    }
    return;
}

IBlock* IBlock::getPtr() {
    return new IBlock(*this);
}

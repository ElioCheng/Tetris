#include "LBlock.h"
using namespace std;

LBlock::LBlock() : name('L'), heavyBlock(false)  {
    Xcoordinate.resize(4);
    Ycoordinate.resize(4);
    rotate = 0;
}

LBlock::~LBlock() {}

bool LBlock::getState() {
    return heavyBlock;
}

void LBlock::setState(bool state) {
    heavyBlock = state;
}

void LBlock::set(string judge, int index, int num) {
    if (judge == "X") {
        Xcoordinate[index] = num;
    } else if (judge == "Y") {
        Ycoordinate[index] = num;
    }
}

int LBlock::get(string judge, int index) {
    if (judge == "X") {
        return Xcoordinate[index];
    } else if (judge == "Y") {
        return Ycoordinate[index];
    }
    return 0;
}

bool LBlock::exist(int Xvalue, int Yvalue) {
    for (int i = 0; i < 4; i++) {
        if(Xcoordinate[i] == Xvalue && Ycoordinate[i] == Yvalue) {
            return true;
        }
    }
    return false;
}

char LBlock::getType() {
    return name;
}

Block* LBlock::getCopy(Block* copy) {
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

void LBlock::CW() {
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
    if (rotate == 0 && x - 1 >= 0) {
        set("X", 0, x + 1);
        set("Y", 0, y + 1);
        set("X", 1, x + 1);
        set("Y", 1, y);
        set("X", 2, x);
        set("Y", 2, y);
        set("X", 3, x - 1);
        set("Y", 3, y);
        rotate++;
    } else if(rotate == 1 && y + 1 <= 10) {
        set("X", 0, x);
        set("Y", 0, y);
        set("X", 1, x + 1);
        set("Y", 1, y);
        set("X", 2, x);
        set("Y", 2, y + 1);
        set("X", 3, x);
        set("Y", 3, y + 2);
        rotate++;
    } else if(rotate == 2 && x + 1 <= 17) {
        set("X", 0, x);
        set("Y", 0, y + 1);
        set("X", 1, x);
        set("Y", 1, y + 2);
        set("X", 2, x + 1);
        set("Y", 2, y + 2);
        set("X", 3, x + 2);
        set("Y", 3, y + 2);
        rotate++;
    } else if(rotate == 3 && y - 1 >= 0) {
        set("X", 0, x + 1);
        set("Y", 0, y + 1);
        set("X", 1, x + 2);
        set("Y", 1, y + 1);
        set("X", 2, x + 2);
        set("Y", 2, y);
        set("X", 3, x + 2);
        set("Y", 3, y - 1);
        rotate = 0;
    }
    return;
}

LBlock* LBlock::getPtr() {
    return new LBlock(*this);
}


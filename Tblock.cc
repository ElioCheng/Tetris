#include "TBlock.h"
using namespace std;

TBlock::TBlock() : name('T') {
    // Initialize the Block with spaces
    grid = {
        {" ", " ", " ", " "},
        {" ", " ", " ", " "},
        {"T", "T", "T", " "},
        {" ", "T", " ", " "}
    };
}

TBlock::~TBlock() {}

TBlock* TBlock::getPtr() {
    return new TBlock(*this);
}

char TBlock::getType() {
    return name;
} 
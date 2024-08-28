#include "Level5.h"
#include "Block.h"
#include <cstdlib>
#include <string>
using namespace std;

Level5::Level5() {}

Block* Level5::generateBlock() {
    int num = rand() % 9;
    char pixel;
    if (num == 0) {
        pixel = 'I';
    } else if (num == 1) {
        pixel = 'J';
    } else if (num == 2) {
        pixel = 'L';
    } else if (num == 3) {
        pixel = 'O';
    } else if (num == 4) {
        pixel = 'T';
    } else if (num == 5 || num == 6) {
        pixel = 'S';
    } else if (num == 7 || num == 8) {
        pixel = 'Z';
    }
    Block *newBlock = createBlock(pixel);
    newBlock->setState(true);
    return newBlock;
}

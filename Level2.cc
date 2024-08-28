#include "Level2.h"
#include <cstdlib>
#include <string>
using namespace std;

Level2::Level2() {}

Block * Level2::generateBlock() {
    int num = rand() % 7;
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
    } else if (num == 5) {
        pixel = 'S';
    } else if (num == 6) {
        pixel = 'Z';
    }
    Block * newBlock = createBlock(pixel);
    return newBlock;
}

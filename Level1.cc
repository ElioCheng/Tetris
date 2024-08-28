#include "Level1.h"
#include <cstdlib>
#include <string>
using namespace std;

Level1::Level1() {}

Block * Level1::generateBlock() {
    int num = rand() % 6;
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
    } else {
        int get = rand() % 2;
        if (get == 0) {
            pixel = 'S';
        } else {
            pixel = 'Z';
        }
    }
    Block * newBlock = createBlock(pixel);
    return newBlock;
}

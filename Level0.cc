#include <cstdlib>
#include <fstream>
#include <string>

#include "Level0.h"

using namespace std;

Level0::Level0(string sequence): // Add each letter from input file to a vector
    index{0} { // set sequence based on player
    ifstream file{sequence};
    char letter;
    while (file >> letter) {
        this->sequence.push_back(letter);
    }
}

Block * Level0::generateBlock() {
    char num = sequence[index];
    Block * newBlock = createBlock(num);
    index++; 
    int size = sequence.size();
    if (index >= size) {
        index = 0;
    }
    return newBlock;
}
 


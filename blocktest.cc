#include "Block.h"
#include "IBlock.h"
#include "JBlock.h"
#include <iostream>
using namespace std;
int main() {
    // Create an IBlock
    IBlock iBlock;
    JBlock jBlock;
    std::cout << "Initial IBlock:\n";
    iBlock.printGrid();
    cout << endl;
    jBlock.printGrid();    

    // Rotate the block clockwise and print
    iBlock.rotateCW();
    jBlock.rotateCW();
    std::cout << "IBlock after CW rotation:\n";
    iBlock.printGrid();
    jBlock.printGrid();
    // Rotate the block counter-clockwise and print
    iBlock.rotateCCW();
    jBlock.rotateCW();
    std::cout << "IBlock after CCW rotation:\n";
    iBlock.printGrid();
    jBlock.printGrid();

    // Test getType
    std::cout << "Type of block: " << iBlock.getType() << "\n";
    std::cout << "Type of block: " << jBlock.getType() << "\n";
    return 0;
}

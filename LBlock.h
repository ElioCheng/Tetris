#ifndef LBlock_h
#define LBlock_h

#include "Block.h"
#include <string>
#include <vector>
using namespace std;

class LBlock : public Block {
private:
    char name;
    vector<int> Xcoordinate;
    vector<int> Ycoordinate;
    int rotate;
    bool heavyBlock;

public:
    LBlock();
    ~LBlock();
    bool getState();
    void setState(bool state);
    void set(string judge, int index, int num) override;
    int get(string judge, int index) override;
    bool exist(int Xvalue, int Yvalue) override;
    char getType();
    Block* getCopy(Block* copy) override;
    void CW() override;
    LBlock* getPtr() override;
};

#endif

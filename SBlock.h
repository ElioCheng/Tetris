#ifndef SBlock_h
#define SBlock_h

#include "Block.h"
#include <string>
#include <vector>
using namespace std;

class SBlock : public Block {
private:
    char name;
    vector<int> Xcoordinate;
    vector<int> Ycoordinate;
    int rotate;
    bool heavyBlock;

public:
    SBlock();
    ~SBlock();
    bool getState();
    void setState(bool state);
    void set(string judge, int index, int num) override;
    int get(string judge, int index) override;
    bool exist(int Xvalue, int Yvalue) override;
    Block* getCopy(Block* copy) override;
    char getType();
    void CW() override;
    SBlock* getPtr() override;
};

#endif

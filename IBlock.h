#ifndef IBlock_h
#define IBlock_h

#include "Block.h"
#include <string>
#include <vector>
using namespace std;

class IBlock : public Block {
private:
    char name;
    vector<int> Xcoordinate;
    vector<int> Ycoordinate;
    int rotate;
    bool heavyBlock;

public:
    IBlock();
    ~IBlock();
    char getType();
    bool getState();
    void setState(bool state);
    void set(string judge, int index, int num) override;
    int get(string judge, int index) override;
    bool exist(int Xvalue, int Yvalue) override;
    Block* getCopy(Block* copy) override;
    void CW() override;
    IBlock* getPtr() override;
};

#endif

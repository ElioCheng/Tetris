#ifndef OBlock_h
#define OBlock_h

#include "Block.h"
#include <string>
#include <vector>
using namespace std;

class OBlock : public Block {
private:
    char name;
    vector<int> Xcoordinate;
    vector<int> Ycoordinate;
    int rotate;
    bool heavyBlock;

public:
    OBlock();
    ~OBlock();
    bool getState();
    void setState(bool state);
    void set(string judge, int index, int num) override;
    int get(string judge, int index) override;
    bool exist(int Xvalue, int Yvalue) override;
    char getType();
    Block* getCopy(Block* copy) override;
    void CW() override;
    OBlock* getPtr() override;
};

#endif

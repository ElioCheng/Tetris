#ifndef ZBlock_h
#define ZBlock_h

#include "Block.h"
#include <string>
#include <vector>

using namespace std;

class ZBlock : public Block {
private:
    char name;
    vector<int> Xcoordinate;
    vector<int> Ycoordinate;
    int rotate;
    bool heavyBlock;

public:
    ZBlock();
    virtual ~ZBlock();
    
    char getType();
    void set(string judge, int index, int num) override;
    int get(string judge, int index) override;
    bool exist(int Xvalue, int Yvalue) override;
    Block* getCopy(Block* copy) override;
    void CW() override;
    bool getState();
    void setState(bool state);
    ZBlock* getPtr() override;
};

#endif

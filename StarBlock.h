#ifndef STARBlock_h
#define STARBlock_h

#include "Block.h"
#include <string>
#include <vector>

using namespace std;

class StarBlock : public Block {
private:
    char name;
    vector<int> Xcoordinate;
    vector<int> Ycoordinate;
    bool heavyBlock;

public:
    StarBlock();
    virtual ~StarBlock();
    
    bool getState();
    void setState(bool state);
    char getType();

    void set(string judge, int index, int num) override;
    int get(string judge, int index) override;
    bool exist(int Xvalue, int Yvalue) override;
    Block* getCopy(Block* copy) override;
    void CW() override;

    StarBlock* getPtr() override;
};

#endif

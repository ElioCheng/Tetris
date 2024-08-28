#ifndef JBlock_h
#define JBlock_h

#include "Block.h"
#include <string>
#include <vector>
using namespace std;

class JBlock : public Block {
private:
    char name;
    vector<int> Xcoordinate;
    vector<int> Ycoordinate;
    int rotate;
    bool heavyBlock;

public:
    JBlock();
    ~JBlock();
    char getType();
    bool getState();
    void setState(bool state);
    void set(string judge, int index, int num) override;
    int get(string judge, int index) override;
    bool exist(int Xvalue, int Yvalue) override;
    Block* getCopy(Block* copy) override;
    void CW() override;
    JBlock* getPtr() override;
};

#endif

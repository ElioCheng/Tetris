#ifndef Block_h
#define Block_h
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

class Block {
public:
    Block() {};
    ~Block() {};
    virtual void CW() = 0;
    virtual void setState(bool state) = 0;
    virtual bool getState() = 0;
    virtual char getType() = 0;
    virtual Block* getPtr() = 0;
    virtual Block* getCopy(Block *copy) = 0;
    virtual void set(string judge, int index, int num) = 0;
    virtual int get(string judge, int index) = 0;
    virtual bool exist(int Xvalue, int Yvalue) = 0;
};

#endif

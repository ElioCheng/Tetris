#ifndef Board_hpp
#define Board_hpp

#include "Player.h"
#include <memory>


class Generalboard {
public:
    Generalboard();
    virtual ~Generalboard() = 0;
    virtual void generate(Player& player1, Player& player2) = 0;
};

#endif 

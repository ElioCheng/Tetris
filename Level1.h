#ifndef _LEVEL1_H_
#define _LEVEL1_H_
#include "Level.h"
#include <string>

class Level1 : public Level {
public:
    Level1();
    Block * generateBlock() override;
};

#endif

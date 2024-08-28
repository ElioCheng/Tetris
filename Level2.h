#ifndef _LEVEL2_H_
#define _LEVEL2_H_
#include "Level.h"
#include <string>

class Level2 : public Level {
    public:
    Level2();
    Block * generateBlock() override;
};

#endif

#ifndef _LEVEL4_H_
#define _LEVEL4_H_
#include "Level.h"
#include <string>

class Level4 : public Level {
    public:
    Level4();
    Block * generateBlock() override;
};

#endif

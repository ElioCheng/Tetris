#ifndef _LEVEL3_H_
#define _LEVEL3_H_
#include "Level.h"
#include <string>

class Level3 : public Level {
    public:
    Level3();
    Block * generateBlock() override;
};

#endif

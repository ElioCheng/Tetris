#ifndef _LEVEL5_H_
#define _LEVEL5_H_
#include "Level.h"
#include <string>

class Level5 : public Level {
    public:
    Level5();
    Block * generateBlock() override;
};

#endif

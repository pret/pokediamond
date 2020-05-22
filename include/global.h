#ifndef GUARD_GLOBAL_H
#define GUARD_GLOBAL_H

#include "function_target.h"
#include "nitro.h"

enum GameVersion {
    VERSION_SAPPHIRE   =  1,
    VERSION_RUBY       =  2,
    VERSION_EMERALD    =  3,
    VERSION_FIRE_RED   =  4,
    VERSION_LEAF_GREEN =  5,
    VERSION_DIAMOND    = 10,
};

enum GameLanguage {
    LANGUAGE_JAPANESE   = 1,
    LANGUAGE_ENGLISH    = 2,
};

extern void ErrorHandling(void);

#endif //GUARD_GLOBAL_H

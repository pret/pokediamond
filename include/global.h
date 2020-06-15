#ifndef GUARD_GLOBAL_H
#define GUARD_GLOBAL_H

#include "config.h"
#include "function_target.h"
#include "nitro.h"

#define NELEMS(a) (sizeof(a) / sizeof(*(a)))

enum GameVersion {
    VERSION_SAPPHIRE   =  1,
    VERSION_RUBY       =  2,
    VERSION_EMERALD    =  3,
    VERSION_FIRE_RED   =  4,
    VERSION_LEAF_GREEN =  5,
    VERSION_DIAMOND    = 10,
    VERSION_PEARL      = 11,
};

enum GameLanguage {
    LANGUAGE_JAPANESE   = 1,
    LANGUAGE_ENGLISH    = 2,
    LANGUAGE_FRENCH = 3,
    LANGUAGE_ITALIAN = 4,
    LANGUAGE_GERMAN = 5,
    LANGUAGE_SPANISH = 7,
    LANGUAGE_KOREAN = 8
};

extern void ErrorHandling(void);

#define GF_ASSERT(expr) do {if (!(expr)) ErrorHandling();} while (0)

extern const enum GameLanguage gGameLanguage;
extern const enum GameVersion gGameVersion;

#endif //GUARD_GLOBAL_H

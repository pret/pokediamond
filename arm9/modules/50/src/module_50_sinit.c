#include "global.h"

extern void Poketch_InitApp(void *func1, void *func2);
extern void MOD50_02254854();
extern void MOD50_02254908();

THUMB_FUNC static void MOD50_02254840(void)
{
    Poketch_InitApp(MOD50_02254854, MOD50_02254908);
}

#define NitroStaticInit MOD50_02254840
#include "sinit.h"

#include "global.h"

extern void Poketch_InitApp(void *func1, void *func2);
extern void MOD39_02254854();
extern void MOD39_022549D4();

THUMB_FUNC static void MOD39_02254840(void)
{
    Poketch_InitApp(MOD39_02254854, MOD39_022549D4);
}

#define NitroStaticInit MOD39_02254840
#include "sinit.h"

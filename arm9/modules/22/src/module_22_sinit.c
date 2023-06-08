#include "global.h"

extern void Poketch_InitApp(void *func1, void *func2);
extern void MOD22_02254854();
extern void MOD22_022549D8();

static void MOD22_02254840(void)
{
    Poketch_InitApp(MOD22_02254854, MOD22_022549D8);
}

#define NitroStaticInit MOD22_02254840
#include "sinit.h"

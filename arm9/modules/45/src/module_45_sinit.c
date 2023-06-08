#include "global.h"

extern void Poketch_InitApp(void *func1, void *func2);
extern void MOD45_02254854();
extern void MOD45_02254A30();

static void MOD45_02254840(void)
{
    Poketch_InitApp(MOD45_02254854, MOD45_02254A30);
}

#define NitroStaticInit MOD45_02254840
#include "sinit.h"

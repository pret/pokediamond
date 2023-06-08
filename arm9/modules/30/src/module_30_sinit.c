#include "global.h"

extern void Poketch_InitApp(void *func1, void *func2);
extern void MOD30_02254854();
extern void MOD30_0225496C();

static void MOD30_02254840(void)
{
    Poketch_InitApp(MOD30_02254854, MOD30_0225496C);
}

#define NitroStaticInit MOD30_02254840
#include "sinit.h"

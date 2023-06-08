#include "global.h"

extern void Poketch_InitApp(void *func1, void *func2);
extern void MOD25_02254854();
extern void MOD25_0225496C();

static void MOD25_02254840(void)
{
    Poketch_InitApp(MOD25_02254854, MOD25_0225496C);
}

#define NitroStaticInit MOD25_02254840
#include "sinit.h"

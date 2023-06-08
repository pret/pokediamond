#include "global.h"

extern void Poketch_InitApp(void *func1, void *func2);
extern void MOD27_02254854();
extern void MOD27_0225492C();

static void MOD27_02254840(void)
{
    Poketch_InitApp(MOD27_02254854, MOD27_0225492C);
}

#define NitroStaticInit MOD27_02254840
#include "sinit.h"

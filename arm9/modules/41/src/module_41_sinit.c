#include "global.h"

extern void Poketch_InitApp(void *func1, void *func2);
extern void MOD41_02254854();
extern void MOD41_02254AD8();

static void MOD41_02254840(void)
{
    Poketch_InitApp(MOD41_02254854, MOD41_02254AD8);
}

#define NitroStaticInit MOD41_02254840
#include "sinit.h"

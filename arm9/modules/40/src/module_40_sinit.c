#include "global.h"

extern void Poketch_InitApp(void *func1, void *func2);
extern void MOD40_02254854();
extern void MOD40_022549D4();

static void MOD40_02254840(void)
{
    Poketch_InitApp(MOD40_02254854, MOD40_022549D4);
}

#define NitroStaticInit MOD40_02254840
#include "sinit.h"

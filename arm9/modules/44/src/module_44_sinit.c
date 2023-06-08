#include "global.h"

extern void Poketch_InitApp(void *func1, void *func2);
extern void MOD44_02254854();
extern void MOD44_02254920();

static void MOD44_02254840(void)
{
    Poketch_InitApp(MOD44_02254854, MOD44_02254920);
}

#define NitroStaticInit MOD44_02254840
#include "sinit.h"

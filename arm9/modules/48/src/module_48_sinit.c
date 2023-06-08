#include "global.h"

extern void Poketch_InitApp(void *func1, void *func2);
extern void MOD48_02254854();
extern void MOD48_0225498C();

static void MOD48_02254840(void)
{
    Poketch_InitApp(MOD48_02254854, MOD48_0225498C);
}

#define NitroStaticInit MOD48_02254840
#include "sinit.h"

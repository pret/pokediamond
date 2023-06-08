#include "global.h"

extern void Poketch_InitApp(void *func1, void *func2);
extern void MOD36_02254854();
extern void MOD36_02254990();

static void MOD36_02254840(void)
{
    Poketch_InitApp(MOD36_02254854, MOD36_02254990);
}

#define NitroStaticInit MOD36_02254840
#include "sinit.h"

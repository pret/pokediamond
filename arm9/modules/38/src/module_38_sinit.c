#include "global.h"

extern void Poketch_InitApp(void *func1, void *func2);
extern void MOD38_02254854();
extern void MOD38_02254990();

static void MOD38_02254840(void)
{
    Poketch_InitApp(MOD38_02254854, MOD38_02254990);
}

#define NitroStaticInit MOD38_02254840
#include "sinit.h"

#include "global.h"

extern void Poketch_InitApp(void *func1, void *func2);
extern void MOD37_02254854();
extern void MOD37_02254934();

static void MOD37_02254840(void)
{
    Poketch_InitApp(MOD37_02254854, MOD37_02254934);
}

#define NitroStaticInit MOD37_02254840
#include "sinit.h"

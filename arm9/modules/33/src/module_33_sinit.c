#include "global.h"

extern void Poketch_InitApp(void *func1, void *func2);
extern void MOD33_02254854();
extern void MOD33_02254908();

static void MOD33_02254840(void)
{
    Poketch_InitApp(MOD33_02254854, MOD33_02254908);
}

#define NitroStaticInit MOD33_02254840
#include "sinit.h"

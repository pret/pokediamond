#include "global.h"

extern void Poketch_InitApp(void *func1, void *func2);
extern void MOD28_02254854();
extern void MOD28_022549F4();

THUMB_FUNC static void MOD28_02254840(void)
{
    Poketch_InitApp(MOD28_02254854, MOD28_022549F4);
}

#define NitroStaticInit MOD28_02254840
#include "sinit.h"

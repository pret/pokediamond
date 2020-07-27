#include "global.h"

extern void Poketch_InitApp(void *func1, void *func2);
extern void MOD21_02254854();
extern void MOD21_0225496C();

THUMB_FUNC static void MOD21_02254840(void)
{
    Poketch_InitApp(MOD21_02254854, MOD21_0225496C);
}

#define NitroStaticInit MOD21_02254840
#include "sinit.h"

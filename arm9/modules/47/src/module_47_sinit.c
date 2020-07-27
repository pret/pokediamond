#include "global.h"

extern void Poketch_InitApp(void *func1, void *func2);
extern void MOD47_02254854();
extern void MOD47_0225491C();

THUMB_FUNC static void MOD47_02254840(void)
{
    Poketch_InitApp(MOD47_02254854, MOD47_0225491C);
}

#define NitroStaticInit MOD47_02254840
#include "sinit.h"

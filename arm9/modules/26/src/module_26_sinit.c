#include "global.h"

extern void Poketch_InitApp(void *func1, void *func2);
extern void MOD26_02254854();
extern void MOD26_02254A84();

THUMB_FUNC static void MOD26_02254840(void)
{
    Poketch_InitApp(MOD26_02254854, MOD26_02254A84);
}

#define NitroStaticInit MOD26_02254840
#include "sinit.h"

#include "global.h"

extern void Poketch_InitApp(void *func1, void *func2);
extern void MOD29_02254854();
extern void MOD29_02254914();

THUMB_FUNC static void MOD29_02254840(void)
{
    Poketch_InitApp(MOD29_02254854, MOD29_02254914);
}

#define NitroStaticInit MOD29_02254840
#include "sinit.h"

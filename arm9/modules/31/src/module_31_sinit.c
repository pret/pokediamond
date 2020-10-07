#include "global.h"

extern void Poketch_InitApp(void *func1, void *func2);
extern void MOD31_02254854();
extern void MOD31_02254954();

THUMB_FUNC static void MOD31_02254840(void)
{
    Poketch_InitApp(MOD31_02254854, MOD31_02254954);
}

#define NitroStaticInit MOD31_02254840
#include "sinit.h"

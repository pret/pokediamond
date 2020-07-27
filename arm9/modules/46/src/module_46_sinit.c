#include "global.h"

extern void Poketch_InitApp(void *func1, void *func2);
extern void MOD46_02254854();
extern void MOD46_02254908();

THUMB_FUNC static void MOD46_02254840(void)
{
    Poketch_InitApp(MOD46_02254854, MOD46_02254908);
}

#define NitroStaticInit MOD46_02254840
#include "sinit.h"

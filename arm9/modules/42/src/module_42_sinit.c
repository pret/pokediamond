#include "global.h"

extern void Poketch_InitApp(void *func1, void *func2);
extern void MOD42_02254854();
extern void MOD42_02254A38();

THUMB_FUNC static void MOD42_02254840(void)
{
    Poketch_InitApp(MOD42_02254854, MOD42_02254A38);
}

#define NitroStaticInit MOD42_02254840
#include "sinit.h"

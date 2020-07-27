#include "global.h"

extern void Poketch_InitApp(void *func1, void *func2);
extern void MOD24_02254854();
extern void MOD24_02254990();

THUMB_FUNC static void MOD24_02254840(void)
{
    Poketch_InitApp(MOD24_02254854, MOD24_02254990);
}

#define NitroStaticInit MOD24_02254840
#include "sinit.h"

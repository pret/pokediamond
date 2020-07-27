#include "global.h"

extern void Poketch_InitApp(void *func1, void *func2);
extern void MOD35_02254854();
extern void MOD35_02254924();

THUMB_FUNC static void MOD35_02254840(void)
{
    Poketch_InitApp(MOD35_02254854, MOD35_02254924);
}

#define NitroStaticInit MOD35_02254840
#include "sinit.h"

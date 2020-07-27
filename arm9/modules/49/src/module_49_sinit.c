#include "global.h"

extern void Poketch_InitApp(void *func1, void *func2);
extern void MOD49_02254854();
extern void MOD49_02254974();

THUMB_FUNC static void MOD49_02254840(void)
{
    Poketch_InitApp(MOD49_02254854, MOD49_02254974);
}

#define NitroStaticInit MOD49_02254840
#include "sinit.h"

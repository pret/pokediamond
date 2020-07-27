#include "global.h"

extern void Poketch_InitApp(void *func1, void *func2);
extern void MOD34_02254854();
extern void MOD34_02254948();

THUMB_FUNC static void MOD34_02254840(void)
{
    Poketch_InitApp(MOD34_02254854, MOD34_02254948);
}

#define NitroStaticInit MOD34_02254840
#include "sinit.h"

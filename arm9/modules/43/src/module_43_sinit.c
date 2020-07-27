#include "global.h"

extern void Poketch_InitApp(void *func1, void *func2);
extern void MOD43_02254854();
extern void MOD43_02254970();

THUMB_FUNC static void MOD43_02254840(void)
{
    Poketch_InitApp(MOD43_02254854, MOD43_02254970);
}

#define NitroStaticInit MOD43_02254840
#include "sinit.h"

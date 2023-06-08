#include "global.h"

extern void Poketch_InitApp(void *func1, void *func2);
extern void MOD23_02254854();
extern void MOD23_022549A4();

static void MOD23_02254840(void)
{
    Poketch_InitApp(MOD23_02254854, MOD23_022549A4);
}

#define NitroStaticInit MOD23_02254840
#include "sinit.h"

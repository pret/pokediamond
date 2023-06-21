#include "global.h"

extern void Poketch_InitApp(void *func1, void *func2);
extern void ov45_02254854();
extern void ov45_02254A30();

static void ov45_02254840(void)
{
    Poketch_InitApp(ov45_02254854, ov45_02254A30);
}

#define NitroStaticInit ov45_02254840
#include "sinit.h"

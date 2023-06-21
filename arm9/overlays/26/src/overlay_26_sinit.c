#include "global.h"

extern void Poketch_InitApp(void *func1, void *func2);
extern void ov26_02254854();
extern void ov26_02254A84();

static void ov26_02254840(void)
{
    Poketch_InitApp(ov26_02254854, ov26_02254A84);
}

#define NitroStaticInit ov26_02254840
#include "sinit.h"

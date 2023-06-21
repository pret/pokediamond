#include "global.h"

extern void Poketch_InitApp(void *func1, void *func2);
extern void ov22_02254854();
extern void ov22_022549D8();

static void ov22_02254840(void)
{
    Poketch_InitApp(ov22_02254854, ov22_022549D8);
}

#define NitroStaticInit ov22_02254840
#include "sinit.h"

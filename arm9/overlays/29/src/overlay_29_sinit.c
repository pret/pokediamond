#include "global.h"

extern void Poketch_InitApp(void *func1, void *func2);
extern void ov29_02254854();
extern void ov29_02254914();

static void ov29_02254840(void)
{
    Poketch_InitApp(ov29_02254854, ov29_02254914);
}

#define NitroStaticInit ov29_02254840
#include "sinit.h"

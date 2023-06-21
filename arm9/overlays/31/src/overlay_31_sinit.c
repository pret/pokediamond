#include "global.h"

extern void Poketch_InitApp(void *func1, void *func2);
extern void ov31_02254854();
extern void ov31_02254954();

static void ov31_02254840(void)
{
    Poketch_InitApp(ov31_02254854, ov31_02254954);
}

#define NitroStaticInit ov31_02254840
#include "sinit.h"

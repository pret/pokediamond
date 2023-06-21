#include "global.h"

extern void Poketch_InitApp(void *func1, void *func2);
extern void ov44_02254854();
extern void ov44_02254920();

static void ov44_02254840(void)
{
    Poketch_InitApp(ov44_02254854, ov44_02254920);
}

#define NitroStaticInit ov44_02254840
#include "sinit.h"

#include "global.h"

extern void Poketch_InitApp(void *func1, void *func2);
extern void ov43_02254854();
extern void ov43_02254970();

static void ov43_02254840(void)
{
    Poketch_InitApp(ov43_02254854, ov43_02254970);
}

#define NitroStaticInit ov43_02254840
#include "sinit.h"

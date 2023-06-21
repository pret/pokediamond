#include "global.h"

extern void Poketch_InitApp(void *func1, void *func2);
extern void ov48_02254854();
extern void ov48_0225498C();

static void ov48_02254840(void)
{
    Poketch_InitApp(ov48_02254854, ov48_0225498C);
}

#define NitroStaticInit ov48_02254840
#include "sinit.h"

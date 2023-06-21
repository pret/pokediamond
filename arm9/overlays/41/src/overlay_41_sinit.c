#include "global.h"

extern void Poketch_InitApp(void *func1, void *func2);
extern void ov41_02254854();
extern void ov41_02254AD8();

static void ov41_02254840(void)
{
    Poketch_InitApp(ov41_02254854, ov41_02254AD8);
}

#define NitroStaticInit ov41_02254840
#include "sinit.h"

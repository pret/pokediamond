#include "global.h"

extern void Poketch_InitApp(void *func1, void *func2);
extern void ov24_02254854();
extern void ov24_02254990();

static void ov24_02254840(void)
{
    Poketch_InitApp(ov24_02254854, ov24_02254990);
}

#define NitroStaticInit ov24_02254840
#include "sinit.h"

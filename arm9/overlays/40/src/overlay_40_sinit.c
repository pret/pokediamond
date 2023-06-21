#include "global.h"

extern void Poketch_InitApp(void *func1, void *func2);
extern void ov40_02254854();
extern void ov40_022549D4();

static void ov40_02254840(void)
{
    Poketch_InitApp(ov40_02254854, ov40_022549D4);
}

#define NitroStaticInit ov40_02254840
#include "sinit.h"

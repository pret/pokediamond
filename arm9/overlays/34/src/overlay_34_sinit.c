#include "global.h"

extern void Poketch_InitApp(void *func1, void *func2);
extern void ov34_02254854();
extern void ov34_02254948();

static void ov34_02254840(void)
{
    Poketch_InitApp(ov34_02254854, ov34_02254948);
}

#define NitroStaticInit ov34_02254840
#include "sinit.h"

#include "global.h"

extern void Poketch_InitApp(void *func1, void *func2);
extern void ov47_02254854();
extern void ov47_0225491C();

static void ov47_02254840(void) {
    Poketch_InitApp(ov47_02254854, ov47_0225491C);
}

#define NitroStaticInit ov47_02254840
#include "sinit.h"

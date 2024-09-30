#include "global.h"

extern void Poketch_InitApp(void *func1, void *func2);
extern void ov30_02254854();
extern void ov30_0225496C();

static void ov30_02254840(void) {
    Poketch_InitApp(ov30_02254854, ov30_0225496C);
}

#define NitroStaticInit ov30_02254840
#include "sinit.h"

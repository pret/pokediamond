#include "global.h"

extern void Poketch_InitApp(void *func1, void *func2);
extern void ov27_02254854();
extern void ov27_0225492C();

static void ov27_02254840(void) {
    Poketch_InitApp(ov27_02254854, ov27_0225492C);
}

#define NitroStaticInit ov27_02254840
#include "sinit.h"

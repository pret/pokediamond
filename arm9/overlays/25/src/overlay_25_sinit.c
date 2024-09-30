#include "global.h"

extern void Poketch_InitApp(void *func1, void *func2);
extern void ov25_02254854();
extern void ov25_0225496C();

static void ov25_02254840(void) {
    Poketch_InitApp(ov25_02254854, ov25_0225496C);
}

#define NitroStaticInit ov25_02254840
#include "sinit.h"

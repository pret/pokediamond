#include "global.h"

extern void Poketch_InitApp(void *func1, void *func2);
extern void ov39_02254854();
extern void ov39_022549D4();

static void ov39_02254840(void) {
    Poketch_InitApp(ov39_02254854, ov39_022549D4);
}

#define NitroStaticInit ov39_02254840
#include "sinit.h"

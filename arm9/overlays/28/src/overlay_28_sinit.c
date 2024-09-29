#include "global.h"

extern void Poketch_InitApp(void *func1, void *func2);
extern void ov28_02254854();
extern void ov28_022549F4();

static void ov28_02254840(void) {
    Poketch_InitApp(ov28_02254854, ov28_022549F4);
}

#define NitroStaticInit ov28_02254840
#include "sinit.h"

#include "global.h"

extern void Poketch_InitApp(void *func1, void *func2);
extern void ov50_02254854();
extern void ov50_02254908();

static void ov50_02254840(void) {
    Poketch_InitApp(ov50_02254854, ov50_02254908);
}

#define NitroStaticInit ov50_02254840
#include "sinit.h"

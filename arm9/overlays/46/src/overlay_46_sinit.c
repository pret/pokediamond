#include "global.h"

extern void Poketch_InitApp(void *func1, void *func2);
extern void ov46_02254854();
extern void ov46_02254908();

static void ov46_02254840(void) {
    Poketch_InitApp(ov46_02254854, ov46_02254908);
}

#define NitroStaticInit ov46_02254840
#include "sinit.h"

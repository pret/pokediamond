#include "global.h"

extern void Poketch_InitApp(void *func1, void *func2);
extern void ov42_02254854();
extern void ov42_02254A38();

static void ov42_02254840(void) {
    Poketch_InitApp(ov42_02254854, ov42_02254A38);
}

#define NitroStaticInit ov42_02254840
#include "sinit.h"

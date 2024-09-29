#include "global.h"

extern void Poketch_InitApp(void *func1, void *func2);
extern void ov49_02254854();
extern void ov49_02254974();

static void ov49_02254840(void) {
    Poketch_InitApp(ov49_02254854, ov49_02254974);
}

#define NitroStaticInit ov49_02254840
#include "sinit.h"

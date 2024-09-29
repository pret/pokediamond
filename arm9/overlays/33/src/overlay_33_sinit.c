#include "global.h"

extern void Poketch_InitApp(void *func1, void *func2);
extern void ov33_02254854();
extern void ov33_02254908();

static void ov33_02254840(void) {
    Poketch_InitApp(ov33_02254854, ov33_02254908);
}

#define NitroStaticInit ov33_02254840
#include "sinit.h"

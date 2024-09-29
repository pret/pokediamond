#include "global.h"

extern void Poketch_InitApp(void *func1, void *func2);
extern void ov35_02254854();
extern void ov35_02254924();

static void ov35_02254840(void) {
    Poketch_InitApp(ov35_02254854, ov35_02254924);
}

#define NitroStaticInit ov35_02254840
#include "sinit.h"

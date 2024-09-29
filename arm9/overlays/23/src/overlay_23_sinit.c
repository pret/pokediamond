#include "global.h"

extern void Poketch_InitApp(void *func1, void *func2);
extern void ov23_02254854();
extern void ov23_022549A4();

static void ov23_02254840(void) {
    Poketch_InitApp(ov23_02254854, ov23_022549A4);
}

#define NitroStaticInit ov23_02254840
#include "sinit.h"

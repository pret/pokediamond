#include "global.h"

extern void Poketch_InitApp(void *func1, void *func2);
extern void ov36_02254854();
extern void ov36_02254990();

static void ov36_02254840(void) {
    Poketch_InitApp(ov36_02254854, ov36_02254990);
}

#define NitroStaticInit ov36_02254840
#include "sinit.h"

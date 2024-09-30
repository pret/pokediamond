#include "global.h"

extern void Poketch_InitApp(void *func1, void *func2);
extern void ov38_02254854();
extern void ov38_02254990();

static void ov38_02254840(void) {
    Poketch_InitApp(ov38_02254854, ov38_02254990);
}

#define NitroStaticInit ov38_02254840
#include "sinit.h"

#include "global.h"
#include "sinit.h"
#pragma thumb on

static void NitroStaticInit(void) {
    static u32 var[2];
    var[1]++;
}

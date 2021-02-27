#include "global.h"
#include "fx.h"
#include "unk_0201CBEC.h"

THUMB_FUNC int FUN_0201CBEC(int a0, int a1, int a2, int a3) {

    int r0 = a0 - a2;
    int r2 = a1 - a3;

    return FX_Sqrt((r0 * r0 + r2 * r2) << 0xc) >> 0xc;
}

#include "global.h"
#include "main.h"


extern void FUN_0201681C(u32 param0, u32 heap_id, u32 param2);
extern void MOD52_021D769C(u32 heap_id, u32 param1);

THUMB_FUNC int MOD52_021D74E0() {
    FUN_0201681C(3, 0x4d, 2 << 16);
	InitializeMainRNG();

    return 1;
}
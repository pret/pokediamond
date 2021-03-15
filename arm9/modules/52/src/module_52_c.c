#include "global.h"
#include "main.h"
#include "overlay_manager.h"


extern void FUN_0201681C(u32 param0, u32 heap_id, u32 param2);
extern int FUN_020168D0(u32 heap_id);
extern void MOD52_021D769C(u32 heap_id, int param1);
extern struct Unk21DBE18 UNK_020FD144;

THUMB_FUNC int MOD52_021D74E0() {
    FUN_0201681C(3, 0x4d, 2 << 16);
	InitializeMainRNG();

    return 1;
}

THUMB_FUNC int MOD52_021D74F8(struct UnkStruct_02006234 *param0) {
    int res = OverlayManager_GetField18(param0)[2];

    MOD52_021D769C(0x4d, res);

    return 1;
}

THUMB_FUNC int MOD52_021D750C() {
    FUN_020168D0(0x4d);
    RegisterMainOverlay(-1, &UNK_020FD144);

    return 1;
}
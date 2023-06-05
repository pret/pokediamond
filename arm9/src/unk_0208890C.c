#include "global.h"
#include "unk_0208890C.h"
#include "MI_memory.h"
#include "bag.h"
#include "heap.h"
#include "main.h"
#include "player_data.h"
#include "poke_overlay.h"

extern struct SaveBlock2* ScriptEnvironment_GetSavePtr(struct FieldSystem *);
extern void* FUN_02028048(struct SaveBlock2* sav2);
extern void FUN_020373D4(struct FieldSystem *, struct OverlayManagerTemplate *, void*);
extern BOOL FUN_020889B0(struct OverlayManager *, u32*);
extern BOOL FUN_02088A00(struct OverlayManager *, u32*);
extern BOOL FUN_02088A78(struct OverlayManager *, u32*);

const struct OverlayManagerTemplate UNK_020FD6E4 = {
    FUN_020889B0,
    FUN_02088A00,
    FUN_02088A78,
    SDK_OVERLAY_INVALID_ID,
};

THUMB_FUNC struct UnkStruct_0208890C* FUN_0208890C(void* a0, struct SaveBlock2* sav2, u32 heap_id, void* a3)
{
    struct UnkStruct_0208890C* ret = AllocFromHeap(heap_id, sizeof(struct UnkStruct_0208890C));
    MI_CpuFill8(ret, 0, sizeof(struct UnkStruct_0208890C));

    ret->sav2 = sav2;
    ret->unk8 = FUN_02028048(sav2);
    ret->player = Save_PlayerData_GetProfileAddr(sav2);
    ret->bag = Save_Bag_Get(sav2);
    ret->options = Save_PlayerData_GetOptionsAddr(sav2);
    ret->unk1C = a3;
    ret->unk4 = a0;

    return ret;
}

THUMB_FUNC void FUN_02088950(struct FieldSystem *fieldSystem, struct UnkStruct_0208890C *param1)
{
    FUN_020373D4(fieldSystem, (struct OverlayManagerTemplate *)&UNK_020FD6E4, param1);
}

THUMB_FUNC struct UnkStruct_0208890C* FUN_02088960(struct FieldSystem *fieldSystem, void* a1, u32 heap_id)
{
    struct SaveBlock2* sav2 = ScriptEnvironment_GetSavePtr(fieldSystem);
    struct UnkStruct_0208890C* ret = FUN_0208890C(a1, sav2, heap_id, fieldSystem->unk98);

    FUN_02088950(fieldSystem, ret);

    return ret;
}

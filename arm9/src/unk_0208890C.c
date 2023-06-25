#include "global.h"
#include "unk_0208890C.h"
#include "MI_memory.h"
#include "bag.h"
#include "heap.h"
#include "main.h"
#include "player_data.h"
#include "poke_overlay.h"

extern struct SaveData* FieldSystem_GetSaveDataPtr(struct FieldSystem *);
extern u32 sub_02028048(struct SaveData* save);
extern void sub_020373D4(struct FieldSystem *, struct OverlayManagerTemplate *, void*);
extern BOOL sub_020889B0(struct OverlayManager *, u32*);
extern BOOL sub_02088A00(struct OverlayManager *, u32*);
extern BOOL sub_02088A78(struct OverlayManager *, u32*);

const struct OverlayManagerTemplate UNK_020FD6E4 = {
    sub_020889B0,
    sub_02088A00,
    sub_02088A78,
    SDK_OVERLAY_INVALID_ID,
};

struct PoffinCaseAppData* sub_0208890C(u32 a0, struct SaveData* save, HeapID heapId, u32 *a3)
{
    struct PoffinCaseAppData* ret = AllocFromHeap(heapId, sizeof(struct PoffinCaseAppData));
    MI_CpuFill8(ret, 0, sizeof(struct PoffinCaseAppData));

    ret->save = save;
    ret->unk8 = sub_02028048(save);
    ret->player = Save_PlayerData_GetProfileAddr(save);
    ret->bag = Save_Bag_Get(save);
    ret->options = Save_PlayerData_GetOptionsAddr(save);
    ret->unk1C = a3;
    ret->unk4 = a0;

    return ret;
}

void sub_02088950(struct FieldSystem *fieldSystem, struct PoffinCaseAppData *param1)
{
    sub_020373D4(fieldSystem, (struct OverlayManagerTemplate *)&UNK_020FD6E4, param1);
}

struct PoffinCaseAppData* sub_02088960(struct FieldSystem *fieldSystem, u32 a1, HeapID heapId)
{
    struct SaveData* save = FieldSystem_GetSaveDataPtr(fieldSystem);
    struct PoffinCaseAppData* ret = sub_0208890C(a1, save, heapId, fieldSystem->unk98);

    sub_02088950(fieldSystem, ret);

    return ret;
}

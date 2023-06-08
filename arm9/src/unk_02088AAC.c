#include "global.h"
#include "unk_02088AAC.h"
#include "heap.h"
#include "overlay_manager.h"
#include "unk_020851B8.h"

extern BOOL MOD68_021D74E0(struct OverlayManager *, u32 *);
extern BOOL MOD68_021D75D8(struct OverlayManager *, u32 *);
extern BOOL MOD68_021D762C(struct OverlayManager *, u32 *);
extern BOOL MOD73_021D74F0(struct OverlayManager *, u32 *);
extern BOOL MOD73_021D758C(struct OverlayManager *, u32 *);
extern BOOL MOD73_021D7640(struct OverlayManager *, u32 *);
extern BOOL MOD75_021E6BA0(struct OverlayManager *, u32 *);
extern BOOL MOD75_021E6D6C(struct OverlayManager *, u32 *);
extern BOOL MOD75_021E6F00(struct OverlayManager *, u32 *);

extern BOOL FUN_0208898C(struct OverlayManager **r0);

u32 FUN_02088AAC(struct UnkStruct_02088AAC *r0, u32 *r1)
{
    switch (*r1)
    {
    case 0:
        *r1 = FUN_02088B4C(r0);
        break;
    case 1:
        *r1 = FUN_02088BA8(r0);
        break;
    case 2:
        *r1 = FUN_02088C3C(r0);
        break;
    case 3:
        *r1 = FUN_02088CDC(r0);
        break;
    case 4:
        return 1;
    case 5:
        return 4;
    }

    return 0;
}

u32 FUN_02088AFC(struct UnkStruct_02088AAC *r0)
{
    FS_EXTERN_OVERLAY(MODULE_73);

    const struct OverlayManagerTemplate OVERLAY_73_MANAGER =
    {
        .initFunc = MOD73_021D74F0,
        .mainFunc = MOD73_021D758C,
        .exitFunc = MOD73_021D7640,
        .ovly = FS_OVERLAY_ID(MODULE_73)
    };
    r0->ovly_data = OverlayManager_New(&OVERLAY_73_MANAGER, (s32 *)r0, r0->heap_id);

    return 2;
}

u32 FUN_02088B28(struct UnkStruct_02088AAC *r0)
{
    if (!FUN_0208898C(&r0->ovly_data))
    {
        return 2;
    }

    if (r0->unk20 == TRUE)
    {
        return 0;
    }

    return 3;
}

u32 FUN_02088B48()
{
    return 4;
}

u32 FUN_02088B4C(struct UnkStruct_02088AAC *r0)
{
    FS_EXTERN_OVERLAY(MODULE_75);

    static const u8 UNK_020FD6F4[] = { 0x04, 0xFF };
    const struct OverlayManagerTemplate OVERLAY_75_MANAGER =
        {
            .initFunc = MOD75_021E6BA0,
            .mainFunc = MOD75_021E6D6C,
            .exitFunc = MOD75_021E6F00,
            .ovly = FS_OVERLAY_ID(MODULE_75)
        };
    struct BagView *bag_view = CreateBagView(r0->unk10->bag, UNK_020FD6F4, r0->heap_id);

    FUN_0206E314(bag_view, r0->unk10->sav2, (u8)((u8)r0->unk06 == 1 ? 5 : 4), r0->unk0C);

    r0->ovly_data = OverlayManager_New(&OVERLAY_75_MANAGER, (s32 *)bag_view, r0->heap_id);
    r0->ovly_param = bag_view;

    return 1;
}

u32 FUN_02088BA8(struct UnkStruct_02088AAC *r0)
{
    if (!FUN_0208898C(&r0->ovly_data))
    {
        return 1;
    }

    struct BagView *bag_view = BagView_New((u8)r0->heap_id);

    memcpy(bag_view, r0->ovly_param, BagView_sizeof());
    FreeToHeap(r0->ovly_param);

    r0->ovly_param = NULL;
    r0->item = FUN_0206E37C(bag_view);

    FreeToHeap(bag_view);

    switch (FUN_0206E384(bag_view))
    {
    case 1:
        return 2;
    case 5:
        return 5;
    default:
        GF_AssertFail();
        r0->item = FIRST_BERRY_IDX;
    case 0:
    case 2:
    case 3:
    case 4:
        GF_ASSERT(Bag_TakeItem(r0->unk10->bag, (u16)r0->item, 1, r0->heap_id));
        return 4;
    }
}

u32 FUN_02088C3C(struct UnkStruct_02088AAC *r0)
{
    FS_EXTERN_OVERLAY(MODULE_68);

    struct Bag *bag = r0->unk10->bag;
    const struct OverlayManagerTemplate OVERLAY_68_MANAGER =
        {
            .initFunc = MOD68_021D74E0,
            .mainFunc = MOD68_021D75D8,
            .exitFunc = MOD68_021D762C,
            .ovly = FS_OVERLAY_ID(MODULE_68)
        };

    r0->ovly_param = FUN_020851B8((u8)r0->heap_id);

    FUN_020851DC(r0->ovly_param, (u16)r0->item, TRUE);

    u8 berry_count = 0;
    for (u8 berry_id = 0; berry_id < (u8)NUM_BERRIES; berry_id++)
    {
        u8 item_id = (u8)BerryToItemId(berry_id);
        if (Bag_HasItem(bag, item_id, 1, r0->heap_id) == TRUE)
        {
            FUN_020851DC(r0->ovly_param, item_id, 0);

            berry_count++;
        }
    }

    u8 sp5;
    u8 sp6;

    FUN_0206F17C(r0->unk0C, 4, &sp6, &sp5);
    FUN_020851F8(r0->ovly_param, sp5, sp6, (u8)(berry_count + 2));

    r0->ovly_data = OverlayManager_New(&OVERLAY_68_MANAGER, (s32 *)r0->ovly_param, r0->heap_id);

    return 3;
}

u32 FUN_02088CDC(struct UnkStruct_02088AAC *r0)
{
    if (!FUN_0208898C(&r0->ovly_data))
    {
        return 3;
    }

    u8 sp0;
    u8 sp1;

    FUN_0208524C(r0->ovly_param, &sp0, &sp1);
    FUN_0206F190(r0->unk0C, 4, sp1, sp0);
    FreeToHeap(r0->ovly_param);

    r0->ovly_param = NULL;

    return 0;
}

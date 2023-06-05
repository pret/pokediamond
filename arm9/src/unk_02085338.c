#include "global.h"
#include "heap.h"
#include "event_data.h"
#include "unk_02085338.h"

extern BOOL FUN_0205ED0C(struct ScriptState * state);

THUMB_FUNC struct UnkStruct_02085338 * FUN_02085338(u8 r5, u8 r7, struct SaveBlock2 * sav2, u32 heap_id)
{
    struct UnkStruct_02085338 * ret = (struct UnkStruct_02085338 *) AllocFromHeap(heap_id, sizeof(struct UnkStruct_02085338));
    ret->unk_00 = r5;
    ret->unk_01 = r7;
    ret->unk_0c = Save_Pokedex_Get(sav2);
    ret->unk_10 = FUN_02013B5C(sav2);
    ret->unk_04 = (u8)FUN_0205ED0C(SaveArray_Flags_Get(sav2));
    ret->unk_05 = 0;
    ret->unk_02 = 1;
    ret->unk_03 = 0;
    ret->unk_08 = Options_GetFrame(Save_PlayerData_GetOptionsAddr(sav2));
    if (r5 == 2)
    {
        MailMsg_Init_WithBank(&ret->unk_14, 3);
    }
    else
    {
        for (int i = 0; i < 2; i++)
        {
            ret->unk_1c[i] = 0xFFFF;
        }
    }
    return ret;
}

THUMB_FUNC void FUN_020853A8(struct UnkStruct_02085338 * ptr)
{
    FreeToHeap(ptr);
}

THUMB_FUNC void FUN_020853B0(struct UnkStruct_02085338 * ptr, u16 a1)
{
    ptr->unk_1c[0] = a1;
}

THUMB_FUNC void FUN_020853B4(struct UnkStruct_02085338 * ptr, u16 a1, u16 a2)
{
    ptr->unk_1c[0] = a1;
    ptr->unk_1c[1] = a2;
}

THUMB_FUNC void FUN_020853BC(struct UnkStruct_02085338 * ptr, const struct MailMessage * a1)
{
    ptr->unk_14 = *a1;
}

THUMB_FUNC void FUN_020853D0(struct UnkStruct_02085338 * ptr)
{
    ptr->unk_02 = 1;
    ptr->unk_03 = 0;
}

THUMB_FUNC void FUN_020853DC(struct UnkStruct_02085338 * ptr)
{
    ptr->unk_05 = 1;
}

THUMB_FUNC u8 FUN_020853E4(struct UnkStruct_02085338 * ptr)
{
    return ptr->unk_02;
}

THUMB_FUNC u8 FUN_020853E8(struct UnkStruct_02085338 * ptr)
{
    return ptr->unk_03;
}

THUMB_FUNC u16 FUN_020853EC(struct UnkStruct_02085338 * ptr)
{
    return ptr->unk_1c[0];
}

THUMB_FUNC void FUN_020853F0(struct UnkStruct_02085338 * ptr, u16 * a1)
{
    a1[0] = ptr->unk_1c[0];
    a1[1] = ptr->unk_1c[1];
}

THUMB_FUNC void FUN_020853FC(struct UnkStruct_02085338 * ptr, struct MailMessage * a1)
{
    return MailMsg_Copy(a1, &ptr->unk_14);
}

THUMB_FUNC u8 FUN_0208540C(struct UnkStruct_02085338 * ptr)
{
    return ptr->unk_00;
}

THUMB_FUNC u8 FUN_02085410(struct UnkStruct_02085338 * ptr)
{
    return ptr->unk_01;
}

THUMB_FUNC u32 FUN_02085414(struct UnkStruct_02085338 * ptr)
{
    return ptr->unk_08;
}

THUMB_FUNC struct Pokedex * FUN_02085418(struct UnkStruct_02085338 * ptr)
{
    return ptr->unk_0c;
}

THUMB_FUNC struct UnkStruct_02013B28 * FUN_0208541C(struct UnkStruct_02085338 * ptr)
{
    return ptr->unk_10;
}

THUMB_FUNC u8 FUN_02085420(struct UnkStruct_02085338 * ptr)
{
    return ptr->unk_04;
}

THUMB_FUNC u8 FUN_02085424(struct UnkStruct_02085338 * ptr)
{
    return ptr->unk_05;
}

THUMB_FUNC void FUN_02085428(struct UnkStruct_02085338 * ptr, u16 * a1, struct MailMessage * a2)
{
    switch (ptr->unk_00)
    {
    case 0:
        a1[0] = ptr->unk_1c[0];
        break;
    case 1:
        a1[0] = ptr->unk_1c[0];
        a1[1] = ptr->unk_1c[1];
        break;
    case 2:
        *a2 = ptr->unk_14;
        break;
    }
}

THUMB_FUNC BOOL FUN_0208545C(struct UnkStruct_02085338 * ptr, const u16 * a1, const struct MailMessage * a2)
{
    switch (ptr->unk_00)
    {
    case 0:
        return a1[0] == ptr->unk_1c[0];
    case 1:
        return a1[0] == ptr->unk_1c[0] && a1[1] == ptr->unk_1c[1];
    case 2:
    default:
        return MailMsg_Compare(&ptr->unk_14, a2);
    }
}

THUMB_FUNC void FUN_020854A0(struct UnkStruct_02085338 * r5, u16 * r4, struct MailMessage * r6)
{
    r5->unk_03 = (u8)(!FUN_0208545C(r5, r4, r6) ? 1 : 0);
    r5->unk_02 = 0;
    for (int i = 0; i < 2; i++)
        r5->unk_1c[i] = r4[i];
    r5->unk_14 = *r6;
}

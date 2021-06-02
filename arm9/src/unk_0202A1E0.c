#include "global.h"
#include "MI_memory.h"
#include "msgdata.h"
#include "heap.h"
#include "unk_0202A1E0.h"

THUMB_FUNC s32 FUN_0202A1E0()
{
    return 228;
}

THUMB_FUNC void FUN_0202A1E4(void *dest)
{
    MI_CpuFill8(dest, 0, 60);
}

THUMB_FUNC void FUN_0202A1F0(struct Unk0202A1F0 *arg0)
{
    MI_CpuFill8(arg0, 0, 360);
    arg0->u_3 = 1;
}

THUMB_FUNC void FUN_0202A204(struct UnkMailStruct *arg0)
{
    MailMsg_init_fromTemplate(&arg0->messages[0], 0);
    MailMsg_init_fromTemplate(&arg0->messages[1], 1);
    MailMsg_init_fromTemplate(&arg0->messages[2], 2);
    MailMsg_init_fromTemplate(&arg0->messages[3], 3);
}

THUMB_FUNC void FUN_0202A230(void *dst)
{
    MI_CpuFill8(dst, 0, 2876);
}

THUMB_FUNC u32 FUN_0202A240(struct Unk0202A240 *unk, u32 mode, void *dst)
{
    switch (mode)
    {
        case 0:
            return unk->u_0_2;
        case 1:
            return unk->u_2;
        case 2:
            return unk->u_3;
        case 3:
            return unk->u_4;
        case 4:
            return unk->u_6;
        case 5:
            MI_CpuCopy8(&unk->u_8, dst, 4);
            return 0;
        case 6:
            MI_CpuCopy8(&unk->u_2C, dst, 16);
            return 0;
        case 7:
            return unk->u_0_0;
        case 8:
            MI_CpuCopy8(&unk->u_C, dst, 28);
            return 0;
        case 9:
            return unk->u_0_5;
        case 10:
            return unk->u_28;
        default:
            return 0;
    };
}

THUMB_FUNC void FUN_0202A2C4(struct Unk0202A240 *dst, u32 mode, void *src)
{
    switch (mode)
    {
        case 0:
            dst->u_0_2 = *(u8 *)src;
            break;
        case 1:
            dst->u_2 = *(u8 *)src;
            break;
        case 2:
            dst->u_3 = *(u8 *)src;
            break;
        case 3:
            dst->u_4 = *(u16 *)src;
            break;
        case 4:
            dst->u_6 = *(u16 *)src;
            break;
        case 5:
            MI_CpuCopy8(src, &dst->u_8, 4);
            break;
        case 6:
            MI_CpuCopy8(src, &dst->u_2C, 16);
            break;
        case 7:
            dst->u_0_0 = *(u8 *)src;
            break;
        case 8:
            MI_CpuCopy8(src, &dst->u_C, 28);
            break;
        case 10:
            dst->u_28 = *(u32 *)src;
            break;
        case 9:
            dst->u_0_5 = *(u8 *)src;
            break;
    }
}

THUMB_FUNC void FUN_0202A36C(struct Unk0202A240 *unk, s32 arg1, s32 arg2, s32 arg3)
{
    if (unk->u_3 + arg1 < 0xff)
    {
        unk->u_3 += arg1;
    }

    if (unk->u_4 + arg2 < 0xffff)
    {
        unk->u_4 += arg2;
    }

    if (unk->u_6 + arg3 < 0xffff)
    {
        unk->u_6 += arg3;
    }
}

THUMB_FUNC u8 FUN_0202A398(struct Unk0202A240 *unk)
{
    return unk->u_0_1;
}

THUMB_FUNC void FUN_0202A3A0(struct Unk0202A240 *unk, u16 arg1)
{
    unk->u_0_1 = arg1;
}

THUMB_FUNC u16 FUN_0202A3B4(struct Unk0202A3B4 *unk, u16 arg1, s32 controlVariable)
{
    switch (controlVariable)
    {
        case 0:
            break;
        case 1:
            if (arg1 > 0x270F)
            {
                unk->u_0 = 0x270F;
            }
            else
            {
                unk->u_0 = arg1;
            }
            break;
        case 2:
        case 3:
        case 4:
            break;
        case 5:
            if (unk->u_0 + arg1 > 0x270F)
            {
                unk->u_0 = 0x270F;
            }
            else
            {
                unk->u_0 += arg1;
            }
            break;
        case 6:
            if (unk->u_0 < arg1)
            {
                unk->u_0 = 0;
            }
            else
            {
                unk->u_0 -= arg1;
            }
            break;
    }
    return unk->u_0;
}

THUMB_FUNC u8 FUN_0202A40C(struct Unk0202A40C *unk, s32 controlVariable)
{
    switch (controlVariable)
    {
        case 2:
            unk->u_2 = 0;
            unk->u_8_4 = 0;
            break;
        case 3:
            if (unk->u_8_4 != 0)
            {
                unk->u_2 += 1;
            }
            else
            {
                unk->u_2 = 1;
                unk->u_8_4 = 1;
            }
            break;
    }
    return unk->u_2;
}

THUMB_FUNC u8 FUN_0202A444(struct Unk0202A444 *unk, s32 controlVariable)
{
    switch (controlVariable)
    {
        case 2:
            unk->u_3 = 1;
            break;
        case 3:
            if (unk->u_3 < 0xa)
            {
                unk->u_3++;
            }
            break;
        case 4:
            if (unk->u_3 > 1)
            {
                unk->u_3--;
            }
            break;
    }
    return unk->u_3;
}

THUMB_FUNC void FUN_0202A474(void *dst, s32 arg1, const void *src)
{
    if (arg1 == 0)
    {
        MI_CpuCopy8(src, dst + 0xc0, 0xa8);
    }
    else
    {
        MI_CpuCopy8(src, dst + 0x18, 0xa8);
    }
}

THUMB_FUNC void FUN_0202A498(const void *src, s32 arg1, void *dst)
{
    if (arg1 == 0)
    {
        MI_CpuCopy8(src + 0xc0, dst, 0xa8);
    }
    else
    {
        MI_CpuCopy8(src + 0x18, dst, 0xa8);
    }
}

THUMB_FUNC u16 FUN_0202A4B8(struct Unk0202A4B8 *arg0, struct Unk0202A4B8 *arg1) 
{
    u16 var1, var2, var3, var4, var5, total;

    var1 = (u16) ((arg1->u_2 - 1) * 1000);
    var2 = (u16) (arg1->u_4 * 10);
    var3 = (u16) (arg1->u_3 * 20);
    
    if (var2 + var3 > 950)
    {
        var4 = 0;
    }
    else
    {
        var4 = (u16) (950 - (var2 + var3));
    }

    if (arg1->u_6 > 970)
    {
        var5 = 0;
    }
    else
    {
        var5 = (u16) ((1000 - arg1->u_6) / 30);
    }

    total = (u16) (var1 + var4 + var5);
    arg0->u_16 = total;
    return total;
}

THUMB_FUNC u16 FUN_0202A520(struct Unk0202A4B8 *unk)
{
    return unk->u_16;
}

THUMB_FUNC u8 FUN_0202A524(struct Unk0202A4B8 *unk)
{
    return (u8)(unk->u_16 / (0xfa << 2));
}

THUMB_FUNC u16 FUN_0202A538(struct Unk0202A4B8 *unk, s32 arg1, s32 arg2)
{
    if (arg1 == 5)
    {
        return 0;
    }

    switch(arg2) {
        case 2:
            unk->u_array_C[arg1] = 0;
            break;
        case 3:
            if (unk->u_array_C[arg1] < 0xfffe) {
                unk->u_array_C[arg1]++;
            }
            break;
    }
    return unk->u_array_C[arg1];    
}

THUMB_FUNC BOOL FUN_0202A578(struct Unk0202A578 *arg0, u16 arg1, u32 arg2) 
{
    u16 i;
    u16 flag = 1;

    for (i = 0; i < arg1 ; i++)
    {
        flag <<= 1;
    }

    switch (arg2)
    {
        case 2:
            flag = (u16) (flag ^ 0xffff);
            arg0->u_8 &= flag;
            break;
        case 1:
            arg0->u_8 |= flag;
            break;
        case 0:
            return (BOOL) ((arg0->u_8 >> arg1) & 1);
    }

    return 0;
}


THUMB_FUNC void FUN_0202A5CC(struct Unk0202A5CC *unk, u32 arg1)
{
    unk->u_4 = arg1;
}

THUMB_FUNC u32 FUN_0202A5D0(struct Unk0202A5CC *unk)
{
    return unk->u_4;
}


THUMB_FUNC void FUN_0202A5D4(struct SaveBlock2 *sav2, u32 arg1, struct MailMessage *arg2)
{
    struct UnkSaveStruct_0202A5D4 *data = SavArray_get(sav2, 23);
    MailMsg_copy(&data->messages.messages[arg1], arg2);
}

THUMB_FUNC struct MailMessage *FUN_0202A5F4(struct SaveBlock2 *sav2, u32 arg1)
{
    struct UnkSaveStruct_0202A5D4 *data = SavArray_get(sav2, 23);
    return &data->messages.messages[arg1];
}

THUMB_FUNC void FUN_0202A60C(struct Unk0202A670 *arg0, u8 arg1, u8 arg2, struct Unk0202A68C *arg3) {

    u8 bitmask = 1;

    if (arg2 == 0 || arg2 > 200)
    {
        return;
    }

    if (arg1 == 0 || arg1 > 10)
    {
        return;
    }

    u16 var2 = (u16) ((arg1 - 1) * 200 + (arg2 - 1));
    u8 index = (u8) (var2 / 8);
    u8 remainder = (u8) (var2 % 8);
    bitmask <<= remainder;

    arg0->u_4[index] |= bitmask;
    arg0->u_0 = (arg3->u_0 << 24) | ((arg3->u_4 & 0xff) << 16) | ((arg3->u_8 & 0xff) << 8) | arg3->u_C;
}

THUMB_FUNC void FUN_0202A670(struct Unk0202A670 *arg0)
{

    MI_CpuFill8(&(arg0->u_4), 0, 250);
    MI_CpuFill8(arg0, 0, 4);
}

THUMB_FUNC BOOL FUN_0202A68C(struct Unk0202A68C *arg0, struct Unk0202A68C *arg1)
{
    if (arg0->u_0 > arg1->u_0) {
        return TRUE;
    } else if (arg0->u_4 > arg1->u_4) {
        return TRUE;
    } else if (arg0->u_8 > arg1->u_8) {
        return TRUE;
    }
    return FALSE;
}

THUMB_FUNC BOOL FUN_0202A6B4(struct Unk0202A670 *arg0, u8 arg1, u8 arg2, struct Unk0202A68C *arg3) 
{    
    u8 bitmask = 1;

    if (arg2 > 200 || arg1 > 10)
    {
        return FALSE;
    }

    u32 var0 = arg0->u_0;

    Unk0202A68C var1;
    var1.u_0 = var0 >> 24 & 0xff;
    var1.u_4 = var0 >> 16 & 0xff;
    var1.u_8 = var0 >> 8 & 0xff;
    var1.u_C = var0 & 0xff;

    if (FUN_0202A68C(arg3, &var1))
    {
        FUN_0202A670(arg0);
        return FALSE;
    }

    u16 var2 = (u16) ((arg1 - 1) * 200 + (arg2 - 1));
    u8 index = (u8) (var2 / 8);
    u8 remainder = (u8) (var2 % 8);
    bitmask <<= remainder;

    if (arg0->u_4[index] & bitmask)
    {
        return 1;
    }
    return FALSE;
}


THUMB_FUNC u8 FUN_0202A744(struct Unk0202A744 *unk)
{
    return unk->u_FE;
}

THUMB_FUNC u8 FUN_0202A74C(struct Unk0202A744 *unk)
{
    return unk->u_FF;
}

THUMB_FUNC void FUN_0202A754(struct Unk0202A744 *dest, void *src, u8 arg2, u8 arg3)
{
    MI_CpuCopy8(src, &dest->u_104, sizeof(struct Unk0202A744_substruct1));
    dest->u_101 = arg2;
    dest->u_100 = arg3;
    dest->u_FE = 1;
}

THUMB_FUNC void FUN_0202A784(struct Unk0202A744 *src, struct Unk0202A784 *dest)
{
    dest->u_0 = src->u_101;
    dest->u_1 = src->u_100;
}

THUMB_FUNC void FUN_0202A798(struct Unk0202A798_1 *arg0, struct Unk0202A798_2 *arg1, u32 arg2)
{
    struct Unk0202A798_substruct2 *var0 = &arg1->u_0;
    u8 *var1 = arg1->u_30;
    struct Unk0202A798_substruct1 *src = &arg0->u_104[arg2];
    struct MsgData *message;

    var0->u_0 = 10000;
    var0->u_4 = src->u_C9;

    if(src->u_C8_0)
    {
        message = NewMsgDataFromNarc(0, NARC_MSGDATA_MSG, 17, 11);
        ReadMsgDataIntoU16Array(message, (u32) (22 + src->u_C8_1), var0->u_8);
        DestroyMsgData(message);
    }
    else
    {
        MI_CpuCopy8(src->u_A8, var0->u_8, 16);
    }

    MI_CpuCopy8(src->u_CA, var0->u_18, 8);
    MI_CpuCopy8(src->u_D2, var0->u_20, 8);
    MI_CpuCopy8(src->u_DA, var0->u_28, 8);
    MI_CpuCopy8(src->u_0, var1, 168);
}

THUMB_FUNC void FUN_0202A838(struct Unk0202A744 *dest, void *src, u8 arg2, u8 arg3)
{
    MI_CpuCopy8(src, &dest->u_740, sizeof(dest->u_740));
    dest->u_103 = arg2;
    dest->u_102 = arg3;
    dest->u_FF = 1;
}

THUMB_FUNC void FUN_0202A864(struct Unk0202A744 *src, struct Unk0202A784 *dest)
{
    dest->u_0 = src->u_103;
    dest->u_1 = src->u_102;
}

THUMB_FUNC struct Unk0202A744_substruct2 *FUN_0202A878(struct Unk0202A744 *src, u32 heap_id)
{
    struct Unk0202A744_substruct2 *dstp = AllocFromHeap(heap_id, sizeof(struct Unk0202A744_substruct2) /* 1020 */);
    MI_CpuCopy8(&src->u_740, dstp, sizeof(struct Unk0202A744_substruct2));
    return dstp;
}

THUMB_FUNC s32 FUN_0202A89C()
{
    return 0xD00; // 3328
}

THUMB_FUNC void FUN_0202A8A4(struct UnkSaveStruct_0202A5D4 *savStruct)
{
    FUN_0202A1E4(savStruct);
    FUN_0202A1F0(&savStruct->u_3C);
    FUN_0202A204(&savStruct->messages);
    FUN_0202A230(&savStruct->u_1C4);
}

THUMB_FUNC struct UnkSaveStruct_0202A5D4 *FUN_0202A8CC(struct SaveBlock2* sav2)
{
    return SavArray_get(sav2, 23);
}

THUMB_FUNC struct Unk0202A1F0 *FUN_0202A8D8(struct SaveBlock2* sav2)
{
    struct UnkSaveStruct_0202A5D4 *data = SavArray_get(sav2, 23);
    return &data->u_3C;
}

THUMB_FUNC void *FUN_0202A8E4(struct SaveBlock2* sav2)
{
    struct UnkSaveStruct_0202A5D4 *data = SavArray_get(sav2, 23);
    return &data->u_1C4;
}
#include "global.h"
#include "MI_memory.h"
#include "msgdata.h"
#include "heap.h"
#include "unk_0202A1E0.h"

THUMB_FUNC s32 SaveStruct23_Substruct4_Substruct1_sizeof()
{
    return sizeof(struct SaveStruct23_Substruct4_Substruct1); // 228
}

THUMB_FUNC void SaveStruct23_Substruct1_Init(struct SaveStruct23_Substruct1 *substruct1)
{
    MI_CpuFill8(substruct1, 0, sizeof(struct SaveStruct23_Substruct1));
}

THUMB_FUNC void SaveStruct23_Substruct2_Init(struct SaveStruct23_Substruct2 *substruct2)
{
    MI_CpuFill8(substruct2, 0, sizeof(struct SaveStruct23_Substruct2));
    substruct2->u_3 = 1;
}

THUMB_FUNC void SaveStruct23_Messages_Init(struct SaveStruct23_Messages *messages)
{
    MailMsg_Init_FromTemplate(&messages->messages[0], 0);
    MailMsg_Init_FromTemplate(&messages->messages[1], 1);
    MailMsg_Init_FromTemplate(&messages->messages[2], 2);
    MailMsg_Init_FromTemplate(&messages->messages[3], 3);
}

THUMB_FUNC void SaveStruct23_Substruct4_Init(struct SaveStruct23_Substruct4 *substruct4)
{
    MI_CpuFill8(substruct4, 0, sizeof(struct SaveStruct23_Substruct4));
}

THUMB_FUNC u32 SaveStruct23_Substruct1_GetField(struct SaveStruct23_Substruct1 *substruct1, SaveStruct23_Substruct1_Field field, void *dst)
{
    switch (field)
    {
        case FIELD_0x0_2:
            return substruct1->u_0_2;
        case FIELD_0x2:
            return substruct1->u_2;
        case FIELD_0x3:
            return substruct1->u_3;
        case FIELD_0x4:
            return substruct1->u_4;
        case FIELD_0x6:
            return substruct1->u_6;
        case FIELD_0x8:
            MI_CpuCopy8(&substruct1->u_8, dst, 4);
            return 0;
        case FIELD_0x2C:
            MI_CpuCopy8(&substruct1->u_2C, dst, 16);
            return 0;
        case FIELD_flag0:
            return substruct1->flag0;
        case FIELD_0xC:
            MI_CpuCopy8(&substruct1->u_C, dst, 28);
            return 0;
        case FIELD_0x0_5:
            return substruct1->u_0_5;
        case FIELD_0x28:
            return substruct1->u_28;
        default:
            return 0;
    };
}

THUMB_FUNC void SaveStruct23_Substruct1_SetField(struct SaveStruct23_Substruct1 *substruct1, SaveStruct23_Substruct1_Field field, void *value)
{
    switch (field)
    {
        case FIELD_0x0_2:
            substruct1->u_0_2 = *(u8 *)value;
            break;
        case FIELD_0x2:
            substruct1->u_2 = *(u8 *)value;
            break;
        case FIELD_0x3:
            substruct1->u_3 = *(u8 *)value;
            break;
        case FIELD_0x4:
            substruct1->u_4 = *(u16 *)value;
            break;
        case FIELD_0x6:
            substruct1->u_6 = *(u16 *)value;
            break;
        case FIELD_0x8:
            MI_CpuCopy8(value, &substruct1->u_8, 4);
            break;
        case FIELD_0x2C:
            MI_CpuCopy8(value, &substruct1->u_2C, 16);
            break;
        case FIELD_flag0:
            substruct1->flag0 = *(u8 *)value;
            break;
        case FIELD_0xC:
            MI_CpuCopy8(value, &substruct1->u_C, 28);
            break;
        case FIELD_0x28:
            substruct1->u_28 = *(u32 *)value;
            break;
        case FIELD_0x0_5:
            substruct1->u_0_5 = *(u8 *)value;
            break;
    }
}

THUMB_FUNC void FUN_0202A36C(struct SaveStruct23_Substruct1 *substruct1, s32 arg1, s32 arg2, s32 arg3)
{
    if (substruct1->u_3 + arg1 < 0xff)
    {
        substruct1->u_3 += arg1;
    }

    if (substruct1->u_4 + arg2 < 0xffff)
    {
        substruct1->u_4 += arg2;
    }

    if (substruct1->u_6 + arg3 < 0xffff)
    {
        substruct1->u_6 += arg3;
    }
}

THUMB_FUNC BOOL SaveStruct23_Substruct1_GetFlag1(struct SaveStruct23_Substruct1 *substruct1)
{
    return substruct1->flag1;
}

THUMB_FUNC void SaveStruct23_Substruct1_SetFlag1(struct SaveStruct23_Substruct1 *substruct1, BOOL flag)
{
    substruct1->flag1 = flag;
}

THUMB_FUNC u16 SaveStruct23_Substruct2_SetField_0x0(struct SaveStruct23_Substruct2 *substruct2, u16 value, DataSetMode mode)
{
    switch (mode)
    {
        case DATA_SET:
            if (value > 9999)
            {
                substruct2->u_0 = 9999;
            }
            else
            {
                substruct2->u_0 = value;
            }
            break;
        case DATA_ADD:
            if (substruct2->u_0 + value > 9999)
            {
                substruct2->u_0 = 9999;
            }
            else
            {
                substruct2->u_0 += value;
            }
            break;
        case DATA_SUBSTRACT:
            if (substruct2->u_0 < value)
            {
                substruct2->u_0 = 0;
            }
            else
            {
                substruct2->u_0 -= value;
            }
            break;
        case DATA_GET:
        default:
            break;
    }
    return substruct2->u_0;
}

THUMB_FUNC u8 SaveStruct23_Substruct2_SetField_0x2(struct SaveStruct23_Substruct2 *substruct2, DataSetMode mode)
{
    switch (mode)
    {
        case DATA_RESET:
            substruct2->u_2 = 0;
            substruct2->flag4 = 0;
            break;
        case DATA_INCREMENT:
            if (substruct2->flag4)
            {
                substruct2->u_2++;
            }
            else
            {
                substruct2->u_2 = 1;
                substruct2->flag4 = 1;
            }
            break;
    }
    return substruct2->u_2;
}

THUMB_FUNC u8 SaveStruct23_Substruct2_SetField_0x3(struct SaveStruct23_Substruct2 *substruct2, DataSetMode mode)
{
    switch (mode)
    {
        case DATA_RESET:
            substruct2->u_3 = 1;
            break;
        case DATA_INCREMENT:
            if (substruct2->u_3 < 10)
            {
                substruct2->u_3++;
            }
            break;
        case DATA_DECREMENT:
            if (substruct2->u_3 > 1)
            {
                substruct2->u_3--;
            }
            break;
    }
    return substruct2->u_3;
}

THUMB_FUNC void SaveStruct23_Substruct2_SetArray(struct SaveStruct23_Substruct2 *substruct2, s32 mode, void *src)
{
    if (mode == 0)
    {
        MI_CpuCopy8(src, substruct2->u_C0, 168);
    }
    else
    {
        MI_CpuCopy8(src, substruct2->u_18, 168);
    }
}

THUMB_FUNC void SaveStruct23_Substruct2_GetArray(struct SaveStruct23_Substruct2 *substruct2, s32 mode, void *dst)
{
    if (mode == 0)
    {
        MI_CpuCopy8(substruct2->u_C0, dst, 168);
    }
    else
    {
        MI_CpuCopy8(substruct2->u_18, dst, 168);
    }
}

THUMB_FUNC u16 SaveStruct23_Substruct2_SetField_0x16(struct SaveStruct23_Substruct2 *substruct2, struct Unk0202A4B8 *arg1) 
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
    substruct2->u_16 = total;
    return total;
}

THUMB_FUNC u16 SaveStruct23_Substruct2_GetField_0x16(struct SaveStruct23_Substruct2 *substruct2)
{
    return substruct2->u_16;
}

THUMB_FUNC u8 FUN_0202A524(struct SaveStruct23_Substruct2 *substruct2)
{
    return (u8)(substruct2->u_16 / 1000);
}

THUMB_FUNC u16 SaveStruct23_Substruct2_SetField_0xC(struct SaveStruct23_Substruct2 *substruct2, u16 arg1, DataSetMode mode)
{
    if (arg1 == 5)
    {
        return 0;
    }

    switch(mode) {
        case DATA_RESET:
            substruct2->u_C[arg1] = 0;
            break;
        case DATA_INCREMENT:
            if (substruct2->u_C[arg1] < 0xfffe) {
                substruct2->u_C[arg1]++;
            }
            break;
    }
    return substruct2->u_C[arg1];    
}

THUMB_FUNC BOOL SaveStruct23_Substruct2_SetFlag(struct SaveStruct23_Substruct2 *substruct2, u16 flagNumber, DataSetMode mode) 
{
    u16 i;
    u16 flag = 1;

    for (i = 0; i < flagNumber ; i++)
    {
        flag <<= 1;
    }

    switch (mode)
    {
        case DATA_RESET:
            flag = (u16) (flag ^ 0xffff);
            substruct2->flags &= flag;
            break;
        case DATA_SET:
            substruct2->flags |= flag;
            break;
        case DATA_GET:
            return (BOOL) ((substruct2->flags >> flagNumber) & 1);
    }

    return FALSE;
}


THUMB_FUNC void SaveStruct23_Substruct2_SetField_0x4(struct SaveStruct23_Substruct2 *substruct2, u32 value)
{
    substruct2->u_4 = value;
}

THUMB_FUNC u32 SaveStruct23_Substruct2_GetField_0x4(struct SaveStruct23_Substruct2 *substruct2)
{
    return substruct2->u_4;
}


THUMB_FUNC void SaveStruct23_SetMessage(struct SaveBlock2 *sav2, u32 index, struct MailMessage *message)
{
    struct SaveStruct23 *data = SaveArray_Get(sav2, 23);
    MailMsg_Copy(&data->messages.messages[index], message);
}

THUMB_FUNC struct MailMessage *SaveStruct23_GetMessage(struct SaveBlock2 *sav2, u32 index)
{
    struct SaveStruct23 *data = SaveArray_Get(sav2, 23);
    return &data->messages.messages[index];
}

THUMB_FUNC void SaveStruct23_Substruct4_SetArrayFlag(struct SaveStruct23_Substruct4 *substruct4, u8 arg1, u8 arg2, struct Unk0202A68C *arg3) {

    u8 flag = 1;

    if (arg2 == 0 || arg2 > 200)
    {
        return;
    }

    if (arg1 == 0 || arg1 > 10)
    {
        return;
    }

    u16 var1 = (u16) ((arg1 - 1) * 200 + (arg2 - 1));
    u8 index = (u8) (var1 / 8);
    u8 remainder = (u8) (var1 % 8);
    flag <<= remainder;

    substruct4->flags[index] |= flag;
    substruct4->u_0 = (arg3->u_0 << 24) | ((arg3->u_4 & 0xff) << 16) | ((arg3->u_8 & 0xff) << 8) | arg3->u_C;
}

THUMB_FUNC void SaveStruct23_Substruct4_ClearArrayFlags(struct SaveStruct23_Substruct4 *substruct4)
{

    MI_CpuFill8(substruct4->flags, 0, 250);
    MI_CpuFill8(&substruct4->u_0, 0, 4);
}

THUMB_FUNC BOOL StructUnk0202A68C_Compare(struct Unk0202A68C *struct1, struct Unk0202A68C *struct2)
{
    if (struct1->u_0 > struct2->u_0) {
        return TRUE;
    } else if (struct1->u_4 > struct2->u_4) {
        return TRUE;
    } else if (struct1->u_8 > struct2->u_8) {
        return TRUE;
    }
    return FALSE;
}

THUMB_FUNC BOOL SaveStruct23_Substruct4_GetArrayFlag(struct SaveStruct23_Substruct4 *substruct4, u8 arg1, u8 arg2, struct Unk0202A68C *arg3) 
{    
    u8 flag = 1;

    if (arg2 > 200 || arg1 > 10)
    {
        return FALSE;
    }

    u32 var0 = substruct4->u_0;

    Unk0202A68C var1;
    var1.u_0 = var0 >> 24 & 0xff;
    var1.u_4 = var0 >> 16 & 0xff;
    var1.u_8 = var0 >> 8 & 0xff;
    var1.u_C = var0 & 0xff;

    if (StructUnk0202A68C_Compare(arg3, &var1))
    {
        SaveStruct23_Substruct4_ClearArrayFlags(substruct4);
        return FALSE;
    }

    u16 var2 = (u16) ((arg1 - 1) * 200 + (arg2 - 1));
    u8 index = (u8) (var2 / 8);
    u8 remainder = (u8) (var2 % 8);
    flag <<= remainder;

    if (substruct4->flags[index] & flag)
    {
        return TRUE;
    }
    return FALSE;
}


THUMB_FUNC u8 SaveStruct23_Substruct4_GetField_0xFE(struct SaveStruct23_Substruct4 *substruct4)
{
    return substruct4->u_FE;
}

THUMB_FUNC u8 SaveStruct23_Substruct4_GetField_0xFF(struct SaveStruct23_Substruct4 *substruct4)
{
    return substruct4->u_FF;
}

THUMB_FUNC void SaveStruct23_Substruct4_SetSubstruct1(struct SaveStruct23_Substruct4 *substruct4, struct SaveStruct23_Substruct4_Substruct1 *substruct1, u8 arg2, u8 arg3)
{
    MI_CpuCopy8(substruct1, &substruct4->substruct1, sizeof(struct SaveStruct23_Substruct4_Substruct1)*7);
    substruct4->u_101 = arg2;
    substruct4->u_100 = arg3;
    substruct4->u_FE = 1;
}

THUMB_FUNC void FUN_0202A784(struct SaveStruct23_Substruct4 *substruct4, struct Unk0202A784 *dst)
{
    dst->u_0 = substruct4->u_101;
    dst->u_1 = substruct4->u_100;
}

THUMB_FUNC void FUN_0202A798(struct SaveStruct23_Substruct4 *substruct4, struct Unk0202A798 *arg1, u32 arg2)
{
    struct Unk0202A798_substruct *unk_substruct = &arg1->u_0;
    u8 *var1 = arg1->u_30;
    struct SaveStruct23_Substruct4_Substruct1 *substruct4_substruct1 = &substruct4->substruct1[arg2];
    struct MsgData *message;

    unk_substruct->u_0 = 10000;
    unk_substruct->u_4 = substruct4_substruct1->u_C9;

    if(substruct4_substruct1->u_C8_0)
    {
        message = NewMsgDataFromNarc(MSGDATA_LOAD_DIRECT, NARC_MSGDATA_MSG, 17, 11);
        ReadMsgDataIntoU16Array(message, (u32) (22 + substruct4_substruct1->u_C8_1), unk_substruct->u_8);
        DestroyMsgData(message);
    }
    else
    {
        MI_CpuCopy8(substruct4_substruct1->u_A8, unk_substruct->u_8, 16);
    }

    MI_CpuCopy8(substruct4_substruct1->u_CA, unk_substruct->u_18, 8);
    MI_CpuCopy8(substruct4_substruct1->u_D2, unk_substruct->u_20, 8);
    MI_CpuCopy8(substruct4_substruct1->u_DA, unk_substruct->u_28, 8);
    MI_CpuCopy8(substruct4_substruct1->u_0, var1, 168);
}

THUMB_FUNC void FUN_0202A838(struct SaveStruct23_Substruct4 *substruct4, struct SaveStruct23_Substruct4_Substruct2 *substruct4_substruct2, u8 arg2, u8 arg3)
{
    MI_CpuCopy8(substruct4_substruct2, &substruct4->substruct2, sizeof(struct SaveStruct23_Substruct4_Substruct2));
    substruct4->u_103 = arg2;
    substruct4->u_102 = arg3;
    substruct4->u_FF = 1;
}

THUMB_FUNC void FUN_0202A864(struct SaveStruct23_Substruct4 *substruct4, struct Unk0202A784 *dst)
{
    dst->u_0 = substruct4->u_103;
    dst->u_1 = substruct4->u_102;
}

THUMB_FUNC struct SaveStruct23_Substruct4_Substruct2 *FUN_0202A878(struct SaveStruct23_Substruct4 *substruct4, u32 heap_id)
{
    struct SaveStruct23_Substruct4_Substruct2 *substruct4_substruct2 = AllocFromHeap(heap_id, sizeof(struct SaveStruct23_Substruct4_Substruct2) /* 1020 */);
    MI_CpuCopy8(&substruct4->substruct2, substruct4_substruct2, sizeof(struct SaveStruct23_Substruct4_Substruct2));
    return substruct4_substruct2;
}

THUMB_FUNC s32 SaveStruct23_sizeof()
{
    return sizeof(struct SaveStruct23); // 0xD00 (3328)
}

THUMB_FUNC void SaveStruct23_Init(struct SaveStruct23 *saveStruct23)
{
    SaveStruct23_Substruct1_Init(&saveStruct23->substruct1);
    SaveStruct23_Substruct2_Init(&saveStruct23->substruct2);
    SaveStruct23_Messages_Init(&saveStruct23->messages);
    SaveStruct23_Substruct4_Init(&saveStruct23->substruct4);
}

THUMB_FUNC struct SaveStruct23_Substruct1 *SaveStruct23_GetSubstruct1(struct SaveBlock2* sav2)
{
    return &((struct SaveStruct23 *)SaveArray_Get(sav2, 23))->substruct1;
}

THUMB_FUNC struct SaveStruct23_Substruct2 *SaveStruct23_GetSubstruct2(struct SaveBlock2* sav2)
{
    return &((struct SaveStruct23 *)SaveArray_Get(sav2, 23))->substruct2;
}

THUMB_FUNC struct SaveStruct23_Substruct4 *SaveStruct23_GetSubstruct4(struct SaveBlock2* sav2)
{
    return &((struct SaveStruct23 *)SaveArray_Get(sav2, 23))->substruct4;
}
#include "unk_0205FA2C.h"
#include "unk_020337E8.h"
#include "unk_0202A1E0.h"

extern void *UNK_020F96DC;
extern void *UNK_020FA6E8;
extern u32 FUN_02079C70(struct SaveBlock2 *sav2);
extern void FUN_0207B000(struct UnkPlayerStruct2_0205FA2C *ptr, const u8 param1[12]);
extern void FUN_0207C2A4(struct UnkPlayerStruct2_0205FA2C *ptr, struct PlayerData *player_data);
extern u32 *FUN_02038790(struct UnkSavStruct80 *param0, u16 param1, u16 param2);
extern u16 *GetVarPointer(struct UnkSavStruct80 *arg, u16);
extern u16 MOD06_02244660(struct UnkSavStruct80 *param0, u8 *param1);
extern u16 MOD06_022446BC(struct UnkSavStruct80 *param0, u8 *param1);
extern u16 MOD06_022446E0(struct UnkSavStruct80 *param0, u8 *param1);
extern u32 FUN_02026CC4(struct SaveBlock2 *sav2);
extern u32 FUN_02025D94(u32 param0, u32 param1);

const u8 UNK_020F7454[] = {
    0x00,
    0x01,
    0x02,
    0x04,
    0x03,
    0x05,
    0x06,
    0x07,
    0x08,
};

THUMB_FUNC u32 FUN_0205FA2C(
    struct UnkCallbackStruct1_0205FA2C *param0, struct UnkSavStruct80 *param1, u32 heap_id)
{
    struct UnkPlayerStruct1_0205FA2C *ptr = (struct UnkPlayerStruct1_0205FA2C *)AllocFromHeapAtEnd(
        heap_id, sizeof(struct UnkPlayerStruct1_0205FA2C));

    struct SaveBlock2 *sav2 = param1->saveBlock2;
    MI_CpuFill8(ptr, 0, sizeof(struct UnkPlayerStruct1_0205FA2C));

    ptr->options = Sav2_PlayerData_GetOptionsAddr(sav2);

    ptr->player_party = SavArray_PlayerParty_get(sav2);

    ptr->bag = Sav2_Bag_get(sav2);

    ptr->unk21 = 0;
    ptr->unk20 = param0->unk08;
    ptr->unk32 = param0->unk0a;
    ptr->unk322 = param0->unk0b;
    ptr->unk33 = param0->unk0c;
    ptr->unk22 = param0->unk0d;

    for (u8 i = 0; i < 6; i++)
    {
        ptr->unk2c[i] = param0->unk0e[i];
    }

    FUN_020373D4(param1, (u32)&UNK_020F96DC, (u32)ptr);

    *param0->unk14 = ptr;

    return 1;
}

THUMB_FUNC u32 FUN_0205FAD8(
    struct UnkCallbackStruct1_0205FA2C *param0, struct UnkSavStruct80 *param1)
{
    if (FUN_0204647C(param1))
    {
        return 1;
    }

    struct UnkPlayerStruct1_0205FA2C *ptr = (struct UnkPlayerStruct1_0205FA2C *)*param0->unk14;

    u8 r1 = ptr->unk22;
    if (r1 != 6)
    {
        if (r1 == 7)
        {
            param0->unk00 = 0;
            return 4;
        }
    }
    else
    {
        param0->unk00 = 1;
        return 4;
    }

    MI_CpuCopy8(ptr->unk2c, param0->unk0e, 6);

    param0->unk0d = ptr->unk22;
    FreeToHeap(ptr);

    *param0->unk14 = NULL;

    return 2;
}

THUMB_FUNC u32 FUN_0205FB34(
    struct UnkCallbackStruct1_0205FA2C *param0, struct UnkSavStruct80 *param1, u32 heap_id)
{
    struct SaveBlock2 *sav2 = param1->saveBlock2;

    struct UnkPlayerStruct2_0205FA2C *ptr = (struct UnkPlayerStruct2_0205FA2C *)AllocFromHeapAtEnd(
        heap_id, sizeof(struct UnkPlayerStruct2_0205FA2C));
    MI_CpuFill8(ptr, 0, sizeof(struct UnkPlayerStruct2_0205FA2C));

    ptr->options = Sav2_PlayerData_GetOptionsAddr(sav2);
    ptr->player_party = SavArray_PlayerParty_get(sav2);
    ptr->IsNatDex = SavArray_IsNatDexEnabled(sav2);
    ptr->unk2c = FUN_02079C70(sav2);

    ptr->unk11 = 1;
    ptr->unk14 = param0->unk0d;

    ptr->party_count = (u8)GetPartyCount(ptr->player_party);

    ptr->unk18 = 0;
    ptr->unk12 = param0->unk09;

    ptr->unk20 = FUN_0202A918(sav2);

    FUN_0207B000(ptr, UNK_020F7454);

    FUN_0207C2A4(ptr, Sav2_PlayerData_GetProfileAddr(sav2));

    FUN_020373D4(param1, (u32)&UNK_020FA6E8, (u32)ptr);

    *param0->unk14 = ptr;

    return 3;
}

THUMB_FUNC u32 FUN_0205FBC0(
    struct UnkCallbackStruct1_0205FA2C *param0, struct UnkSavStruct80 *param1)
{
    if (FUN_0204647C(param1))
    {
        return 3;
    }

    struct UnkPlayerStruct2_0205FA2C *ptr = (struct UnkPlayerStruct2_0205FA2C *)*param0->unk14;
    param0->unk0d = ptr->unk14;
    FreeToHeap(ptr);

    *param0->unk14 = NULL;

    return 0;
}

THUMB_FUNC int FUN_0205FBE8(struct UnkStruct_0204639C *param0)
{
    struct UnkSavStruct80 *res = FUN_02046528(param0);
    struct UnkCallbackStruct1_0205FA2C *res2 =
        (struct UnkCallbackStruct1_0205FA2C *)FUN_0204652C(param0);
    switch (res2->unk04)
    {
    case 0:
        res2->unk04 = FUN_0205FA2C(res2, res, 0xb);
        break;
    case 1:
        res2->unk04 = FUN_0205FAD8(res2, res);
        break;
    case 2:
        res2->unk04 = FUN_0205FB34(res2, res, 0xb);
        break;
    case 3:
        res2->unk04 = FUN_0205FBC0(res2, res);
        break;
    case 4:
        FreeToHeap(res2);
        return 1;
    }

    return 0;
}

THUMB_FUNC void FUN_0205FC50(struct UnkStruct_0204639C *param0,
    void **param1,
    u8 param2,
    u8 param3,
    u8 param4,
    u8 param5,
    u8 param6,
    u8 param7)
{
    struct UnkSavStruct80 *res = FUN_02046528(param0);

    struct UnkCallbackStruct1_0205FA2C *ptr = (struct UnkCallbackStruct1_0205FA2C *)AllocFromHeap(
        0xb, sizeof(struct UnkCallbackStruct1_0205FA2C));
    MI_CpuFill8(ptr, 0, sizeof(struct UnkCallbackStruct1_0205FA2C));

    ptr->unk08 = param2;
    ptr->unk09 = param3;
    ptr->unk0a = param4;
    ptr->unk0b = param5;
    ptr->unk0c = param6;
    ptr->unk0d = param7;
    ptr->unk14 = param1;

    FUN_0204640C(res->unk10, &FUN_0205FBE8, (u32 *)ptr);
}

THUMB_FUNC u32 FUN_0205FC9C(
    struct UnkCallbackStruct2_0205FA2C *param0, struct UnkSavStruct80 *param1)
{
    if (FUN_0203384C(param1->saveBlock2))
    {

        param0->unk08 = FUN_02038790(param1, param0->unk12, param0->unk14);
        return 1;
    }

    param0->unk00 = 1;
    return 2;
}

THUMB_FUNC u32 FUN_0205FCC4(
    struct UnkCallbackStruct2_0205FA2C *param0, struct UnkSavStruct80 *param1)
{
    if (FUN_0204647C(param1))
    {
        return 1;
    }

    param0->unk00 = param0->unk08[8];
    FreeToHeap(param0->unk08);

    return 2;
}

THUMB_FUNC int FUN_0205FCE8(struct UnkStruct_0204639C *param0)
{
    struct UnkSavStruct80 *res = FUN_02046528(param0);
    struct UnkCallbackStruct2_0205FA2C *res2 =
        (struct UnkCallbackStruct2_0205FA2C *)FUN_0204652C(param0);

    switch (res2->unk04)
    {
    case 0:
        res2->unk04 = FUN_0205FC9C(res2, res);
        break;
    case 1:
        res2->unk04 = FUN_0205FCC4(res2, res);
        break;
    case 2:
        u16 *var = GetVarPointer(res, res2->unk10);
        *var = (u16)res2->unk00;
        FreeToHeap(res2);

        return 1;
    }

    return 0;
}

THUMB_FUNC void FUN_0205FD38(struct UnkStruct_0204639C *param0, u16 param1, u16 param2, u16 param3)
{
    struct UnkSavStruct80 *res = FUN_02046528(param0);
    struct UnkCallbackStruct2_0205FA2C *ptr = (struct UnkCallbackStruct2_0205FA2C *)AllocFromHeap(
        0xb, sizeof(struct UnkCallbackStruct2_0205FA2C));
    MI_CpuFill8(ptr, 0, sizeof(struct UnkCallbackStruct2_0205FA2C));

    ptr->unk12 = param1;
    ptr->unk14 = param3;
    ptr->unk10 = param2;

    FUN_0204640C(res->unk10, &FUN_0205FCE8, (u32 *)ptr);
}

THUMB_FUNC int FUN_0205FD70(struct UnkStruct_0204639C *param0)
{
    struct UnkSavStruct80 *res = FUN_02046528(param0);
    u16 *res2 = (u16 *)FUN_0204652C(param0);
    u8 *res3 = FUN_020316E0(1 - FUN_02031190());
    if (res3 == NULL)
    {
        return 0;
    }

    u16 *var = GetVarPointer(res, res2[1]);
    switch (res2[0])
    {
    case 0:
        *var = MOD06_02244660(res, res3);
        break;
    case 1:
        *var = MOD06_022446BC(res, res3);
        break;
    case 2:
        *var = MOD06_022446E0(res, res3);
        break;
    }

    FreeToHeap(res2);

    return 1;
}

THUMB_FUNC void FUN_0205FDDC(struct UnkStruct_0204639C *param0, u16 param1, u16 param2)
{
    struct UnkSavStruct80 *res = FUN_02046528(param0);

    u16 *ptr = AllocFromHeap(0xb, 2 * sizeof(u16));
    MI_CpuFill8(ptr, 0, 2 * sizeof(u16));

    ptr[0] = param1;
    ptr[1] = param2;

    FUN_0204640C(res->unk10, &FUN_0205FD70, (u32 *)ptr);
}

THUMB_FUNC u32 FUN_0205FE10(struct SaveBlock2 *sav2)
{

    u16 res = (u16) GameStats_GetCapped(Sav2_GameStats_get(sav2), 0x35);
    if (res < 20)
    {
        return 0;
    }

    struct SaveStruct23_Substruct2 *saveStruct23_substruct2 = SaveStruct23_GetSubstruct2(sav2);

    BOOL flagD = (u8)SaveStruct23_Substruct2_SetFlag(saveStruct23_substruct2, 0xd, DATA_GET);
    BOOL flag0 = (u8)SaveStruct23_Substruct2_SetFlag(saveStruct23_substruct2, 0, DATA_GET);
    BOOL flag1 = (u8)SaveStruct23_Substruct2_SetFlag(saveStruct23_substruct2, 1, DATA_GET);

    BOOL flagE = (u8)SaveStruct23_Substruct2_SetFlag(saveStruct23_substruct2, 0xe, DATA_GET);
    BOOL flag2 = (u8)SaveStruct23_Substruct2_SetFlag(saveStruct23_substruct2, 2, DATA_GET);
    BOOL flag3 = (u8)SaveStruct23_Substruct2_SetFlag(saveStruct23_substruct2, 3, DATA_GET);

    if (flagD && flag0 && flag1)
    {
        return 0;
    }

    u32 res9 = FUN_02026CC4(sav2);
    if (!flagD)
    {
        if (FUN_02025D94(res9, 0x55) != 0)
        {
            SaveStruct23_Substruct2_SetFlag(saveStruct23_substruct2, 0xd, DATA_SET);
            return 1;
        }

        if (!flagE)
        {
            SaveStruct23_Substruct2_SetFlag(saveStruct23_substruct2, 0xe, DATA_SET);
        }

        return 4;
    }

    if (res < 50)
    {
        return 0;
    }

    if (!flag0)
    {
        if (FUN_02025D94(res9, 0x56) != 0)
        {
            SaveStruct23_Substruct2_SetFlag(saveStruct23_substruct2, 0, DATA_SET);
            return 2;
        }

        if (!flag2)
        {
            SaveStruct23_Substruct2_SetFlag(saveStruct23_substruct2, 2, DATA_SET);
        }

        return 4;
    }

    if (res < 100 || flag1)
    {
        return 0;
    }

    if (FUN_02025D94(res9, 0x57) != 0)
    {
        SaveStruct23_Substruct2_SetFlag(saveStruct23_substruct2, 1, DATA_SET);
        return 3;
    }

    if (!flag3)
    {
        SaveStruct23_Substruct2_SetFlag(saveStruct23_substruct2, 3, DATA_SET);
    }

    return 4;
}

THUMB_FUNC u32 FUN_0205FF5C(struct SaveBlock2 *sav2)
{
    u16 res = (u16) GameStats_GetCapped(Sav2_GameStats_get(sav2), 0x35);
    if (res < 20)
    {
        return 0;
    }

    struct SaveStruct23_Substruct2 *saveStruct23_substruct2 = SaveStruct23_GetSubstruct2(sav2);

    BOOL flagD = (u8)SaveStruct23_Substruct2_SetFlag(saveStruct23_substruct2, 0xd, DATA_GET);
    BOOL flag0 = (u8)SaveStruct23_Substruct2_SetFlag(saveStruct23_substruct2, 0, DATA_GET);
    BOOL flag1 = (u8)SaveStruct23_Substruct2_SetFlag(saveStruct23_substruct2, 1, DATA_GET);

    BOOL flagE = (u8)SaveStruct23_Substruct2_SetFlag(saveStruct23_substruct2, 0xe, DATA_GET);
    BOOL flag2 = (u8)SaveStruct23_Substruct2_SetFlag(saveStruct23_substruct2, 2, DATA_GET);
    BOOL flag3 = (u8)SaveStruct23_Substruct2_SetFlag(saveStruct23_substruct2, 3, DATA_GET);

    if (flagD && flag0 && flag1)
    {
        return 0;
    }

    if (!flagD)
    {
        if (flagE)
        {
            return 4;
        }

        return 1;
    }

    if (res < 50)
    {
        return 0;
    }

    if (!flag0)
    {
        if (flag2)
        {
            return 5;
        }

        return 2;
    }

    if (res < 100)
    {
        return 0;
    }

    if (flag1)
    {
        return 0;
    }

    if (flag3)
    {
        return 6;
    }

    return 3;
}

THUMB_FUNC void FUN_02060044(u16 **param0, u32 *param1)
{
    u16 *ptr = param0[42];

    ptr[18] += param1[0];
    ptr[20] += param1[1];
    ptr[19] += param1[2];
}

THUMB_FUNC u32 FUN_02060064(u32 param0)
{
    return param0 * 0x02E90EDD + 1;
}

THUMB_FUNC u32 FUN_02060070(u32 param0)
{
    return param0 * 0x5D588B65 + 1;
}

THUMB_FUNC u32 FUN_0206007C(struct SaveBlock2 *sav2)
{
    u32 res = FUN_02060070(FUN_020287A4(FUN_0202881C(sav2)));

    SaveStruct23_Substruct2_SetField_0x4(SaveStruct23_GetSubstruct2(sav2), res);

    return res;
}

THUMB_FUNC u32 FUN_020600A0(struct SaveBlock2 *sav2)
{
    struct SaveStruct23_Substruct2 *saveStruct23_substruct2 = SaveStruct23_GetSubstruct2(sav2);

    u32 res2 = FUN_02060070(SaveStruct23_Substruct2_GetField_0x4(saveStruct23_substruct2));

    SaveStruct23_Substruct2_SetField_0x4(saveStruct23_substruct2, res2);
    u32 res3 = FUN_02060064(res2);

    SaveStruct23_Substruct1_SetField(SaveStruct23_GetSubstruct1(sav2), FIELD_0x28, &res3);

    return res3;
}

THUMB_FUNC u32 FUN_020600DC(struct SaveBlock2 *sav2)
{
    struct SaveStruct23_Substruct2 *saveStruct23_substruct2 = SaveStruct23_GetSubstruct2(sav2);

    struct SaveStruct23_Substruct1 *saveStruct23_substruct1 = SaveStruct23_GetSubstruct1(sav2);

    u32 res3 = FUN_02060064(SaveStruct23_Substruct2_GetField_0x4(saveStruct23_substruct2));

    int i = 0;
    int res4 = SaveStruct23_Substruct2_SetField_0xC(saveStruct23_substruct2, (u16)SaveStruct23_Substruct1_GetField(saveStruct23_substruct1, FIELD_0x0_2, 0), DATA_GET) * 0x18;

    for (i = 0; i < res4; i++)
    {
        res3 = FUN_02060064(res3);
    }

    SaveStruct23_Substruct1_SetField(SaveStruct23_GetSubstruct1(sav2), FIELD_0x28, &res3);

    return res3;
}

THUMB_FUNC BOOL FUN_02060144(u32 **param0)
{
    if (param0[7][0] == SPECIES_ARCEUS)
    {
        return TRUE;
    }

    return FALSE;
}

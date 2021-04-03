#include "unk_0205FA2C.h"

extern void *UNK_020F96DC;
extern void *UNK_020FA6E8;
extern u32 FUN_02079C70(struct SaveBlock2 *sav2);
extern void FUN_0207B000(void *ptr, u8 param1[12]);
extern void FUN_0207C2A4(void *ptr, struct PlayerData *player_data);
extern u32 FUN_0203384C(u32 param0);
extern u32 FUN_02038790(u32 *param0, u16 param1, u16 param2);
extern u16 *GetVarPointer(void *arg, u16);
extern u32 FUN_02031190();
extern u32 FUN_020316E0(u32 param0);
extern u16 MOD06_02244660(struct UnkStruct_0204639C *param0, u32 param1);
extern u16 MOD06_022446BC(struct UnkStruct_0204639C *param0, u32 param1);
extern u16 MOD06_022446E0(struct UnkStruct_0204639C *param0, u32 param1);
extern void FUN_0202A5CC(u32 param0, u32 param1);
extern u32 FUN_0202A5D0(u32 param0);
extern u32 FUN_0202A150(struct UnkStruct_02029FB0 *param0, u32 param1);
extern u32 FUN_0202A8D8(struct SaveBlock2 *sav2);
extern u32 FUN_0202A578(u32 param0, u32 param1, u32 param2);
extern u32 FUN_02026CC4(struct SaveBlock2 *sav2);
extern u32 FUN_02025D94(u32 param0, u32 param1);
extern u32 FUN_0202A8CC(struct SaveBlock2 *sav2);
extern void FUN_0202A2C4(u32 param0, u32 param1, u32 *param2);
extern u32 FUN_0202A240(u32 param0, u32 param1, u32 param2);
extern int FUN_0202A538(u32 param0, u16 param1, u32 param2);

struct UnkStruct3
{
    /* 0x00 */ struct PlayerParty *player_party;
    /* 0x04 */ struct Bag *bag;
    u32 unk08;
    /* 0x0c */ struct Options *options;
    u32 unk10[4];
    u8 unk20;
    u8 unk21;
    u8 unk22;
    u8 unk23;
    u32 unk24[2];
    u8 unk2c[6];
    u8 unk32:4;
    u8 unk322:4;
    u8 unk33;
    u32 unk34[3];
};

THUMB_FUNC u32 FUN_0205FA2C(u8 *param0, struct UnkStruct_0204639C *param1, u32 heap_id)
{
    struct UnkStruct3 *ptr =
        (struct UnkStruct3 *)AllocFromHeapAtEnd(heap_id, sizeof(struct UnkStruct3));

    struct SaveBlock2 *sav2 = (struct SaveBlock2 *)(param1->unkC);
    MI_CpuFill8(ptr, 0, sizeof(struct UnkStruct3));

    ptr->options = Sav2_PlayerData_GetOptionsAddr(sav2);

    ptr->player_party = SavArray_PlayerParty_get(sav2);

    ptr->bag = Sav2_Bag_get(sav2);

    ptr->unk21 = 0;
    ptr->unk20 = param0[8];
    ptr->unk32 = param0[10];
    ptr->unk322 = param0[11];
    ptr->unk33 = param0[0xc];
    ptr->unk22 = param0[0xd];

    for (u8 i = 0; i < 6; i++)
    {
        ptr->unk2c[i] = param0[i + 0xe];

    }
    

    FUN_020373D4(param1, &UNK_020F96DC, ptr);

    *((u32 **)param0)[5] = ptr;

    return 1;
}

THUMB_FUNC u32 FUN_0205FAD8(u8 *param0, void *param1)
{
    if (FUN_0204647C(param1))
    {
        return 1;
    }

    void *ptr = *((u32 **)param0)[5];

    u8 r1 = *(u8 *)(ptr + 0x22);
    if (r1 != 6)
    {
        if (r1 == 7)
        {
            ((u32 *)param0)[0] = 0;
            return 4;
        }
    }
    else
    {
        ((u32 *)param0)[0] = 1;
        return 4;
    }

    MI_CpuCopy8(ptr + 0x2c, param0 + 0xe, 6);

    param0[0xd] = *(u8 *)(ptr + 0x22);
    FreeToHeap(ptr);

    *((u32 **)param0)[5] = 0;

    return 2;
}


struct UnkStruct4 {
    /* 0x00 */ struct PlayerData *player_data;
    /* 0x04 */ struct Options *options;
    u32 unk08;
    u32 unk0c;
    u8 unk10;
    u8 unk11;
    u8 unk12;
    u8 unk13;
    u8 unk14;
    u8 unk15[3];
    u16 unk18;
    u16 unk1a;
    u32 unk1c;
    u32 unk20;
    u32 unk24;
    u32 unk28;
    u32 unk2c;

};

THUMB_FUNC u32 FUN_0205FB34(u8 *param0, struct UnkStruct_0204639C *param1, u32 heap_id)
{
    struct SaveBlock2 *sav2 = (struct SaveBlock2 *)(param1->unkC);

    struct UnkStruct4 *ptr = (struct UnkStruct4 *)AllocFromHeapAtEnd(heap_id, sizeof(struct UnkStruct4));
    MI_CpuFill8(ptr, 0, sizeof(struct UnkStruct4));

    ptr->options = Sav2_PlayerData_GetOptionsAddr(sav2);
    ptr->player_data = SavArray_PlayerParty_get(sav2);
    ptr->unk1c = FUN_0206BB28(sav2);
    ptr->unk2c = FUN_02079C70(sav2);

    ptr->unk11 = 1;
    ptr->unk14 = param0[0xd];

    ptr->unk13 = GetPartyCount(*(u32 *)ptr);

    ptr->unk18 = 0;
    ptr->unk12 = param0[9];

    ptr->unk20 = FUN_0202A918(sav2);

    FUN_0207B000(ptr, UNK_020F7454);

    FUN_0207C2A4(ptr, Sav2_PlayerData_GetProfileAddr(sav2));

    FUN_020373D4(param1, &UNK_020FA6E8, ptr);

    *((u32 **)param0)[5] = ptr;

    return 3;
}

THUMB_FUNC u32 FUN_0205FBC0(u8 ***param0, void *param1)
{
    if (FUN_0204647C(param1))
    {
        return 3;
    }

    u8 *r0 = param0[5][0];
    ((u8 *)param0)[0xd] = r0[20];
    FreeToHeap(r0);

    param0[5][0] = 0;

    return 0;
}

THUMB_FUNC int FUN_0205FBE8(struct UnkStruct_0204639C *param0)
{
    struct UnkStruct_0204639C *res = FUN_02046528(param0);
    struct SaveBlock2 *sav2 = (struct SaveBlock2 *)FUN_0204652C(param0);
    switch (sav2->unk_00004)
    {
    case 0:
        sav2->unk_00004 = FUN_0205FA2C((u8 *)sav2, res, 0xb);
        break;
    case 1:
        sav2->unk_00004 = FUN_0205FAD8((u8 *)sav2, res);
        break;
    case 2:
        sav2->unk_00004 = FUN_0205FB34((u8 *)sav2, res, 0xb);
        break;
    case 3:
        sav2->unk_00004 = FUN_0205FBC0((u8 ***)sav2, res);
        break;
    case 4:
        FreeToHeap(sav2);
        return 1;
    }

    return 0;
}

struct UnkStruct1
{
    u32 unk00;
    u32 unk04;
    u8 unk08;
    u8 unk09;
    u8 unk0a;
    u8 unk0b;
    u8 unk0c;
    u8 unk0d;
    u16 unk0e;
    u32 unk10;
    u32 unk14;
};

THUMB_FUNC void FUN_0205FC50(struct UnkStruct_0204639C *param0,
    u32 param1,
    u8 param2,
    u8 param3,
    u8 param4,
    u8 param5,
    u8 param6,
    u8 param7)
{
    struct UnkStruct_0204639C *res = FUN_02046528(param0);

    struct UnkStruct1 *ptr = (struct UnkStruct1 *)AllocFromHeap(0xb, sizeof(struct UnkStruct1));
    MI_CpuFill8(ptr, 0, sizeof(struct UnkStruct1));
    ptr->unk08 = param2;
    ptr->unk09 = param3;

    ptr->unk0a = param4;
    ptr->unk0b = param5;
    ptr->unk0c = param6;
    ptr->unk0d = param7;
    ptr->unk14 = param1;

    FUN_0204640C(res->unk10, &FUN_0205FBE8, (u32 *)ptr);
}

THUMB_FUNC u32 FUN_0205FC9C(u16 *param0, u32 *param1)
{
    if (FUN_0203384C(param1[3]))
    {

        ((u32 *)param0)[2] = FUN_02038790(param1, param0[9], param0[10]);
        return 1;
    }

    ((u32 *)param0)[0] = 1;
    return 2;
}

THUMB_FUNC u32 FUN_0205FCC4(u32 **param0, void *param1)
{
    if (FUN_0204647C(param1))
    {
        return 1;
    }

    param0[0] = param0[2][8];
    FreeToHeap(param0[2]);

    return 2;
}

THUMB_FUNC int FUN_0205FCE8(struct UnkStruct_0204639C *param0)
{
    struct UnkStruct_0204639C *res = FUN_02046528(param0);
    struct SaveBlock2 *sav2 = (struct SaveBlock2 *)FUN_0204652C(param0);

    switch (sav2->unk_00004)
    {
    case 0:
        sav2->unk_00004 = FUN_0205FC9C((u16 *)sav2, (u32 *)res);
        break;
    case 1:
        sav2->unk_00004 = FUN_0205FCC4((u32 **)sav2, (void *)res);
        break;
    case 2:
        u16 *var = GetVarPointer(res, ((u16 *)sav2)[8]);
        *var = sav2->flashOkay;
        FreeToHeap(sav2);

        return 1;
    }

    return 0;
}

struct UnkStruct2
{
    u32 unk00;
    u32 unk04;
    u8 unk08;
    u8 unk09;
    u8 unk0a;
    u8 unk0b;
    u8 unk0c;
    u8 unk0d;
    u16 unk0e;
    u16 unk10;
    u16 unk12;
    u16 unk14;
    u16 unk16;
};

THUMB_FUNC void FUN_0205FD38(struct UnkStruct_0204639C *param0, u16 param1, u16 param2, u16 param3)
{
    struct UnkStruct_0204639C *res = FUN_02046528(param0);
    struct UnkStruct2 *ptr = (struct UnkStruct2 *)AllocFromHeap(0xb, sizeof(struct UnkStruct2));
    MI_CpuFill8(ptr, 0, sizeof(struct UnkStruct2));

    ptr->unk12 = param1;
    ptr->unk14 = param3;
    ptr->unk10 = param2;

    FUN_0204640C(res->unk10, &FUN_0205FCE8, (u32 *)ptr);
}

THUMB_FUNC int FUN_0205FD70(struct UnkStruct_0204639C *param0)
{
    struct UnkStruct_0204639C *res = FUN_02046528(param0);
    u16 *res2 = (u16 *)FUN_0204652C(param0);
    u32 res3 = FUN_020316E0(1 - FUN_02031190());
    if (res3 == 0)
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
    struct UnkStruct_0204639C *res = FUN_02046528(param0);

    u16 *ptr = AllocFromHeap(0xb, 2 * sizeof(u16));
    MI_CpuFill8(ptr, 0, 2 * sizeof(u16));

    ptr[0] = param1;
    ptr[1] = param2;

    FUN_0204640C(res->unk10, &FUN_0205FD70, ptr);
}

THUMB_FUNC u32 FUN_0205FE10(struct SaveBlock2 *sav2)
{

    u16 res = FUN_0202A150(FUN_02029FC8(sav2), 0x35);
    if (res < 20)
    {
        return 0;
    }

    u32 res2 = FUN_0202A8D8(sav2);

    u8 res3 = FUN_0202A578(res2, 0xd, 0);
    u8 res4 = FUN_0202A578(res2, 0, 0);
    u8 res5 = FUN_0202A578(res2, 1, 0);

    u8 res6 = FUN_0202A578(res2, 0xe, 0);
    u8 res7 = FUN_0202A578(res2, 2, 0);
    u8 res8 = FUN_0202A578(res2, 3, 0);

    if (res3 != 0 && res4 != 0 && res5 != 0)
    {
        return 0;
    }

    u32 res9 = FUN_02026CC4(sav2);
    if (res3 == 0)
    {
        if (FUN_02025D94(res9, 0x55) != 0)
        {
            FUN_0202A578(res2, 0xd, 1);
            return 1;
        }

        if (res6 == 0)
        {
            FUN_0202A578(res2, 0xe, 1);
        }

        return 4;
    }

    if (res < 50)
    {
        return 0;
    }

    if (res4 == 0)
    {
        if (FUN_02025D94(res9, 0x56) != 0)
        {
            FUN_0202A578(res2, 0, 1);
            return 2;
        }

        if (res7 == 0)
        {
            FUN_0202A578(res2, 2, 1);
        }

        return 4;
    }

    if (res < 100 || res5 != 0)
    {
        return 0;
    }

    if (FUN_02025D94(res9, 0x57) != 0)
    {
        FUN_0202A578(res2, 1, 1);
        return 3;
    }

    if (res8 == 0)
    {
        FUN_0202A578(res2, 3, 1);
    }

    return 4;
}

THUMB_FUNC u32 FUN_0205FF5C(struct SaveBlock2 *sav2)
{
    u16 res = FUN_0202A150(FUN_02029FC8(sav2), 0x35);
    if (res < 20)
    {
        return 0;
    }

    u32 res2 = FUN_0202A8D8(sav2);

    u8 res3 = FUN_0202A578(res2, 0xd, 0);
    u8 res4 = FUN_0202A578(res2, 0, 0);
    u8 res5 = FUN_0202A578(res2, 1, 0);

    u8 res6 = FUN_0202A578(res2, 0xe, 0);
    u8 res7 = FUN_0202A578(res2, 2, 0);
    u8 res8 = FUN_0202A578(res2, 3, 0);

    if (res3 != 0 && res4 != 0 && res5 != 0)
    {
        return 0;
    }

    if (res3 == 0)
    {
        if (res6 != 0)
        {
            return 4;
        }

        return 1;
    }

    if (res < 50)
    {
        return 0;
    }

    if (res4 == 0)
    {
        if (res7 != 0)
        {
            return 5;
        }

        return 2;
    }

    if (res < 100)
    {
        return 0;
    }

    if (res5 != 0)
    {
        return 0;
    }

    if (res8 != 0)
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

    FUN_0202A5CC(FUN_0202A8D8(sav2), res);

    return res;
}

THUMB_FUNC u32 FUN_020600A0(struct SaveBlock2 *sav2)
{
    u32 res = FUN_0202A8D8(sav2);

    u32 res2 = FUN_02060070(FUN_0202A5D0(res));

    FUN_0202A5CC(res, res2);
    u32 res3 = FUN_02060064(res2);

    FUN_0202A2C4(FUN_0202A8CC(sav2), 0xa, &res3);

    return res3;
}

THUMB_FUNC u32 FUN_020600DC(struct SaveBlock2 *sav2)
{
    u32 res = FUN_0202A8D8(sav2);

    u32 res2 = FUN_0202A8CC(sav2);

    u32 res3 = FUN_02060064(FUN_0202A5D0(res));

    int i = 0;
    int res4 = FUN_0202A538(res, FUN_0202A240(res2, 0, 0), 0) * 0x18;

    for (i = 0; i < res4; i++)
    {
        res3 = FUN_02060064(res3);
    }

    FUN_0202A2C4(FUN_0202A8CC(sav2), 0xa, &res3);

    return res3;
}

THUMB_FUNC BOOL FUN_02060144(u32 **param0)
{
    if (param0[7][0] == 0x1ED)
    {
        return TRUE;
    }

    return FALSE;
}

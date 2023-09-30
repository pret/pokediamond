#include "global.h"
#include "unk_0205FA2C.h"
#include "battle_setup.h"
#include "unk_020337E8.h"
#include "unk_0202A1E0.h"
#include "overlay_manager.h"

extern OverlayManagerTemplate UNK_020F96DC;
extern OverlayManagerTemplate UNK_020FA6E8;
extern u32 sub_02079C70(struct SaveData *save);
extern void sub_0207B000(struct UnkPlayerStruct2_0205FA2C *ptr, const u8 param1[12]);
extern void sub_0207C2A4(struct UnkPlayerStruct2_0205FA2C *ptr, PlayerProfile *player_data);
extern u32 *sub_02038790(struct FieldSystem *fieldSystem, u16 param1, u16 param2);
extern u16 *GetVarPointer(struct FieldSystem *fieldSystem, u16);
extern u16 ov06_02244660(struct FieldSystem *fieldSystem, u8 *param1);
extern u16 ov06_022446BC(struct FieldSystem *fieldSystem, u8 *param1);
extern u16 ov06_022446E0(struct FieldSystem *fieldSystem, u8 *param1);
extern u32 sub_02026CC4(struct SaveData *save);
extern u32 sub_02025D94(u32 param0, u32 param1);

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

u32 sub_0205FA2C(
    struct UnkCallbackStruct1_0205FA2C *param0, struct FieldSystem *fieldSystem, HeapID heapId)
{
    struct UnkPlayerStruct1_0205FA2C *ptr = (struct UnkPlayerStruct1_0205FA2C *)AllocFromHeapAtEnd(
        heapId, sizeof(struct UnkPlayerStruct1_0205FA2C));

    struct SaveData *save = fieldSystem->saveData;
    MI_CpuFill8(ptr, 0, sizeof(struct UnkPlayerStruct1_0205FA2C));

    ptr->options = Save_PlayerData_GetOptionsAddr(save);

    ptr->player_party = SaveArray_Party_Get(save);

    ptr->bag = Save_Bag_Get(save);

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

    sub_020373D4(fieldSystem, &UNK_020F96DC, ptr);

    *param0->unk14 = ptr;

    return 1;
}

u32 sub_0205FAD8(
    struct UnkCallbackStruct1_0205FA2C *param0, struct FieldSystem *fieldSystem)
{
    if (FieldSystem_ApplicationIsRunning(fieldSystem))
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

u32 sub_0205FB34(
    struct UnkCallbackStruct1_0205FA2C *param0, struct FieldSystem *fieldSystem, HeapID heapId)
{
    struct SaveData *save = fieldSystem->saveData;

    struct UnkPlayerStruct2_0205FA2C *ptr = (struct UnkPlayerStruct2_0205FA2C *)AllocFromHeapAtEnd(
        heapId, sizeof(struct UnkPlayerStruct2_0205FA2C));
    MI_CpuFill8(ptr, 0, sizeof(struct UnkPlayerStruct2_0205FA2C));

    ptr->options = Save_PlayerData_GetOptionsAddr(save);
    ptr->player_party = SaveArray_Party_Get(save);
    ptr->IsNatDex = SaveArray_IsNatDexEnabled(save);
    ptr->unk2c = sub_02079C70(save);

    ptr->unk11 = 1;
    ptr->unk14 = param0->unk0d;

    ptr->party_count = (u8)Party_GetCount(ptr->player_party);

    ptr->unk18 = 0;
    ptr->unk12 = param0->unk09;

    ptr->unk20 = sub_0202A918(save);

    sub_0207B000(ptr, UNK_020F7454);

    sub_0207C2A4(ptr, Save_PlayerData_GetProfileAddr(save));

    sub_020373D4(fieldSystem, &UNK_020FA6E8, ptr);

    *param0->unk14 = ptr;

    return 3;
}

u32 sub_0205FBC0(
    struct UnkCallbackStruct1_0205FA2C *param0, struct FieldSystem *fieldSystem)
{
    if (FieldSystem_ApplicationIsRunning(fieldSystem))
    {
        return 3;
    }

    struct UnkPlayerStruct2_0205FA2C *ptr = (struct UnkPlayerStruct2_0205FA2C *)*param0->unk14;
    param0->unk0d = ptr->unk14;
    FreeToHeap(ptr);

    *param0->unk14 = NULL;

    return 0;
}

BOOL sub_0205FBE8(struct TaskManager *taskManager)
{
    struct FieldSystem *fieldSystem = TaskManager_GetFieldSystem(taskManager);
    struct UnkCallbackStruct1_0205FA2C *res2 =
        (struct UnkCallbackStruct1_0205FA2C *)TaskManager_GetEnvironment(taskManager);
    switch (res2->unk04)
    {
    case 0:
        res2->unk04 = sub_0205FA2C(res2, fieldSystem, HEAP_ID_FIELD);
        break;
    case 1:
        res2->unk04 = sub_0205FAD8(res2, fieldSystem);
        break;
    case 2:
        res2->unk04 = sub_0205FB34(res2, fieldSystem, HEAP_ID_FIELD);
        break;
    case 3:
        res2->unk04 = sub_0205FBC0(res2, fieldSystem);
        break;
    case 4:
        FreeToHeap(res2);
        return TRUE;
    }

    return FALSE;
}

void sub_0205FC50(struct TaskManager *taskManager,
    void **param1,
    u8 param2,
    u8 param3,
    u8 param4,
    u8 param5,
    u8 param6,
    u8 param7)
{
    struct FieldSystem *fieldSystem = TaskManager_GetFieldSystem(taskManager);

    struct UnkCallbackStruct1_0205FA2C *ptr = (struct UnkCallbackStruct1_0205FA2C *)AllocFromHeap(
        HEAP_ID_FIELD, sizeof(struct UnkCallbackStruct1_0205FA2C));
    MI_CpuFill8(ptr, 0, sizeof(struct UnkCallbackStruct1_0205FA2C));

    ptr->unk08 = param2;
    ptr->unk09 = param3;
    ptr->unk0a = param4;
    ptr->unk0b = param5;
    ptr->unk0c = param6;
    ptr->unk0d = param7;
    ptr->unk14 = param1;

    TaskManager_Call(fieldSystem->taskManager, &sub_0205FBE8, ptr);
}

u32 sub_0205FC9C(
    struct UnkCallbackStruct2_0205FA2C *param0, struct FieldSystem *fieldSystem)
{
    if (sub_0203384C(fieldSystem->saveData))
    {

        param0->unk08 = sub_02038790(fieldSystem, param0->unk12, param0->unk14);
        return 1;
    }

    param0->unk00 = 1;
    return 2;
}

u32 sub_0205FCC4(
    struct UnkCallbackStruct2_0205FA2C *param0, struct FieldSystem *fieldSystem)
{
    if (FieldSystem_ApplicationIsRunning(fieldSystem))
    {
        return 1;
    }

    param0->unk00 = param0->unk08[8];
    FreeToHeap(param0->unk08);

    return 2;
}

BOOL sub_0205FCE8(struct TaskManager *taskManager)
{
    struct FieldSystem *fieldSystem = TaskManager_GetFieldSystem(taskManager);
    struct UnkCallbackStruct2_0205FA2C *res2 =
        (struct UnkCallbackStruct2_0205FA2C *)TaskManager_GetEnvironment(taskManager);

    switch (res2->unk04)
    {
    case 0:
        res2->unk04 = sub_0205FC9C(res2, fieldSystem);
        break;
    case 1:
        res2->unk04 = sub_0205FCC4(res2, fieldSystem);
        break;
    case 2:
        u16 *var = GetVarPointer(fieldSystem, res2->unk10);
        *var = (u16)res2->unk00;
        FreeToHeap(res2);

        return TRUE;
    }

    return FALSE;
}

void sub_0205FD38(struct TaskManager *taskManager, u16 param1, u16 param2, u16 param3)
{
    struct FieldSystem *fieldSystem = TaskManager_GetFieldSystem(taskManager);
    struct UnkCallbackStruct2_0205FA2C *ptr = (struct UnkCallbackStruct2_0205FA2C *)AllocFromHeap(
        HEAP_ID_FIELD, sizeof(struct UnkCallbackStruct2_0205FA2C));
    MI_CpuFill8(ptr, 0, sizeof(struct UnkCallbackStruct2_0205FA2C));

    ptr->unk12 = param1;
    ptr->unk14 = param3;
    ptr->unk10 = param2;

    TaskManager_Call(fieldSystem->taskManager, &sub_0205FCE8, (u32 *)ptr);
}

BOOL sub_0205FD70(struct TaskManager *taskManager)
{
    struct FieldSystem *fieldSystem = TaskManager_GetFieldSystem(taskManager);
    u16 *res2 = (u16 *)TaskManager_GetEnvironment(taskManager);
    u8 *res3 = sub_020316E0(1 - sub_02031190());
    if (res3 == NULL)
    {
        return FALSE;
    }

    u16 *var = GetVarPointer(fieldSystem, res2[1]);
    switch (res2[0])
    {
    case 0:
        *var = ov06_02244660(fieldSystem, res3);
        break;
    case 1:
        *var = ov06_022446BC(fieldSystem, res3);
        break;
    case 2:
        *var = ov06_022446E0(fieldSystem, res3);
        break;
    }

    FreeToHeap(res2);

    return TRUE;
}

void sub_0205FDDC(struct TaskManager *taskManager, u16 param1, u16 param2)
{
    struct FieldSystem *fieldSystem = TaskManager_GetFieldSystem(taskManager);

    u16 *ptr = AllocFromHeap(HEAP_ID_FIELD, 2 * sizeof(u16));
    MI_CpuFill8(ptr, 0, 2 * sizeof(u16));

    ptr[0] = param1;
    ptr[1] = param2;

    TaskManager_Call(fieldSystem->taskManager, &sub_0205FD70, (u32 *)ptr);
}

u32 sub_0205FE10(struct SaveData *save)
{

    u16 res = (u16) GameStats_GetCapped(Save_GameStats_Get(save), 0x35);
    if (res < 20)
    {
        return 0;
    }

    struct FrontierData *frontierData = Save_FrontierData_Get(save);

    BOOL flagD = (u8)FrontierData_SetFlag(frontierData, 0xd, DATA_GET);
    BOOL flag0 = (u8)FrontierData_SetFlag(frontierData, 0, DATA_GET);
    BOOL flag1 = (u8)FrontierData_SetFlag(frontierData, 1, DATA_GET);

    BOOL flagE = (u8)FrontierData_SetFlag(frontierData, 0xe, DATA_GET);
    BOOL flag2 = (u8)FrontierData_SetFlag(frontierData, 2, DATA_GET);
    BOOL flag3 = (u8)FrontierData_SetFlag(frontierData, 3, DATA_GET);

    if (flagD && flag0 && flag1)
    {
        return 0;
    }

    u32 res9 = sub_02026CC4(save);
    if (!flagD)
    {
        if (sub_02025D94(res9, 0x55) != 0)
        {
            FrontierData_SetFlag(frontierData, 0xd, DATA_SET);
            return 1;
        }

        if (!flagE)
        {
            FrontierData_SetFlag(frontierData, 0xe, DATA_SET);
        }

        return 4;
    }

    if (res < 50)
    {
        return 0;
    }

    if (!flag0)
    {
        if (sub_02025D94(res9, 0x56) != 0)
        {
            FrontierData_SetFlag(frontierData, 0, DATA_SET);
            return 2;
        }

        if (!flag2)
        {
            FrontierData_SetFlag(frontierData, 2, DATA_SET);
        }

        return 4;
    }

    if (res < 100 || flag1)
    {
        return 0;
    }

    if (sub_02025D94(res9, 0x57) != 0)
    {
        FrontierData_SetFlag(frontierData, 1, DATA_SET);
        return 3;
    }

    if (!flag3)
    {
        FrontierData_SetFlag(frontierData, 3, DATA_SET);
    }

    return 4;
}

u32 sub_0205FF5C(struct SaveData *save)
{
    u16 res = (u16) GameStats_GetCapped(Save_GameStats_Get(save), 0x35);
    if (res < 20)
    {
        return 0;
    }

    struct FrontierData *frontierData = Save_FrontierData_Get(save);

    BOOL flagD = (u8)FrontierData_SetFlag(frontierData, 0xd, DATA_GET);
    BOOL flag0 = (u8)FrontierData_SetFlag(frontierData, 0, DATA_GET);
    BOOL flag1 = (u8)FrontierData_SetFlag(frontierData, 1, DATA_GET);

    BOOL flagE = (u8)FrontierData_SetFlag(frontierData, 0xe, DATA_GET);
    BOOL flag2 = (u8)FrontierData_SetFlag(frontierData, 2, DATA_GET);
    BOOL flag3 = (u8)FrontierData_SetFlag(frontierData, 3, DATA_GET);

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

void sub_02060044(FieldSystem *fieldSystem, BattleSetupUnkSub138 *battleSetupSub) {
    UnkStruct_02046444 *unkA8 = fieldSystem->unkA8;
    unkA8->unk24 += battleSetupSub->unk0;
    unkA8->unk28 += battleSetupSub->unk4;
    unkA8->unk26 += battleSetupSub->unk8;
}

u32 sub_02060064(u32 param0)
{
    return param0 * 0x02E90EDD + 1;
}

u32 sub_02060070(u32 param0)
{
    return param0 * 0x5D588B65 + 1;
}

u32 sub_0206007C(struct SaveData *save)
{
    u32 res = sub_02060070(sub_020287A4(sub_0202881C(save)));

    FrontierData_SetField_0x4(Save_FrontierData_Get(save), res);

    return res;
}

u32 sub_020600A0(struct SaveData *save)
{
    struct FrontierData *frontierData = Save_FrontierData_Get(save);

    u32 res2 = sub_02060070(FrontierData_GetField_0x4(frontierData));

    FrontierData_SetField_0x4(frontierData, res2);
    u32 res3 = sub_02060064(res2);

    SaveStruct23_Substruct1_SetField(SaveStruct23_GetSubstruct1(save), FIELD_0x28, &res3);

    return res3;
}

u32 sub_020600DC(struct SaveData *save)
{
    struct FrontierData *frontierData = Save_FrontierData_Get(save);

    struct SaveStruct23_Substruct1 *saveStruct23_substruct1 = SaveStruct23_GetSubstruct1(save);

    u32 res3 = sub_02060064(FrontierData_GetField_0x4(frontierData));

    int i = 0;
    int res4 = FrontierData_SetField_0xC(frontierData, (u16)SaveStruct23_Substruct1_GetField(saveStruct23_substruct1, FIELD_0x0_2, 0), DATA_GET) * 0x18;

    for (i = 0; i < res4; i++)
    {
        res3 = sub_02060064(res3);
    }

    SaveStruct23_Substruct1_SetField(SaveStruct23_GetSubstruct1(save), FIELD_0x28, &res3);

    return res3;
}

BOOL sub_02060144(u32 **param0)
{
    if (param0[7][0] == SPECIES_ARCEUS)
    {
        return TRUE;
    }

    return FALSE;
}

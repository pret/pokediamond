#include "global.h"
#include "msgdata.h"
#include "heap.h"
#include "save.h"
#include "math_util.h"
#include "unk_020139D8.h"
#include "msgdata/msg.naix"

const u8 sNarcLanguages[][2] = {
    { LANGUAGE_JAPANESE, 0 },
    { LANGUAGE_ENGLISH,  1 },
    { LANGUAGE_FRENCH,   2 },
    { LANGUAGE_ITALIAN,  3 },
    { LANGUAGE_GERMAN,   4 },
    { LANGUAGE_SPANISH,  5 },
};

const u16 sNarcMsgBanks[] = {
    NARC_msg_narc_0362_bin, // Species names
    NARC_msg_narc_0589_bin, // Move names
    NARC_msg_narc_0565_bin, // Type names
    NARC_msg_narc_0553_bin, // Ability names
    NARC_msg_narc_0388_bin, // Trainer
    NARC_msg_narc_0389_bin, // People
    NARC_msg_narc_0390_bin, // Greetings
    NARC_msg_narc_0391_bin, // Lifestyle
    NARC_msg_narc_0392_bin, // Feelings
    NARC_msg_narc_0393_bin, // Tough words
    NARC_msg_narc_0394_bin  // Union
};

const u16 sNarcMsgCounts[] = {
    496, // Species names
    468, // Move names
    18,  // Type names
    124, // Ability names
    38,  // Trainer
    38,  // People
    107, // Greetings
    104, // Lifestyle
    47,  // Feelings
    32,  // Tough words
    23   // Union
};

const u16 UNK_020ED580[] = { 0x04C0, 0x04F0 };
const u16 UNK_020ED5A8[] = { 0x04A7, 0x04E1 };
const u16 UNK_020ED5AC[] = { 0x0479, 0x0498, 0x049B, 0x049C };
const u16 UNK_020ED5A0[] = { 0x048F, 0x0497 };
const u16 UNK_020ED59C[] = { 0x04FC, 0x0596 };
const u16 UNK_020ED594[] = { 0x047A, 0x048D };
const u16 UNK_020ED58C[] = { 0x0441, 0x0599 };
const u16 UNK_020ED590[] = { 0x042C, 0x059D };
const u16 UNK_020ED5A4[] = { 0x04B0, 0x04FF };
const u16 UNK_020ED598[] = { 0x04B6, 0x0505 };
const u16 UNK_020ED584[] = { 0x024E, 0x03D2 };
const u16 UNK_020ED588[] = { 0x04BB, 0x0500 };

const struct UnkStruct_020ED5EC
{
    const u16 * data;
    s32 count;
} UNK_020ED5EC[] = {
    { UNK_020ED58C, NELEMS(UNK_020ED58C) },
    { UNK_020ED580, NELEMS(UNK_020ED580) },
    { UNK_020ED5A8, NELEMS(UNK_020ED5A8) },
    { UNK_020ED5AC, NELEMS(UNK_020ED5AC) },
    { UNK_020ED5A0, NELEMS(UNK_020ED5A0) },
    { UNK_020ED59C, NELEMS(UNK_020ED59C) },
    { UNK_020ED588, NELEMS(UNK_020ED588) },
    { UNK_020ED584, NELEMS(UNK_020ED584) },
    { UNK_020ED590, NELEMS(UNK_020ED590) },
    { UNK_020ED5A4, NELEMS(UNK_020ED5A4) },
    { UNK_020ED598, NELEMS(UNK_020ED598) },
    { UNK_020ED594, NELEMS(UNK_020ED594) },
};

struct UnkStruct_020139D8 * EasyChatManager_New(HeapID heapId)
{
    struct UnkStruct_020139D8 * ret = (struct UnkStruct_020139D8 *)AllocFromHeap(heapId, sizeof(struct UnkStruct_020139D8));
    s32 i;
    for (i = 0; i < 11; i++)
    {
        ret->heapId = heapId; // inadvertently inside the loop
        ret->msgDatas[i] = NewMsgDataFromNarc(MSGDATA_LOAD_LAZY, NARC_MSGDATA_MSG, sNarcMsgBanks[i], heapId);
    }
    return ret;
}

void EasyChatManager_Delete(struct UnkStruct_020139D8 * unk)
{
    s32 i;
    for (i = 0; i < 11; i++)
    {
        DestroyMsgData(unk->msgDatas[i]);
    }
    FreeToHeap(unk);
}

void EasyChatManager_ReadWordIntoString(struct UnkStruct_020139D8 * unk, u16 wordIdx, struct String * str)
{
    s32 msgBank;
    s32 msgNo;
    GetCategoryAndMsgNoByECWordIdx(wordIdx, &msgBank, &msgNo);
    ReadMsgDataIntoString(unk->msgDatas[msgBank], (u32)msgNo, str);
}

void GetECWordIntoStringByIndex(u32 wordIdx, struct String * a1)
{
    s32 msgBank;
    s32 msgNo;
    if (wordIdx != 0xFFFF)
    {
        GetCategoryAndMsgNoByECWordIdx(wordIdx, &msgBank, &msgNo);
        msgBank = sNarcMsgBanks[msgBank];
        ReadMsgData_NewNarc_ExistingString(NARC_MSGDATA_MSG, (u32)msgBank, (u32)msgNo, HEAP_ID_DEFAULT, a1);
    }
    else
        StringSetEmpty(a1);
}

u16 GetECWordIndexByPair(u16 msgBank, u16 msgNo)
{
    u32 i;
    u16 k;
    u16 j;
    for (i = 0; i < 11; i++)
    {
        if (msgBank == sNarcMsgBanks[i])
        {
            for (j = 0, k = 0; j < i; j++)
                k += sNarcMsgCounts[j];
            return (u16)(k + msgNo);
        }
    }
    return 0xFFFF;
}

void GetCategoryAndMsgNoByECWordIdx(u32 wordIdx, s32 * msgBank_p, s32 * msgNo_p)
{
    s32 i;
    s32 j;
    u32 r3;

    r3 = wordIdx & 0xFFF;
    j = 0;

    for (i = 0; i < NELEMS(sNarcMsgCounts); i++)
    {
        j += sNarcMsgCounts[i];
        if (r3 < j)
        {
            *msgBank_p = i;
            *msgNo_p = (s32)(r3 - (j - sNarcMsgCounts[i]));
            return;
        }
    }
}

u32 sub_02013B28(void)
{
    return sizeof(struct SaveEasyChat);
}

void sub_02013B2C(struct SaveEasyChat * unk)
{
    u32 i;
    unk->unk_0 = 0;
    unk->unk_4 = 0;
    for (i = 0; i < 6; i++)
    {
        if (sNarcLanguages[i][0] == GAME_LANGUAGE)
        {
            sub_02013C18(unk, sNarcLanguages[i][1]);
            break;
        }
    }
}

struct SaveEasyChat * Save_EasyChat_Get(struct SaveData * save)
{
    return (struct SaveEasyChat *)SaveArray_Get(save, 34);
}

BOOL sub_02013B68(struct SaveEasyChat * unk, u32 a1)
{
    return (BOOL)((unk->unk_4 >> a1) & 1);
}

u32 Save_EasyChat_RandomTrendySayingSet(struct SaveEasyChat * unk)
{
    u32 i;
    u32 count;
    u32 which_bit;
    for (i = 0, count = 0; i < 32; i++)
    {
        if (!((unk->unk_4 >> i) & 1))
            count++;
    }
    if (count != 0)
    {
        which_bit = LCRandom() % count;
        for (i = 0; i < 32; i++)
        {
            if (!((unk->unk_4 >> i) & 1))
            {
                if (which_bit == 0)
                {
                    unk->unk_4 |= (1 << i);
                    return i;
                }
                which_bit--;
            }
        }
    }
    return 32;
}

BOOL Save_EasyChat_TrendySayingsUnlockedAllCheck(struct SaveEasyChat * unk)
{
    u32 i;
    for (i = 0; i < 32; i++)
    {
        if (!((unk->unk_4 >> i) & 1))
            return FALSE;
    }
    return TRUE;
}

u16 TrendyWordIdxToECWord(u32 a0)
{
    s32 i;
    u16 skip = 0;
    for (i = 0; i < 9; i++)
        skip += sNarcMsgCounts[i];
    return (u16)(skip + a0);
}

BOOL sub_02013C0C(struct SaveEasyChat * unk, u32 a1)
{
    return (BOOL)((unk->unk_0 >> a1) & 1);
}

void sub_02013C18(struct SaveEasyChat * unk, u32 a1)
{
    unk->unk_0 |= (1 << a1);
}

s32 sub_02013C28(u16 a0)
{
    s32 r3;
    s32 r4;

    for (r3 = 0; r3 < NELEMS(UNK_020ED5EC); r3++)
    {
        for (r4 = 0; r4 < UNK_020ED5EC[r3].count; r4++)
        {
            if (a0 == UNK_020ED5EC[r3].data[r4])
                return UNK_020ED5EC[r3].count - 1;
        }
    }
    return 0;
}

u16 sub_02013C6C(u16 a0, s32 a1)
{
    s32 r7;
    s32 r2;
    s32 r0;

    for (r7 = 0; r7 < NELEMS(UNK_020ED5EC); r7++)
    {
        for (r2 = 0; r2 < UNK_020ED5EC[r7].count; r2++)
        {
            if (a0 == UNK_020ED5EC[r7].data[r2])
            {
                // ERROR: Infinite loop when reached
                for (r0 = 0; /*r0 <*/ UNK_020ED5EC[r7].count; r0++)
                {
                    if (a1 == 0)
                        return UNK_020ED5EC[r7].data[r0];
                    a1--;
                }
                GF_ASSERT(0);
                return 0xFFFF;
            }
        }
    }
    return a0;
}

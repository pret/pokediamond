#include "global.h"
#include "heap.h"
#include "string16.h"
#include "player_data.h"
#include "msgdata.h"
#include "pokemon.h"
#include "pokemon_storage_system.h"
#include "unk_02015CC0.h"
#include "unk_020286F8.h"
#include "filesystem.h"
#include "unk_0201B8B8.h"
#include "trainer_data.h"
#include "script_buffers.h"
#include "unk_02024E64.h"
#include "text.h"

#pragma thumb on

extern u32 GetCityNamesMsgdataIdByCountry(u32);
extern void GetECWordIntoStringByIndex(u32 a0, struct String * a1);
extern void StringCat_HandleTrainerName(struct String * dest, const struct String * src);
extern void StrAddChar(struct String * str, u16 val);
extern void * GfGfxLoader_GetCharData(NarcId, s32, s32, struct UnkStruct_0200B870_sub **, u32);
extern void * GfGfxLoader_LoadFromNarc(NarcId narcId, s32 memberNo, BOOL isCompressed, u32 heap_id, BOOL allocAtEnd);

const u16 UNK_020ECE6C[][2] = {
    { 0x0140, 0x0008 },
    { 0x0160, 0x0010 },
    { 0x01A0, 0x0010 },
    { 0x01E0, 0x0010 },
    { 0x0220, 0x0010 },
    { 0x0260, 0x0010 },
    { 0x02A0, 0x0010 },
};

const u16 UNK_020ECE64[] = {
    382,
    384,
    383,
    0
};

struct ScrStrBufs * ScrStrBufs_new(u32 heap_id)
{
    return ScrStrBufs_new_custom(8, 32, heap_id);
}

struct ScrStrBufs * ScrStrBufs_new_custom(u32 nstr, u32 strlen, u32 heap_id)
{
    GF_ASSERT(nstr != 0);
    GF_ASSERT(strlen != 0);
    struct ScrStrBufs * r4 = AllocFromHeapAtEnd(heap_id, sizeof(struct ScrStrBufs));
    if (r4 != NULL)
    {
        r4->count = nstr;
        r4->heap_id = heap_id;
        r4->tmpbuf = String_ctor(strlen, heap_id);
        if (r4->tmpbuf != NULL)
        {
            r4->array = AllocFromHeapAtEnd(heap_id, nstr * sizeof(struct UnkStruct_0200AA80_sub));
            if (r4->array != NULL)
            {
                int i;
                for (i = 0; i < nstr; i++)
                {
                    ScrStrBufs_InitSub(&r4->array[i]);
                    r4->array[i].msg = String_ctor(strlen, heap_id);
                    if (r4->array[i].msg == NULL)
                        break;
                }
                if (i == nstr)
                    return r4;
            }
        }
    }
    return NULL;
}

void ScrStrBufs_delete(struct ScrStrBufs * ptr)
{
    GF_ASSERT(ptr->count != 0);
    if (ptr->array != NULL)
    {
        int i;
        for (i = 0; i < ptr->count; i++)
        {
            if (ptr->array[i].msg == NULL)
                break;
            String_dtor(ptr->array[i].msg);
        }
        FreeToHeap(ptr->array);
    }
    if (ptr->tmpbuf != NULL)
        String_dtor(ptr->tmpbuf);
    ptr->count = 0;
    FreeToHeap(ptr);
}

void ScrStrBufs_InitSub(struct UnkStruct_0200AA80_sub * sub)
{
#pragma unused(sub)
}

void SetStringAsPlaceholder(struct ScrStrBufs * mgr, u32 idx, struct String * str, struct UnkStruct_0200AA80_sub_sub * a3)
{
    GF_ASSERT(idx < mgr->count);
    if (idx < mgr->count)
    {
        if (a3 != NULL)
        {
            mgr->array[idx].attrs = *a3;
        }
        StringCopy(mgr->array[idx].msg, str);
    }
}

void BufferString(struct ScrStrBufs * mgr, u32 idx, struct String * str, u32 a3, u32 a4, u32 a5)
{
#pragma unused(a3,a4,a5)
    SetStringAsPlaceholder(mgr, idx, str, NULL);
}

void BufferPlayersName(struct ScrStrBufs * mgr, u32 idx, struct PlayerData * data)
{
    u16 * name = PlayerProfile_GetNamePtr(data);
    CopyU16ArrayToString(mgr->tmpbuf, name);
    SetStringAsPlaceholder(mgr, idx, mgr->tmpbuf, NULL);
}

void BufferRivalsName(struct ScrStrBufs * mgr, u32 idx, struct SaveBlock2 * sav2)
{
    u16 * name = GetRivalNamePtr(FUN_02024EC0(sav2));
    CopyU16ArrayToString(mgr->tmpbuf, name);
    SetStringAsPlaceholder(mgr, idx, mgr->tmpbuf, NULL);
}

void BufferFriendsName(struct ScrStrBufs * mgr, u32 idx, struct SaveBlock2 * sav2)
{
    struct PlayerData * data = Sav2_PlayerData_GetProfileAddr(sav2);
    struct MsgData * msgData = NewMsgDataFromNarc(1, NARC_MSGDATA_MSG, 497, mgr->heap_id);
    if (PlayerProfile_GetTrainerGender(data) == 0)
    {
        ReadMsgDataIntoString(msgData, 1, mgr->tmpbuf);
    }
    else
    {
        ReadMsgDataIntoString(msgData, 0, mgr->tmpbuf);
    }
    SetStringAsPlaceholder(mgr, idx, mgr->tmpbuf, NULL);
    DestroyMsgData(msgData);
}

void BufferBoxMonSpeciesName(struct ScrStrBufs * mgr, u32 idx, struct BoxPokemon * mon)
{
    struct MsgData * msgData = NewMsgDataFromNarc(1, NARC_MSGDATA_MSG, 362, mgr->heap_id);
    ReadMsgDataIntoString(msgData, GetBoxMonData(mon, MON_DATA_SPECIES, NULL), mgr->tmpbuf);
    SetStringAsPlaceholder(mgr, idx, mgr->tmpbuf, NULL);
    DestroyMsgData(msgData);
}

void BufferBoxMonSpeciesNameWithArticle(struct ScrStrBufs * mgr, u32 idx, struct BoxPokemon * mon)
{
    BufferSpeciesNameWithArticle(mgr, idx, GetBoxMonData(mon, MON_DATA_SPECIES, NULL));
}

void BufferSpeciesNameWithArticle(struct ScrStrBufs * mgr, u32 idx, u32 species)
{
    struct MsgData * msgData = NewMsgDataFromNarc(1, NARC_MSGDATA_MSG, 363, mgr->heap_id);
    ReadMsgDataIntoString(msgData, species, mgr->tmpbuf);
    SetStringAsPlaceholder(mgr, idx, mgr->tmpbuf, NULL);
    DestroyMsgData(msgData);
}

void BufferBoxMonNickname(struct ScrStrBufs * mgr, u32 idx, struct BoxPokemon * mon)
{
    GetBoxMonData(mon, MON_DATA_NICKNAME_3, mgr->tmpbuf);
    SetStringAsPlaceholder(mgr, idx, mgr->tmpbuf, NULL);
}

void BufferBoxMonOTName(struct ScrStrBufs * mgr, u32 idx, struct BoxPokemon * mon)
{
    GetBoxMonData(mon, MON_DATA_OT_NAME_2, mgr->tmpbuf);
    SetStringAsPlaceholder(mgr, idx, mgr->tmpbuf, NULL);
}

void BufferIntegerAsString(struct ScrStrBufs * mgr, u32 idx, int num, u32 ndigits, int strConvMode, BOOL whichCharset)
{
    String16_FormatInteger(mgr->tmpbuf, num, ndigits, strConvMode, whichCharset);
    SetStringAsPlaceholder(mgr, idx, mgr->tmpbuf, NULL);
}

void BufferMoveName(struct ScrStrBufs * mgr, u32 idx, u32 move)
{
    struct MsgData * msgData = NewMsgDataFromNarc(1, NARC_MSGDATA_MSG, 588, mgr->heap_id);
    if (msgData != NULL)
    {
        ReadMsgDataIntoString(msgData, move, mgr->tmpbuf);
        SetStringAsPlaceholder(mgr, idx, mgr->tmpbuf, NULL);
        DestroyMsgData(msgData);
    }
}

void BufferRibbonNameOrDesc(struct ScrStrBufs * mgr, u32 idx, u32 ribbon)
{
    struct MsgData * msgData = NewMsgDataFromNarc(1, NARC_MSGDATA_MSG, 484, mgr->heap_id);
    if (msgData != NULL)
    {
        ReadMsgDataIntoString(msgData, ribbon, mgr->tmpbuf);
        SetStringAsPlaceholder(mgr, idx, mgr->tmpbuf, NULL);
        DestroyMsgData(msgData);
    }
}

void BufferAbilityName(struct ScrStrBufs * mgr, u32 idx, u32 ability)
{
    struct MsgData * msgData = NewMsgDataFromNarc(1, NARC_MSGDATA_MSG, 552, mgr->heap_id);
    if (msgData != NULL)
    {
        ReadMsgDataIntoString(msgData, ability, mgr->tmpbuf);
        SetStringAsPlaceholder(mgr, idx, mgr->tmpbuf, NULL);
        DestroyMsgData(msgData);
    }
}

void BufferNatureName(struct ScrStrBufs * mgr, u32 idx, u32 nature)
{
    struct MsgData * msgData = NewMsgDataFromNarc(1, NARC_MSGDATA_MSG, 190, mgr->heap_id);
    ReadMsgDataIntoString(msgData, nature, mgr->tmpbuf);
    SetStringAsPlaceholder(mgr, idx, mgr->tmpbuf, NULL);
    DestroyMsgData(msgData);
}

void BufferItemName(struct ScrStrBufs * mgr, u32 idx, u32 item)
{
    struct MsgData * msgData = NewMsgDataFromNarc(1, NARC_MSGDATA_MSG, 344, mgr->heap_id);
    if (msgData != NULL)
    {
        ReadMsgDataIntoString(msgData, item, mgr->tmpbuf);
        SetStringAsPlaceholder(mgr, idx, mgr->tmpbuf, NULL);
        DestroyMsgData(msgData);
    }
}

void BufferItemNameWithIndefArticle(struct ScrStrBufs * mgr, u32 idx, u32 item)
{
    struct MsgData * msgData = NewMsgDataFromNarc(1, NARC_MSGDATA_MSG, 346, mgr->heap_id);
    if (msgData != NULL)
    {
        ReadMsgDataIntoString(msgData, item, mgr->tmpbuf);
        SetStringAsPlaceholder(mgr, idx, mgr->tmpbuf, NULL);
        DestroyMsgData(msgData);
    }
}

void BufferItemNamePlural(struct ScrStrBufs * mgr, u32 idx, u32 item)
{
    struct MsgData * msgData = NewMsgDataFromNarc(1, NARC_MSGDATA_MSG, 347, mgr->heap_id);
    if (msgData != NULL)
    {
        ReadMsgDataIntoString(msgData, item, mgr->tmpbuf);
        SetStringAsPlaceholder(mgr, idx, mgr->tmpbuf, NULL);
        DestroyMsgData(msgData);
    }
}

void BufferPocketName(struct ScrStrBufs * mgr, u32 idx, u32 pocket)
{
    struct MsgData * msgData = NewMsgDataFromNarc(1, NARC_MSGDATA_MSG, 349, mgr->heap_id);
    if (msgData != NULL)
    {
        ReadMsgDataIntoString(msgData, pocket, mgr->tmpbuf);
        SetStringAsPlaceholder(mgr, idx, mgr->tmpbuf, NULL);
        DestroyMsgData(msgData);
    }
}

void BufferTypeName(struct ScrStrBufs * mgr, u32 idx, u32 type)
{
    struct MsgData * msgData = NewMsgDataFromNarc(1, NARC_MSGDATA_MSG, 565, mgr->heap_id);
    if (msgData != NULL)
    {
        ReadMsgDataIntoString(msgData, type, mgr->tmpbuf);
        SetStringAsPlaceholder(mgr, idx, mgr->tmpbuf, NULL);
        DestroyMsgData(msgData);
    }
}

void BufferStatName(struct ScrStrBufs * mgr, u32 idx, u32 stat)
{
    struct MsgData * msgData = NewMsgDataFromNarc(1, NARC_MSGDATA_MSG, 495, mgr->heap_id);
    if (msgData != NULL)
    {
        ReadMsgDataIntoString(msgData, stat, mgr->tmpbuf);
        SetStringAsPlaceholder(mgr, idx, mgr->tmpbuf, NULL);
        DestroyMsgData(msgData);
    }
}

void BufferStatusName(struct ScrStrBufs * mgr, u32 idx, u32 status)
{
    struct MsgData * msgData = NewMsgDataFromNarc(1, NARC_MSGDATA_MSG, 205, mgr->heap_id);
    if (msgData != NULL)
    {
        ReadMsgDataIntoString(msgData, status, mgr->tmpbuf);
        SetStringAsPlaceholder(mgr, idx, mgr->tmpbuf, NULL);
        DestroyMsgData(msgData);
    }
}

void BufferFlavorDislikeText(struct ScrStrBufs * mgr, u32 idx, u32 flavor)
{
    struct MsgData * msgData = NewMsgDataFromNarc(1, NARC_MSGDATA_MSG, 548, mgr->heap_id);
    if (msgData != NULL)
    {
        ReadMsgDataIntoString(msgData, flavor, mgr->tmpbuf);
        SetStringAsPlaceholder(mgr, idx, mgr->tmpbuf, NULL);
        DestroyMsgData(msgData);
    }
}

void BufferLandmarkName(struct ScrStrBufs * mgr, u32 idx, u32 landmark)
{
    struct MsgData * msgData = NewMsgDataFromNarc(1, NARC_MSGDATA_MSG, 382, mgr->heap_id);
    if (msgData != NULL)
    {
        ReadMsgDataIntoString(msgData, landmark, mgr->tmpbuf);
        SetStringAsPlaceholder(mgr, idx, mgr->tmpbuf, NULL);
        DestroyMsgData(msgData);
    }
}

void BufferPoketchAppName(struct ScrStrBufs * mgr, u32 idx, u32 app)
{
    struct MsgData * msgData = NewMsgDataFromNarc(1, NARC_MSGDATA_MSG, 406, mgr->heap_id);
    if (msgData != NULL)
    {
        ReadMsgDataIntoString(msgData, app, mgr->tmpbuf);
        SetStringAsPlaceholder(mgr, idx, mgr->tmpbuf, NULL);
        DestroyMsgData(msgData);
    }
}

void BufferTrainerClassName(struct ScrStrBufs * mgr, u32 idx, u32 trclass)
{
    struct MsgData * msgData = NewMsgDataFromNarc(1, NARC_MSGDATA_MSG, 560, mgr->heap_id);
    if (msgData != NULL)
    {
        ReadMsgDataIntoString(msgData, trclass, mgr->tmpbuf);
        SetStringAsPlaceholder(mgr, idx, mgr->tmpbuf, NULL);
        DestroyMsgData(msgData);
    }
}

void BufferTrainerClassNameWithArticle(struct ScrStrBufs * mgr, u32 idx, u32 trclass)
{
    struct MsgData * msgData = NewMsgDataFromNarc(1, NARC_MSGDATA_MSG, 561, mgr->heap_id);
    if (msgData != NULL)
    {
        ReadMsgDataIntoString(msgData, trclass, mgr->tmpbuf);
        SetStringAsPlaceholder(mgr, idx, mgr->tmpbuf, NULL);
        DestroyMsgData(msgData);
    }
}

void BufferTrainerClassNameFromDataStruct(struct ScrStrBufs * mgr, u32 idx, struct TrainerDataLoaded * tr)
{
    struct MsgData * msgData = NewMsgDataFromNarc(1, NARC_MSGDATA_MSG, 560, mgr->heap_id);
    if (msgData != NULL)
    {
        ReadMsgDataIntoString(msgData, tr->data.trainerClass, mgr->tmpbuf);
        SetStringAsPlaceholder(mgr, idx, mgr->tmpbuf, NULL);
        DestroyMsgData(msgData);
    }
}

void BufferTrainerName(struct ScrStrBufs * mgr, u32 idx, u32 msgno)
{
    struct MsgData * msgData = NewMsgDataFromNarc(1, NARC_MSGDATA_MSG, 559, mgr->heap_id);
    if (msgData != NULL)
    {
        ReadMsgDataIntoString(msgData, msgno, mgr->tmpbuf);
        SetStringAsPlaceholder(mgr, idx, mgr->tmpbuf, NULL);
        DestroyMsgData(msgData);
    }
}

void BufferTrainerNameFromDataStruct(struct ScrStrBufs * mgr, u32 idx, struct TrainerDataLoaded * trdata)
{
    CopyU16ArrayToString(mgr->tmpbuf, trdata->name);
    SetStringAsPlaceholder(mgr, idx, mgr->tmpbuf, NULL);
}

void BufferUndergroundItemName(struct ScrStrBufs * mgr, u32 idx, u32 item)
{
    struct MsgData * msgData = NewMsgDataFromNarc(1, NARC_MSGDATA_MSG, 569, mgr->heap_id);
    if (msgData != NULL)
    {
        ReadMsgDataIntoString(msgData, item, mgr->tmpbuf);
        SetStringAsPlaceholder(mgr, idx, mgr->tmpbuf, NULL);
        DestroyMsgData(msgData);
    }
}

void BufferUndergroundItemNameWithArticle(struct ScrStrBufs * mgr, u32 idx, u32 item)
{
    struct MsgData * msgData = NewMsgDataFromNarc(1, NARC_MSGDATA_MSG, 570, mgr->heap_id);
    if (msgData != NULL)
    {
        ReadMsgDataIntoString(msgData, item, mgr->tmpbuf);
        SetStringAsPlaceholder(mgr, idx, mgr->tmpbuf, NULL);
        DestroyMsgData(msgData);
    }
}

void BufferUndergroundTrapName(struct ScrStrBufs * mgr, u32 idx, u32 trap)
{
    struct MsgData * msgData = NewMsgDataFromNarc(1, NARC_MSGDATA_MSG, 571, mgr->heap_id);
    if (msgData != NULL)
    {
        ReadMsgDataIntoString(msgData, trap, mgr->tmpbuf);
        SetStringAsPlaceholder(mgr, idx, mgr->tmpbuf, NULL);
        DestroyMsgData(msgData);
    }
}

void BufferUndergroundTrapNameWithArticle(struct ScrStrBufs * mgr, u32 idx, u32 trap)
{
    struct MsgData * msgData = NewMsgDataFromNarc(1, NARC_MSGDATA_MSG, 572, mgr->heap_id);
    if (msgData != NULL)
    {
        ReadMsgDataIntoString(msgData, trap, mgr->tmpbuf);
        SetStringAsPlaceholder(mgr, idx, mgr->tmpbuf, NULL);
        DestroyMsgData(msgData);
    }
}

void BufferContestJudgeName(struct ScrStrBufs * mgr, u32 idx, u32 judge)
{
    struct MsgData * msgData = NewMsgDataFromNarc(1, NARC_MSGDATA_MSG, 194, mgr->heap_id);
    if (msgData != NULL)
    {
        ReadMsgDataIntoString(msgData, judge, mgr->tmpbuf);
        SetStringAsPlaceholder(mgr, idx, mgr->tmpbuf, NULL);
        DestroyMsgData(msgData);
    }
}

void BufferContestMessage(struct ScrStrBufs * mgr, u32 idx, u32 msg)
{
    struct MsgData * msgData = NewMsgDataFromNarc(1, NARC_MSGDATA_MSG, 191, mgr->heap_id);
    if (msgData != NULL)
    {
        ReadMsgDataIntoString(msgData, msg, mgr->tmpbuf);
        SetStringAsPlaceholder(mgr, idx, mgr->tmpbuf, NULL);
        DestroyMsgData(msgData);
    }
}

void BufferContestMessage2(struct ScrStrBufs * mgr, u32 idx, u32 msg)
{
    struct MsgData * msgData = NewMsgDataFromNarc(1, NARC_MSGDATA_MSG, 191, mgr->heap_id);
    if (msgData != NULL)
    {
        ReadMsgDataIntoString(msgData, msg, mgr->tmpbuf);
        SetStringAsPlaceholder(mgr, idx, mgr->tmpbuf, NULL);
        DestroyMsgData(msgData);
    }
}

void BufferInterviewQuestion(struct ScrStrBufs * mgr, u32 idx, u32 question)
{
    struct MsgData * msgData = NewMsgDataFromNarc(1, NARC_MSGDATA_MSG, 574, mgr->heap_id);
    if (msgData != NULL)
    {
        ReadMsgDataIntoString(msgData, question, mgr->tmpbuf);
        SetStringAsPlaceholder(mgr, idx, mgr->tmpbuf, NULL);
        DestroyMsgData(msgData);
    }
}

void BufferInterviewAnswer(struct ScrStrBufs * mgr, u32 idx, u32 answer)
{
    struct MsgData * msgData = NewMsgDataFromNarc(1, NARC_MSGDATA_MSG, 573, mgr->heap_id);
    if (msgData != NULL)
    {
        ReadMsgDataIntoString(msgData, answer, mgr->tmpbuf);
        SetStringAsPlaceholder(mgr, idx, mgr->tmpbuf, NULL);
        DestroyMsgData(msgData);
    }
}

void BufferDecorationName(struct ScrStrBufs * mgr, u32 idx, u32 decor)
{
    struct MsgData * msgData = NewMsgDataFromNarc(1, NARC_MSGDATA_MSG, 567, mgr->heap_id);
    if (msgData != NULL)
    {
        ReadMsgDataIntoString(msgData, decor, mgr->tmpbuf);
        SetStringAsPlaceholder(mgr, idx, mgr->tmpbuf, NULL);
        DestroyMsgData(msgData);
    }
}

void BufferDecorationNameWithArticle(struct ScrStrBufs * mgr, u32 idx, u32 decor)
{
    struct MsgData * msgData = NewMsgDataFromNarc(1, NARC_MSGDATA_MSG, 568, mgr->heap_id);
    if (msgData != NULL)
    {
        ReadMsgDataIntoString(msgData, decor, mgr->tmpbuf);
        SetStringAsPlaceholder(mgr, idx, mgr->tmpbuf, NULL);
        DestroyMsgData(msgData);
    }
}

void BufferGenderSymbol(struct ScrStrBufs * mgr, u32 idx, u32 gender)
{
    struct MsgData * msgData = NewMsgDataFromNarc(1, NARC_MSGDATA_MSG, 199, mgr->heap_id);
    switch (gender)
    {
    case 0:
        ReadMsgDataIntoString(msgData, 68, mgr->tmpbuf);
        break;
    case 1:
        ReadMsgDataIntoString(msgData, 69, mgr->tmpbuf);
        break;
    default:
        StringSetEmpty(mgr->tmpbuf);
        break;
    }
    SetStringAsPlaceholder(mgr, idx, mgr->tmpbuf, NULL);
    DestroyMsgData(msgData);
}

void BufferBoxName(struct ScrStrBufs * mgr, u32 idx, struct PCStorage * pc, int boxno)
{
    PCStorage_GetBoxName(pc, boxno, mgr->tmpbuf);
    SetStringAsPlaceholder(mgr, idx, mgr->tmpbuf, NULL);
}

void BufferGymName(struct ScrStrBufs * mgr, u32 idx, u32 gym)
{
    struct MsgData * msgData = NewMsgDataFromNarc(1, NARC_MSGDATA_MSG, 331, mgr->heap_id);
    if (msgData != NULL)
    {
        ReadMsgDataIntoString(msgData, gym, mgr->tmpbuf);
        SetStringAsPlaceholder(mgr, idx, mgr->tmpbuf, NULL);
        DestroyMsgData(msgData);
    }
}

void BufferTimeOfDayName(struct ScrStrBufs * mgr, u32 idx, u32 time)
{
    struct MsgData * msgData = NewMsgDataFromNarc(1, NARC_MSGDATA_MSG, 550, mgr->heap_id);
    if (msgData != NULL)
    {
        ReadMsgDataIntoString(msgData, time, mgr->tmpbuf);
        SetStringAsPlaceholder(mgr, idx, mgr->tmpbuf, NULL);
        DestroyMsgData(msgData);
    }
}

void BufferCountryName(struct ScrStrBufs * mgr, u32 idx, u32 country)
{
    struct MsgData * msgData = NewMsgDataFromNarc(1, NARC_MSGDATA_MSG, 612, mgr->heap_id);
    if (msgData != NULL)
    {
        ReadMsgDataIntoString(msgData, country, mgr->tmpbuf);
        SetStringAsPlaceholder(mgr, idx, mgr->tmpbuf, NULL);
        DestroyMsgData(msgData);
    }
}

void BufferCityName(struct ScrStrBufs * mgr, u32 idx, u32 a2, u32 a3)
{
    u32 r2 = GetCityNamesMsgdataIdByCountry(a2);
    if (r2 != 0 && a3 != 0)
    {
        struct MsgData *msgData = NewMsgDataFromNarc(1, NARC_MSGDATA_MSG, (int)r2, mgr->heap_id);
        if (msgData != NULL)
        {
            ReadMsgDataIntoString(msgData, a3, mgr->tmpbuf);
            SetStringAsPlaceholder(mgr, idx, mgr->tmpbuf, NULL);
            DestroyMsgData(msgData);
        }
    }
}

void FUN_0200B518(struct ScrStrBufs * mgr, u32 idx, u32 a2)
{
    GetECWordIntoStringByIndex(a2, mgr->tmpbuf);
    SetStringAsPlaceholder(mgr, idx, mgr->tmpbuf, NULL);
}

void BufferSealName(struct ScrStrBufs * mgr, u32 idx, u32 seal)
{
    struct MsgData * msgData = NewMsgDataFromNarc(1, NARC_MSGDATA_MSG, 10, mgr->heap_id);
    if (msgData != NULL)
    {
        ReadMsgDataIntoString(msgData, seal, mgr->tmpbuf);
        SetStringAsPlaceholder(mgr, idx, mgr->tmpbuf, NULL);
        DestroyMsgData(msgData);
    }
}

void BufferSealNamePlural(struct ScrStrBufs * mgr, u32 idx, u32 seal)
{
    struct MsgData * msgData = NewMsgDataFromNarc(1, NARC_MSGDATA_MSG, 11, mgr->heap_id);
    if (msgData != NULL)
    {
        ReadMsgDataIntoString(msgData, seal, mgr->tmpbuf);
        SetStringAsPlaceholder(mgr, idx, mgr->tmpbuf, NULL);
        DestroyMsgData(msgData);
    }
}

void BufferLocationName(struct ScrStrBufs * mgr, u32 idx, u16 a2)
{
    u32 r6 = (u32)FUN_02015CC0(a2);
    u32 r4 = (u32)FUN_02015CE0(a2);
    struct MsgData * msgData = NewMsgDataFromNarc(1, NARC_MSGDATA_MSG, UNK_020ECE64[r6], mgr->heap_id);
    if (msgData != NULL)
    {
        if (r4 < MsgDataGetCount(msgData))
        {
            ReadMsgDataIntoString(msgData, r4, mgr->tmpbuf);
            SetStringAsPlaceholder(mgr, idx, mgr->tmpbuf, NULL);
            DestroyMsgData(msgData);
            return;
        }
        // Location is invalid.
        // Fallback: Mystery Zone
        DestroyMsgData(msgData);
        msgData = NewMsgDataFromNarc(1, NARC_MSGDATA_MSG, 382, mgr->heap_id);
        if (msgData != NULL)
        {
            ReadMsgDataIntoString(msgData, 0, mgr->tmpbuf);
            SetStringAsPlaceholder(mgr, idx, mgr->tmpbuf, NULL);
            DestroyMsgData(msgData);
        }
    }
}

void BufferPoffinName(struct ScrStrBufs * mgr, u32 idx, u32 poffin)
{
    struct MsgData * msgData = NewMsgDataFromNarc(1, NARC_MSGDATA_MSG, 414, mgr->heap_id);
    if (msgData != NULL)
    {
        ReadMsgDataIntoString(msgData, poffin, mgr->tmpbuf);
        SetStringAsPlaceholder(mgr, idx, mgr->tmpbuf, NULL);
        DestroyMsgData(msgData);
    }
}

void BufferFashionName(struct ScrStrBufs * mgr, u32 idx, u32 fashion)
{
    struct MsgData * msgData = NewMsgDataFromNarc(1, NARC_MSGDATA_MSG, 338, mgr->heap_id);
    if (msgData != NULL)
    {
        ReadMsgDataIntoString(msgData, fashion, mgr->tmpbuf);
        SetStringAsPlaceholder(mgr, idx, mgr->tmpbuf, NULL);
        DestroyMsgData(msgData);
    }
}

void BufferFashionNameWithArticle(struct ScrStrBufs * mgr, u32 idx, u32 fashion)
{
    struct MsgData * msgData = NewMsgDataFromNarc(1, NARC_MSGDATA_MSG, 339, mgr->heap_id);
    if (msgData != NULL)
    {
        ReadMsgDataIntoString(msgData, fashion, mgr->tmpbuf);
        SetStringAsPlaceholder(mgr, idx, mgr->tmpbuf, NULL);
        DestroyMsgData(msgData);
    }
}

void BufferContestBackgroundName(struct ScrStrBufs * mgr, u32 idx, u32 bg)
{
    struct MsgData * msgData = NewMsgDataFromNarc(1, NARC_MSGDATA_MSG, 340, mgr->heap_id);
    if (msgData != NULL)
    {
        ReadMsgDataIntoString(msgData, bg, mgr->tmpbuf);
        SetStringAsPlaceholder(mgr, idx, mgr->tmpbuf, NULL);
        DestroyMsgData(msgData);
    }
}

void BufferEasyChatWord(struct ScrStrBufs * mgr, struct SaveBlock2 * sav2, u32 r5, u32 idx, u32 sp28)
{
    void * r6 = FUN_0202881C(sav2);
    u8 sp10 = FUN_020287F8(r6, r5);
    u8 r7 = FUN_02028804(r6, r5);
    struct String * r4 = String_ctor(64, 4);
    CopyU16ArrayToString(r4, FUN_020287A8(r6, r5, sp28));
    BufferString(mgr, idx, r4, sp10, 1, r7);
    String_dtor(r4);
}

void BufferMonthNameAbbr(struct ScrStrBufs * mgr, u32 idx, u32 month)
{
    struct MsgData * msgData = NewMsgDataFromNarc(1, NARC_MSGDATA_MSG, 364, mgr->heap_id);
    if (msgData != NULL)
    {
        if (month < 1 || month > 12)
            month = 1;
        ReadMsgDataIntoString(msgData, month - 1, mgr->tmpbuf);
        SetStringAsPlaceholder(mgr, idx, mgr->tmpbuf, NULL);
        DestroyMsgData(msgData);
    }
}

void ScrStrBufs_UpperFirstChar(struct ScrStrBufs * mgr, u32 idx)
{
    StrUpperFirstChar(mgr->array[idx].msg);
}

void StringExpandPlaceholders(struct ScrStrBufs * mgr, struct String * dest, struct String * src)
{
    const u16 * cstr = String_c_str(src);
    StringSetEmpty(dest);
    while (*cstr != EOS)
    {
        if (*cstr == 0xFFFE)
        {
            if (MsgArray_ControlCodeIsStrVar(cstr))
            {
                u32 idx = MsgArray_ControlCodeGetField(cstr, 0);
                GF_ASSERT(idx < mgr->count);
                StringCat_HandleTrainerName(dest, mgr->array[idx].msg);
                cstr = MsgArray_SkipControlCode(cstr);
            }
            else
            {
                const u16 * before = cstr;
                cstr = MsgArray_SkipControlCode(cstr);
                while (before < cstr)
                    StrAddChar(dest, *before++);
            }
        }
        else
            StrAddChar(dest, *cstr++);
    }
}

void ScrStrBufs_ResetBuffers(struct ScrStrBufs * mgr)
{
    for (int i = 0; i < mgr->count; i++)
        StringSetEmpty(mgr->array[i].msg);
}

struct UnkStruct_0200B870 * MessagePrinter_new(u32 r5, u32 r6, u32 sp4, u32 r4)
{
    struct UnkStruct_0200B870 * sp8 = AllocFromHeap(r4, sizeof(struct UnkStruct_0200B870));
    if (sp8 != NULL)
    {
        sp8->unk_0 = GfGfxLoader_GetCharData(NARC_GRAPHIC_FONT, 4, 1, &sp8->unk_4, r4);
        int i;
        u8 * ptr = sp8->unk_4->unk_14;
        for (i = 0; i < sp8->unk_4->unk_10; i++)
        {
            switch (ptr[i])
            {
            case 0x00:
                ptr[i] = (u8)((sp4 << 4) | sp4);
                break;
            case 0x01:
                ptr[i] = (u8)((sp4 << 4) | r5);
                break;
            case 0x02:
                ptr[i] = (u8)((sp4 << 4) | r6);
                break;
            case 0x10:
                ptr[i] = (u8)((r5 << 4) | sp4);
                break;
            case 0x11:
                ptr[i] = (u8)((r5 << 4) | r5);
                break;
            case 0x12:
                ptr[i] = (u8)((r5 << 4) | r6);
                break;
            case 0x20:
                ptr[i] = (u8)((r6 << 4) | sp4);
                break;
            case 0x21:
                ptr[i] = (u8)((r6 << 4) | r5);
                break;
            case 0x22:
                ptr[i] = (u8)((r6 << 4) | r6);
                break;
            }
        }
        sp8->unk_28 = sp4;
    }
    return sp8;
}

void MessagePrinter_delete(struct UnkStruct_0200B870 * a0)
{
    if (a0 != NULL)
    {
        if (a0->unk_0 != NULL)
            FreeToHeap(a0->unk_0);
        FreeToHeap(a0);
    }
}

void FUN_0200B9A8(struct UnkStruct_0200B870 * a0, int a1, struct Window *a2, int a3, int a4)
{
    BlitBitmapRectToWindow(a2, a0->unk_4->unk_14 + UNK_020ECE6C[a1][0], 0, 0, UNK_020ECE6C[a1][1], 8, (u16)a3, (u16)a4, UNK_020ECE6C[a1][1], 8);
}

void FUN_0200B9EC(struct UnkStruct_0200B870 * string, u32 value, u32 n, enum PrintingMode mode, struct Window *window, int x, int y)
{
    ConvertUIntToDecimalString(string->data, value, mode, n);
    for (int i = 0; string->data[i] != EOS; i++)
    {
        if (string->data[i] >= CHAR_0 && string->data[i] <= CHAR_9)
        {
            BlitBitmapRectToWindow(window, string->unk_4->unk_14 + (string->data[i] - CHAR_0) * 32, 0, 0, 8, 8, (u16)x, (u16)y, 8, 8);
        }
        else
        {
            FillWindowPixelRect(window, (u8)string->unk_28, (u16)x, (u16)y, 8, 8);
        }
        x += 8;
    }
}

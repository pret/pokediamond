#include "global.h"
#include "filesystem.h"
#include "graphic/font.naix"
#include "heap.h"
#include "message_format.h"
#include "msgdata.h"
#include "msgdata/msg.naix"
#include "msgdata/msg/narc_0199.h"
#include "msgdata/msg/narc_0382.h"
#include "msgdata/msg/narc_0497.h"
#include "player_data.h"
#include "pokemon.h"
#include "pokemon_storage_system.h"
#include "string16.h"
#include "string_control_code.h"
#include "text.h"
#include "trainer_data.h"
#include "unk_02015CC0.h"
#include "unk_02024E64.h"
#include "unk_020286F8.h"

extern u32 GetCityNamesMsgdataIdByCountry(u32);
extern void GetECWordIntoStringByIndex(u32 a0, struct String * a1);
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
    NARC_msg_narc_0382_bin,
    NARC_msg_narc_0384_bin,
    NARC_msg_narc_0383_bin,
    0
};

MessageFormat *MessageFormat_New(u32 heap_id)
{
    return MessageFormat_New_Custom(8, 32, heap_id);
}

MessageFormat *MessageFormat_New_Custom(u32 nstr, u32 strlen, u32 heap_id)
{
    GF_ASSERT(nstr != 0);
    GF_ASSERT(strlen != 0);
    MessageFormat *messageFormat = AllocFromHeapAtEnd(heap_id, sizeof(MessageFormat));
    if (messageFormat != NULL)
    {
        messageFormat->count = nstr;
        messageFormat->heap_id = heap_id;
        messageFormat->buffer = String_New(strlen, heap_id);
        if (messageFormat->buffer != NULL)
        {
            messageFormat->fields = AllocFromHeapAtEnd(heap_id, nstr * sizeof(MessageFormatFields));
            if (messageFormat->fields != NULL)
            {
                s32 i;
                for (i = 0; i < nstr; i++)
                {
                    MessageFormat_InitFields(&messageFormat->fields[i]);
                    messageFormat->fields[i].msg = String_New(strlen, heap_id);
                    if (messageFormat->fields[i].msg == NULL)
                        break;
                }
                if (i == nstr)
                    return messageFormat;
            }
        }
    }
    return NULL;
}

void MessageFormat_Delete(MessageFormat *messageFormat)
{
    GF_ASSERT(messageFormat->count != 0);
    if (messageFormat->fields != NULL)
    {
        for (s32 i = 0; i < messageFormat->count; i++)
        {
            if (messageFormat->fields[i].msg == NULL) {
                break;
            }
            String_Delete(messageFormat->fields[i].msg);
        }
        FreeToHeap(messageFormat->fields);
    }
    if (messageFormat->buffer != NULL)
        String_Delete(messageFormat->buffer);
    messageFormat->count = 0;
    FreeToHeap(messageFormat);
}

void MessageFormat_InitFields(MessageFormatFields *fields)
{
#pragma unused(fields)
}

void SetStringAsPlaceholder(MessageFormat *messageFormat, u32 idx, struct String *str, MessageFormatAttrs *attrs)
{
    GF_ASSERT(idx < messageFormat->count);
    if (idx < messageFormat->count)
    {
        if (attrs != NULL)
        {
            messageFormat->fields[idx].attrs = *attrs;
        }
        StringCopy(messageFormat->fields[idx].msg, str);
    }
}

void BufferString(MessageFormat *messageFormat, u32 idx, struct String * str, u32 a3, u32 a4, u32 a5)
{
#pragma unused(a3,a4,a5)
    SetStringAsPlaceholder(messageFormat, idx, str, NULL);
}

void BufferPlayersName(MessageFormat *messageFormat, u32 idx, struct PlayerData * data)
{
    u16 * name = PlayerProfile_GetNamePtr(data);
    CopyU16ArrayToString(messageFormat->buffer, name);
    SetStringAsPlaceholder(messageFormat, idx, messageFormat->buffer, NULL);
}

void BufferRivalsName(MessageFormat *messageFormat, u32 idx, struct SaveData * save)
{
    u16 * name = GetRivalNamePtr(FUN_02024EC0(save));
    CopyU16ArrayToString(messageFormat->buffer, name);
    SetStringAsPlaceholder(messageFormat, idx, messageFormat->buffer, NULL);
}

void BufferFriendsName(MessageFormat *messageFormat, u32 idx, struct SaveData * save)
{
    struct PlayerData * data = Save_PlayerData_GetProfileAddr(save);
    struct MsgData * msgData = NewMsgDataFromNarc(MSGDATA_LOAD_LAZY, NARC_MSGDATA_MSG, NARC_msg_narc_0497_bin, messageFormat->heap_id);
    if (PlayerProfile_GetTrainerGender(data) == Male)
    {
        ReadMsgDataIntoString(msgData, narc_0497_00001, messageFormat->buffer); //Dawn
    }
    else
    {
        ReadMsgDataIntoString(msgData, narc_0497_00000, messageFormat->buffer); //Lucas
    }
    SetStringAsPlaceholder(messageFormat, idx, messageFormat->buffer, NULL);
    DestroyMsgData(msgData);
}

void BufferBoxMonSpeciesName(MessageFormat *messageFormat, u32 idx, struct BoxPokemon * mon)
{
    struct MsgData * msgData = NewMsgDataFromNarc(MSGDATA_LOAD_LAZY, NARC_MSGDATA_MSG, NARC_msg_narc_0362_bin, messageFormat->heap_id);
    ReadMsgDataIntoString(msgData, GetBoxMonData(mon, MON_DATA_SPECIES, NULL), messageFormat->buffer);
    SetStringAsPlaceholder(messageFormat, idx, messageFormat->buffer, NULL);
    DestroyMsgData(msgData);
}

void BufferBoxMonSpeciesNameWithArticle(MessageFormat *messageFormat, u32 idx, struct BoxPokemon * mon)
{
    BufferSpeciesNameWithArticle(messageFormat, idx, GetBoxMonData(mon, MON_DATA_SPECIES, NULL));
}

void BufferSpeciesNameWithArticle(MessageFormat *messageFormat, u32 idx, u32 species)
{
    struct MsgData * msgData = NewMsgDataFromNarc(MSGDATA_LOAD_LAZY, NARC_MSGDATA_MSG, NARC_msg_narc_0363_bin, messageFormat->heap_id);
    ReadMsgDataIntoString(msgData, species, messageFormat->buffer);
    SetStringAsPlaceholder(messageFormat, idx, messageFormat->buffer, NULL);
    DestroyMsgData(msgData);
}

void BufferBoxMonNickname(MessageFormat *messageFormat, u32 idx, struct BoxPokemon * mon)
{
    GetBoxMonData(mon, MON_DATA_NICKNAME_3, messageFormat->buffer);
    SetStringAsPlaceholder(messageFormat, idx, messageFormat->buffer, NULL);
}

void BufferBoxMonOTName(MessageFormat *messageFormat, u32 idx, struct BoxPokemon * mon)
{
    GetBoxMonData(mon, MON_DATA_OT_NAME_2, messageFormat->buffer);
    SetStringAsPlaceholder(messageFormat, idx, messageFormat->buffer, NULL);
}

void BufferIntegerAsString(MessageFormat *messageFormat, u32 idx, s32 num, u32 ndigits, enum PrintingMode printingMode, BOOL whichCharset)
{
    String16_FormatInteger(messageFormat->buffer, num, ndigits, printingMode, whichCharset);
    SetStringAsPlaceholder(messageFormat, idx, messageFormat->buffer, NULL);
}

void BufferMoveName(MessageFormat *messageFormat, u32 idx, u32 move)
{
    struct MsgData * msgData = NewMsgDataFromNarc(MSGDATA_LOAD_LAZY, NARC_MSGDATA_MSG, NARC_msg_narc_0588_bin, messageFormat->heap_id);
    if (msgData != NULL)
    {
        ReadMsgDataIntoString(msgData, move, messageFormat->buffer);
        SetStringAsPlaceholder(messageFormat, idx, messageFormat->buffer, NULL);
        DestroyMsgData(msgData);
    }
}

void BufferRibbonNameOrDesc(MessageFormat *messageFormat, u32 idx, u32 ribbon)
{
    struct MsgData * msgData = NewMsgDataFromNarc(MSGDATA_LOAD_LAZY, NARC_MSGDATA_MSG, NARC_msg_narc_0484_bin, messageFormat->heap_id);
    if (msgData != NULL)
    {
        ReadMsgDataIntoString(msgData, ribbon, messageFormat->buffer);
        SetStringAsPlaceholder(messageFormat, idx, messageFormat->buffer, NULL);
        DestroyMsgData(msgData);
    }
}

void BufferAbilityName(MessageFormat *messageFormat, u32 idx, u32 ability)
{
    struct MsgData * msgData = NewMsgDataFromNarc(MSGDATA_LOAD_LAZY, NARC_MSGDATA_MSG, NARC_msg_narc_0552_bin, messageFormat->heap_id);
    if (msgData != NULL)
    {
        ReadMsgDataIntoString(msgData, ability, messageFormat->buffer);
        SetStringAsPlaceholder(messageFormat, idx, messageFormat->buffer, NULL);
        DestroyMsgData(msgData);
    }
}

void BufferNatureName(MessageFormat *messageFormat, u32 idx, u32 nature)
{
    struct MsgData * msgData = NewMsgDataFromNarc(MSGDATA_LOAD_LAZY, NARC_MSGDATA_MSG, NARC_msg_narc_0190_bin, messageFormat->heap_id);
    ReadMsgDataIntoString(msgData, nature, messageFormat->buffer);
    SetStringAsPlaceholder(messageFormat, idx, messageFormat->buffer, NULL);
    DestroyMsgData(msgData);
}

void BufferItemName(MessageFormat *messageFormat, u32 idx, u32 item)
{
    struct MsgData * msgData = NewMsgDataFromNarc(MSGDATA_LOAD_LAZY, NARC_MSGDATA_MSG, NARC_msg_narc_0344_bin, messageFormat->heap_id);
    if (msgData != NULL)
    {
        ReadMsgDataIntoString(msgData, item, messageFormat->buffer);
        SetStringAsPlaceholder(messageFormat, idx, messageFormat->buffer, NULL);
        DestroyMsgData(msgData);
    }
}

void BufferItemNameWithIndefArticle(MessageFormat *messageFormat, u32 idx, u32 item)
{
    struct MsgData * msgData = NewMsgDataFromNarc(MSGDATA_LOAD_LAZY, NARC_MSGDATA_MSG, NARC_msg_narc_0346_bin, messageFormat->heap_id);
    if (msgData != NULL)
    {
        ReadMsgDataIntoString(msgData, item, messageFormat->buffer);
        SetStringAsPlaceholder(messageFormat, idx, messageFormat->buffer, NULL);
        DestroyMsgData(msgData);
    }
}

void BufferItemNamePlural(MessageFormat *messageFormat, u32 idx, u32 item)
{
    struct MsgData * msgData = NewMsgDataFromNarc(MSGDATA_LOAD_LAZY, NARC_MSGDATA_MSG, NARC_msg_narc_0347_bin, messageFormat->heap_id);
    if (msgData != NULL)
    {
        ReadMsgDataIntoString(msgData, item, messageFormat->buffer);
        SetStringAsPlaceholder(messageFormat, idx, messageFormat->buffer, NULL);
        DestroyMsgData(msgData);
    }
}

void BufferPocketName(MessageFormat *messageFormat, u32 idx, u32 pocket)
{
    struct MsgData * msgData = NewMsgDataFromNarc(MSGDATA_LOAD_LAZY, NARC_MSGDATA_MSG, NARC_msg_narc_0349_bin, messageFormat->heap_id);
    if (msgData != NULL)
    {
        ReadMsgDataIntoString(msgData, pocket, messageFormat->buffer);
        SetStringAsPlaceholder(messageFormat, idx, messageFormat->buffer, NULL);
        DestroyMsgData(msgData);
    }
}

void BufferTypeName(MessageFormat *messageFormat, u32 idx, u32 type)
{
    struct MsgData * msgData = NewMsgDataFromNarc(MSGDATA_LOAD_LAZY, NARC_MSGDATA_MSG, NARC_msg_narc_0565_bin, messageFormat->heap_id);
    if (msgData != NULL)
    {
        ReadMsgDataIntoString(msgData, type, messageFormat->buffer);
        SetStringAsPlaceholder(messageFormat, idx, messageFormat->buffer, NULL);
        DestroyMsgData(msgData);
    }
}

void BufferStatName(MessageFormat *messageFormat, u32 idx, u32 stat)
{
    struct MsgData * msgData = NewMsgDataFromNarc(MSGDATA_LOAD_LAZY, NARC_MSGDATA_MSG, NARC_msg_narc_0495_bin, messageFormat->heap_id);
    if (msgData != NULL)
    {
        ReadMsgDataIntoString(msgData, stat, messageFormat->buffer);
        SetStringAsPlaceholder(messageFormat, idx, messageFormat->buffer, NULL);
        DestroyMsgData(msgData);
    }
}

void BufferStatusName(MessageFormat *messageFormat, u32 idx, u32 status)
{
    struct MsgData * msgData = NewMsgDataFromNarc(MSGDATA_LOAD_LAZY, NARC_MSGDATA_MSG, NARC_msg_narc_0205_bin, messageFormat->heap_id);
    if (msgData != NULL)
    {
        ReadMsgDataIntoString(msgData, status, messageFormat->buffer);
        SetStringAsPlaceholder(messageFormat, idx, messageFormat->buffer, NULL);
        DestroyMsgData(msgData);
    }
}

void BufferFlavorDislikeText(MessageFormat *messageFormat, u32 idx, u32 flavor)
{
    struct MsgData * msgData = NewMsgDataFromNarc(MSGDATA_LOAD_LAZY, NARC_MSGDATA_MSG, NARC_msg_narc_0548_bin, messageFormat->heap_id);
    if (msgData != NULL)
    {
        ReadMsgDataIntoString(msgData, flavor, messageFormat->buffer);
        SetStringAsPlaceholder(messageFormat, idx, messageFormat->buffer, NULL);
        DestroyMsgData(msgData);
    }
}

void BufferLandmarkName(MessageFormat *messageFormat, u32 idx, u32 landmark)
{
    struct MsgData * msgData = NewMsgDataFromNarc(MSGDATA_LOAD_LAZY, NARC_MSGDATA_MSG, NARC_msg_narc_0382_bin, messageFormat->heap_id);
    if (msgData != NULL)
    {
        ReadMsgDataIntoString(msgData, landmark, messageFormat->buffer);
        SetStringAsPlaceholder(messageFormat, idx, messageFormat->buffer, NULL);
        DestroyMsgData(msgData);
    }
}

void BufferPoketchAppName(MessageFormat *messageFormat, u32 idx, u32 app)
{
    struct MsgData * msgData = NewMsgDataFromNarc(MSGDATA_LOAD_LAZY, NARC_MSGDATA_MSG, NARC_msg_narc_0406_bin, messageFormat->heap_id);
    if (msgData != NULL)
    {
        ReadMsgDataIntoString(msgData, app, messageFormat->buffer);
        SetStringAsPlaceholder(messageFormat, idx, messageFormat->buffer, NULL);
        DestroyMsgData(msgData);
    }
}

void BufferTrainerClassName(MessageFormat *messageFormat, u32 idx, u32 trclass)
{
    struct MsgData * msgData = NewMsgDataFromNarc(MSGDATA_LOAD_LAZY, NARC_MSGDATA_MSG, NARC_msg_narc_0560_bin, messageFormat->heap_id);
    if (msgData != NULL)
    {
        ReadMsgDataIntoString(msgData, trclass, messageFormat->buffer);
        SetStringAsPlaceholder(messageFormat, idx, messageFormat->buffer, NULL);
        DestroyMsgData(msgData);
    }
}

void BufferTrainerClassNameWithArticle(MessageFormat *messageFormat, u32 idx, u32 trclass)
{
    struct MsgData * msgData = NewMsgDataFromNarc(MSGDATA_LOAD_LAZY, NARC_MSGDATA_MSG, NARC_msg_narc_0561_bin, messageFormat->heap_id);
    if (msgData != NULL)
    {
        ReadMsgDataIntoString(msgData, trclass, messageFormat->buffer);
        SetStringAsPlaceholder(messageFormat, idx, messageFormat->buffer, NULL);
        DestroyMsgData(msgData);
    }
}

void BufferTrainerClassNameFromDataStruct(MessageFormat *messageFormat, u32 idx, struct TrainerDataLoaded * tr)
{
    struct MsgData * msgData = NewMsgDataFromNarc(MSGDATA_LOAD_LAZY, NARC_MSGDATA_MSG, NARC_msg_narc_0560_bin, messageFormat->heap_id);
    if (msgData != NULL)
    {
        ReadMsgDataIntoString(msgData, tr->data.trainerClass, messageFormat->buffer);
        SetStringAsPlaceholder(messageFormat, idx, messageFormat->buffer, NULL);
        DestroyMsgData(msgData);
    }
}

void BufferTrainerName(MessageFormat *messageFormat, u32 idx, u32 msgno)
{
    struct MsgData * msgData = NewMsgDataFromNarc(MSGDATA_LOAD_LAZY, NARC_MSGDATA_MSG, NARC_msg_narc_0559_bin, messageFormat->heap_id);
    if (msgData != NULL)
    {
        ReadMsgDataIntoString(msgData, msgno, messageFormat->buffer);
        SetStringAsPlaceholder(messageFormat, idx, messageFormat->buffer, NULL);
        DestroyMsgData(msgData);
    }
}

void BufferTrainerNameFromDataStruct(MessageFormat *messageFormat, u32 idx, struct TrainerDataLoaded * trdata)
{
    CopyU16ArrayToString(messageFormat->buffer, trdata->name);
    SetStringAsPlaceholder(messageFormat, idx, messageFormat->buffer, NULL);
}

void BufferUndergroundItemName(MessageFormat *messageFormat, u32 idx, u32 item)
{
    struct MsgData * msgData = NewMsgDataFromNarc(MSGDATA_LOAD_LAZY, NARC_MSGDATA_MSG, NARC_msg_narc_0569_bin, messageFormat->heap_id);
    if (msgData != NULL)
    {
        ReadMsgDataIntoString(msgData, item, messageFormat->buffer);
        SetStringAsPlaceholder(messageFormat, idx, messageFormat->buffer, NULL);
        DestroyMsgData(msgData);
    }
}

void BufferUndergroundItemNameWithArticle(MessageFormat *messageFormat, u32 idx, u32 item)
{
    struct MsgData * msgData = NewMsgDataFromNarc(MSGDATA_LOAD_LAZY, NARC_MSGDATA_MSG, NARC_msg_narc_0570_bin, messageFormat->heap_id);
    if (msgData != NULL)
    {
        ReadMsgDataIntoString(msgData, item, messageFormat->buffer);
        SetStringAsPlaceholder(messageFormat, idx, messageFormat->buffer, NULL);
        DestroyMsgData(msgData);
    }
}

void BufferUndergroundTrapName(MessageFormat *messageFormat, u32 idx, u32 trap)
{
    struct MsgData * msgData = NewMsgDataFromNarc(MSGDATA_LOAD_LAZY, NARC_MSGDATA_MSG, NARC_msg_narc_0571_bin, messageFormat->heap_id);
    if (msgData != NULL)
    {
        ReadMsgDataIntoString(msgData, trap, messageFormat->buffer);
        SetStringAsPlaceholder(messageFormat, idx, messageFormat->buffer, NULL);
        DestroyMsgData(msgData);
    }
}

void BufferUndergroundTrapNameWithArticle(MessageFormat *messageFormat, u32 idx, u32 trap)
{
    struct MsgData * msgData = NewMsgDataFromNarc(MSGDATA_LOAD_LAZY, NARC_MSGDATA_MSG, NARC_msg_narc_0572_bin, messageFormat->heap_id);
    if (msgData != NULL)
    {
        ReadMsgDataIntoString(msgData, trap, messageFormat->buffer);
        SetStringAsPlaceholder(messageFormat, idx, messageFormat->buffer, NULL);
        DestroyMsgData(msgData);
    }
}

void BufferContestJudgeName(MessageFormat *messageFormat, u32 idx, u32 judge)
{
    struct MsgData * msgData = NewMsgDataFromNarc(MSGDATA_LOAD_LAZY, NARC_MSGDATA_MSG, NARC_msg_narc_0194_bin, messageFormat->heap_id);
    if (msgData != NULL)
    {
        ReadMsgDataIntoString(msgData, judge, messageFormat->buffer);
        SetStringAsPlaceholder(messageFormat, idx, messageFormat->buffer, NULL);
        DestroyMsgData(msgData);
    }
}

void BufferContestMessage(MessageFormat *messageFormat, u32 idx, u32 msg)
{
    struct MsgData * msgData = NewMsgDataFromNarc(MSGDATA_LOAD_LAZY, NARC_MSGDATA_MSG, NARC_msg_narc_0191_bin, messageFormat->heap_id);
    if (msgData != NULL)
    {
        ReadMsgDataIntoString(msgData, msg, messageFormat->buffer);
        SetStringAsPlaceholder(messageFormat, idx, messageFormat->buffer, NULL);
        DestroyMsgData(msgData);
    }
}

void BufferContestMessage2(MessageFormat *messageFormat, u32 idx, u32 msg)
{
    struct MsgData * msgData = NewMsgDataFromNarc(MSGDATA_LOAD_LAZY, NARC_MSGDATA_MSG, NARC_msg_narc_0191_bin, messageFormat->heap_id);
    if (msgData != NULL)
    {
        ReadMsgDataIntoString(msgData, msg, messageFormat->buffer);
        SetStringAsPlaceholder(messageFormat, idx, messageFormat->buffer, NULL);
        DestroyMsgData(msgData);
    }
}

void BufferInterviewQuestion(MessageFormat *messageFormat, u32 idx, u32 question)
{
    struct MsgData * msgData = NewMsgDataFromNarc(MSGDATA_LOAD_LAZY, NARC_MSGDATA_MSG, NARC_msg_narc_0574_bin, messageFormat->heap_id);
    if (msgData != NULL)
    {
        ReadMsgDataIntoString(msgData, question, messageFormat->buffer);
        SetStringAsPlaceholder(messageFormat, idx, messageFormat->buffer, NULL);
        DestroyMsgData(msgData);
    }
}

void BufferInterviewAnswer(MessageFormat *messageFormat, u32 idx, u32 answer)
{
    struct MsgData * msgData = NewMsgDataFromNarc(MSGDATA_LOAD_LAZY, NARC_MSGDATA_MSG, NARC_msg_narc_0573_bin, messageFormat->heap_id);
    if (msgData != NULL)
    {
        ReadMsgDataIntoString(msgData, answer, messageFormat->buffer);
        SetStringAsPlaceholder(messageFormat, idx, messageFormat->buffer, NULL);
        DestroyMsgData(msgData);
    }
}

void BufferDecorationName(MessageFormat *messageFormat, u32 idx, u32 decor)
{
    struct MsgData * msgData = NewMsgDataFromNarc(MSGDATA_LOAD_LAZY, NARC_MSGDATA_MSG, NARC_msg_narc_0567_bin, messageFormat->heap_id);
    if (msgData != NULL)
    {
        ReadMsgDataIntoString(msgData, decor, messageFormat->buffer);
        SetStringAsPlaceholder(messageFormat, idx, messageFormat->buffer, NULL);
        DestroyMsgData(msgData);
    }
}

void BufferDecorationNameWithArticle(MessageFormat *messageFormat, u32 idx, u32 decor)
{
    struct MsgData * msgData = NewMsgDataFromNarc(MSGDATA_LOAD_LAZY, NARC_MSGDATA_MSG, NARC_msg_narc_0568_bin, messageFormat->heap_id);
    if (msgData != NULL)
    {
        ReadMsgDataIntoString(msgData, decor, messageFormat->buffer);
        SetStringAsPlaceholder(messageFormat, idx, messageFormat->buffer, NULL);
        DestroyMsgData(msgData);
    }
}

void BufferGenderSymbol(MessageFormat *messageFormat, u32 idx, u32 gender)
{
    struct MsgData * msgData = NewMsgDataFromNarc(MSGDATA_LOAD_LAZY, NARC_MSGDATA_MSG, NARC_msg_narc_0199_bin, messageFormat->heap_id);
    switch (gender)
    {
    case 0:
        ReadMsgDataIntoString(msgData, narc_0199_00068, messageFormat->buffer); // ♂
        break;
    case 1:
        ReadMsgDataIntoString(msgData, narc_0199_00069, messageFormat->buffer); // ♀
        break;
    default:
        StringSetEmpty(messageFormat->buffer);
        break;
    }
    SetStringAsPlaceholder(messageFormat, idx, messageFormat->buffer, NULL);
    DestroyMsgData(msgData);
}

void BufferBoxName(MessageFormat *messageFormat, u32 idx, struct PCStorage * pc, s32 boxno)
{
    PCStorage_GetBoxName(pc, boxno, messageFormat->buffer);
    SetStringAsPlaceholder(messageFormat, idx, messageFormat->buffer, NULL);
}

void BufferGymName(MessageFormat *messageFormat, u32 idx, u32 gym)
{
    struct MsgData * msgData = NewMsgDataFromNarc(MSGDATA_LOAD_LAZY, NARC_MSGDATA_MSG, NARC_msg_narc_0331_bin, messageFormat->heap_id);
    if (msgData != NULL)
    {
        ReadMsgDataIntoString(msgData, gym, messageFormat->buffer);
        SetStringAsPlaceholder(messageFormat, idx, messageFormat->buffer, NULL);
        DestroyMsgData(msgData);
    }
}

void BufferTimeOfDayName(MessageFormat *messageFormat, u32 idx, u32 time)
{
    struct MsgData * msgData = NewMsgDataFromNarc(MSGDATA_LOAD_LAZY, NARC_MSGDATA_MSG, NARC_msg_narc_0550_bin, messageFormat->heap_id);
    if (msgData != NULL)
    {
        ReadMsgDataIntoString(msgData, time, messageFormat->buffer);
        SetStringAsPlaceholder(messageFormat, idx, messageFormat->buffer, NULL);
        DestroyMsgData(msgData);
    }
}

void BufferCountryName(MessageFormat *messageFormat, u32 idx, u32 country)
{
    struct MsgData * msgData = NewMsgDataFromNarc(MSGDATA_LOAD_LAZY, NARC_MSGDATA_MSG, NARC_msg_narc_0612_bin, messageFormat->heap_id);
    if (msgData != NULL)
    {
        ReadMsgDataIntoString(msgData, country, messageFormat->buffer);
        SetStringAsPlaceholder(messageFormat, idx, messageFormat->buffer, NULL);
        DestroyMsgData(msgData);
    }
}

void BufferCityName(MessageFormat *messageFormat, u32 idx, u32 countryId, u32 cityId)
{
    u32 msgBank = GetCityNamesMsgdataIdByCountry(countryId);
    if (msgBank != 0 && cityId != 0)
    {
        struct MsgData *msgData = NewMsgDataFromNarc(MSGDATA_LOAD_LAZY, NARC_MSGDATA_MSG, (s32)msgBank, messageFormat->heap_id);
        if (msgData != NULL)
        {
            ReadMsgDataIntoString(msgData, cityId, messageFormat->buffer);
            SetStringAsPlaceholder(messageFormat, idx, messageFormat->buffer, NULL);
            DestroyMsgData(msgData);
        }
    }
}

void BufferECWord(MessageFormat *messageFormat, u32 idx, u32 ecWordIdx)
{
    GetECWordIntoStringByIndex(ecWordIdx, messageFormat->buffer);
    SetStringAsPlaceholder(messageFormat, idx, messageFormat->buffer, NULL);
}

void BufferSealName(MessageFormat *messageFormat, u32 idx, u32 seal)
{
    struct MsgData * msgData = NewMsgDataFromNarc(MSGDATA_LOAD_LAZY, NARC_MSGDATA_MSG, NARC_msg_narc_0010_bin, messageFormat->heap_id);
    if (msgData != NULL)
    {
        ReadMsgDataIntoString(msgData, seal, messageFormat->buffer);
        SetStringAsPlaceholder(messageFormat, idx, messageFormat->buffer, NULL);
        DestroyMsgData(msgData);
    }
}

void BufferSealNamePlural(MessageFormat *messageFormat, u32 idx, u32 seal)
{
    struct MsgData * msgData = NewMsgDataFromNarc(MSGDATA_LOAD_LAZY, NARC_MSGDATA_MSG, NARC_msg_narc_0011_bin, messageFormat->heap_id);
    if (msgData != NULL)
    {
        ReadMsgDataIntoString(msgData, seal, messageFormat->buffer);
        SetStringAsPlaceholder(messageFormat, idx, messageFormat->buffer, NULL);
        DestroyMsgData(msgData);
    }
}

void BufferLocationName(MessageFormat *messageFormat, u32 idx, u16 location)
{
    u32 r6 = (u32)FUN_02015CC0(location);
    u32 r4 = (u32)FUN_02015CE0(location);
    struct MsgData * msgData = NewMsgDataFromNarc(MSGDATA_LOAD_LAZY, NARC_MSGDATA_MSG, UNK_020ECE64[r6], messageFormat->heap_id);
    if (msgData != NULL)
    {
        if (r4 < MsgDataGetCount(msgData))
        {
            ReadMsgDataIntoString(msgData, r4, messageFormat->buffer);
            SetStringAsPlaceholder(messageFormat, idx, messageFormat->buffer, NULL);
            DestroyMsgData(msgData);
            return;
        }
        // Location is invalid.
        // Fallback: Mystery Zone
        DestroyMsgData(msgData);
        msgData = NewMsgDataFromNarc(MSGDATA_LOAD_LAZY, NARC_MSGDATA_MSG, NARC_msg_narc_0382_bin, messageFormat->heap_id);
        if (msgData != NULL)
        {
            ReadMsgDataIntoString(msgData, narc_0382_00000, messageFormat->buffer); // Mystery Zone
            SetStringAsPlaceholder(messageFormat, idx, messageFormat->buffer, NULL);
            DestroyMsgData(msgData);
        }
    }
}

void BufferPoffinName(MessageFormat *messageFormat, u32 idx, u32 poffin)
{
    struct MsgData * msgData = NewMsgDataFromNarc(MSGDATA_LOAD_LAZY, NARC_MSGDATA_MSG, NARC_msg_narc_0414_bin, messageFormat->heap_id);
    if (msgData != NULL)
    {
        ReadMsgDataIntoString(msgData, poffin, messageFormat->buffer);
        SetStringAsPlaceholder(messageFormat, idx, messageFormat->buffer, NULL);
        DestroyMsgData(msgData);
    }
}

void BufferFashionName(MessageFormat *messageFormat, u32 idx, u32 fashion)
{
    struct MsgData * msgData = NewMsgDataFromNarc(MSGDATA_LOAD_LAZY, NARC_MSGDATA_MSG, NARC_msg_narc_0338_bin, messageFormat->heap_id);
    if (msgData != NULL)
    {
        ReadMsgDataIntoString(msgData, fashion, messageFormat->buffer);
        SetStringAsPlaceholder(messageFormat, idx, messageFormat->buffer, NULL);
        DestroyMsgData(msgData);
    }
}

void BufferFashionNameWithArticle(MessageFormat *messageFormat, u32 idx, u32 fashion)
{
    struct MsgData * msgData = NewMsgDataFromNarc(MSGDATA_LOAD_LAZY, NARC_MSGDATA_MSG, NARC_msg_narc_0339_bin, messageFormat->heap_id);
    if (msgData != NULL)
    {
        ReadMsgDataIntoString(msgData, fashion, messageFormat->buffer);
        SetStringAsPlaceholder(messageFormat, idx, messageFormat->buffer, NULL);
        DestroyMsgData(msgData);
    }
}

void BufferContestBackgroundName(MessageFormat *messageFormat, u32 idx, u32 bg)
{
    struct MsgData * msgData = NewMsgDataFromNarc(MSGDATA_LOAD_LAZY, NARC_MSGDATA_MSG, NARC_msg_narc_0340_bin, messageFormat->heap_id);
    if (msgData != NULL)
    {
        ReadMsgDataIntoString(msgData, bg, messageFormat->buffer);
        SetStringAsPlaceholder(messageFormat, idx, messageFormat->buffer, NULL);
        DestroyMsgData(msgData);
    }
}

void BufferGroupName(MessageFormat *messageFormat, struct SaveData * save, u32 r5, u32 idx, u32 sp28)
{
    void * r6 = FUN_0202881C(save);
    u8 sp10 = FUN_020287F8(r6, r5);
    u8 r7 = FUN_02028804(r6, r5);
    struct String * r4 = String_New(64, 4);
    CopyU16ArrayToString(r4, FUN_020287A8(r6, r5, sp28));
    BufferString(messageFormat, idx, r4, sp10, 1, r7);
    String_Delete(r4);
}

void BufferMonthNameAbbr(MessageFormat *messageFormat, u32 idx, u32 month)
{
    struct MsgData * msgData = NewMsgDataFromNarc(MSGDATA_LOAD_LAZY, NARC_MSGDATA_MSG, NARC_msg_narc_0364_bin, messageFormat->heap_id);
    if (msgData != NULL)
    {
        if (month < 1 || month > 12)
            month = 1;
        ReadMsgDataIntoString(msgData, month - 1, messageFormat->buffer);
        SetStringAsPlaceholder(messageFormat, idx, messageFormat->buffer, NULL);
        DestroyMsgData(msgData);
    }
}

void MessageFormat_UpperFirstChar(MessageFormat *messageFormat, u32 idx)
{
    StrUpperFirstChar(messageFormat->fields[idx].msg);
}

void StringExpandPlaceholders(MessageFormat *messageFormat, struct String * dest, struct String * src)
{
    const u16 * cstr = String_c_str(src);
    StringSetEmpty(dest);
    while (*cstr != EOS)
    {
        if (*cstr == EXT_CTRL_CODE_BEGIN)
        {
            if (MsgArray_ControlCodeIsStrVar(cstr))
            {
                u32 idx = MsgArray_ControlCodeGetField(cstr, 0);
                GF_ASSERT(idx < messageFormat->count);
                StringCat_HandleTrainerName(dest, messageFormat->fields[idx].msg);
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

void MessageFormat_ResetBuffers(MessageFormat *messageFormat)
{
    for (int i = 0; i < messageFormat->count; i++)
        StringSetEmpty(messageFormat->fields[i].msg);
}

struct UnkStruct_0200B870 * MessagePrinter_New(u32 color1, u32 color2, u32 color3, u32 heap_id)
{
    struct UnkStruct_0200B870 * sp8 = AllocFromHeap(heap_id, sizeof(struct UnkStruct_0200B870));
    if (sp8 != NULL)
    {
        sp8->unk_0 = GfGfxLoader_GetCharData(NARC_GRAPHIC_FONT, NARC_font_narc_0004_NCGR_lz, 1, &sp8->unk_4, heap_id);
        int i;
        u8 * ptr = sp8->unk_4->unk_14;
        for (i = 0; i < sp8->unk_4->unk_10; i++)
        {
            switch (ptr[i])
            {
            case 0x00:
                ptr[i] = (u8)((color3 << 4) | color3);
                break;
            case 0x01:
                ptr[i] = (u8)((color3 << 4) | color1);
                break;
            case 0x02:
                ptr[i] = (u8)((color3 << 4) | color2);
                break;
            case 0x10:
                ptr[i] = (u8)((color1 << 4) | color3);
                break;
            case 0x11:
                ptr[i] = (u8)((color1 << 4) | color1);
                break;
            case 0x12:
                ptr[i] = (u8)((color1 << 4) | color2);
                break;
            case 0x20:
                ptr[i] = (u8)((color2 << 4) | color3);
                break;
            case 0x21:
                ptr[i] = (u8)((color2 << 4) | color1);
                break;
            case 0x22:
                ptr[i] = (u8)((color2 << 4) | color2);
                break;
            }
        }
        sp8->unk_28 = color3;
    }
    return sp8;
}

void MessagePrinter_Delete(struct UnkStruct_0200B870 * a0)
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

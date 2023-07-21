#include "global.h"
#include "msgdata.h"
#include "heap.h"
#include "save.h"
#include "math_util.h"
#include "easy_chat.h"
#include "msgdata/msg.naix"
#include "constants/abilities.h"
#include "constants/easy_chat.h"
#include "constants/moves.h"

#include "msgdata/msg/narc_0390.h"

static const u8 sLanguageToGreetingMap[6][2] = {
    { LANGUAGE_JAPANESE, narc_0390_konnichiwa },
    { LANGUAGE_ENGLISH,  narc_0390_hello },
    { LANGUAGE_FRENCH,   narc_0390_bonjour },
    { LANGUAGE_ITALIAN,  narc_0390_ciao },
    { LANGUAGE_GERMAN,   narc_0390_hallo },
    { LANGUAGE_SPANISH,  narc_0390_hola },
};

static const u16 sNarcMsgBanks[EC_GROUP_MAX] = {
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
    NARC_msg_narc_0394_bin, // Union
};

static const u16 sNarcMsgCounts[EC_GROUP_MAX] = {
    EC_WORDS_POKEMON_COUNT,
    EC_WORDS_MOVE_COUNT,
    EC_WORDS_TYPE_COUNT,
    EC_WORDS_ABILITY_COUNT,
    EC_WORDS_TRAINER_COUNT,
    EC_WORDS_PEOPLE_COUNT,
    EC_WORDS_GREETINGS_COUNT,
    EC_WORDS_LIFESTYLE_COUNT,
    EC_WORDS_FEELINGS_COUNT,
    EC_WORDS_TOUGH_WORDS_COUNT,
    EC_WORDS_UNION_COUNT,
};

static const ecword_t sEasyChatHey[] = {EC_WORD_GREETINGS_HEY, EC_WORD_GREETINGS_HEY_2};
static const ecword_t sEasyChatHuh_[] = {EC_WORD_GREETINGS_HUH_, EC_WORD_GREETINGS_HUH__2};
static const ecword_t sEasyChatI[] = {EC_WORD_PEOPLE_I, EC_WORD_PEOPLE_I_2, EC_WORD_PEOPLE_I_3, EC_WORD_PEOPLE_I_4};
static const ecword_t sEasyChatKids[] = {EC_WORD_PEOPLE_KIDS, EC_WORD_PEOPLE_KIDS_2};
static const ecword_t sEasyChatNoWay[] = {EC_WORD_GREETINGS_NO_WAY, EC_WORD_FEELINGS_NO_WAY};
static const ecword_t sEasyChatYou[] = {EC_WORD_PEOPLE_YOU, EC_WORD_PEOPLE_YOU_2};
static const ecword_t sEasyChatAnticipation[] = {EC_WORD_ABILITY(ABILITY_ANTICIPATION), EC_WORD_FEELINGS_ANTICIPATION};
static const ecword_t sEasyChatSimple[] = {EC_WORD_ABILITY(ABILITY_SIMPLE), EC_WORD_FEELINGS_SIMPLE};
static const ecword_t sEasyChatWelcome[] = {EC_WORD_GREETINGS_WELCOME, EC_WORD_GREETINGS_WELCOME_2};
static const ecword_t sEasyChatWow[] = {EC_WORD_GREETINGS_WOW, EC_WORD_GREETINGS_WOW_2};
static const ecword_t sEasyChatPsychic[] = {EC_WORD_MOVE(MOVE_PSYCHIC), EC_WORD_TYPE(TYPE_PSYCHIC)};
static const ecword_t sEasyChatOk[] = {EC_WORD_GREETINGS_OK, EC_WORD_GREETINGS_OK_2};

typedef struct ECIdenticalPhrases {
    const ecword_t *data;
    s32 count;
} ECIdenticalPhrases;

static const ECIdenticalPhrases sIdenticalPhrases[12] = {
    { sEasyChatAnticipation, NELEMS(sEasyChatAnticipation) },
    { sEasyChatHey, NELEMS(sEasyChatHey) },
    { sEasyChatHuh_, NELEMS(sEasyChatHuh_) },
    { sEasyChatI, NELEMS(sEasyChatI) },
    { sEasyChatKids, NELEMS(sEasyChatKids) },
    { sEasyChatNoWay, NELEMS(sEasyChatNoWay) },
    { sEasyChatOk, NELEMS(sEasyChatOk) },
    { sEasyChatPsychic, NELEMS(sEasyChatPsychic) },
    { sEasyChatSimple, NELEMS(sEasyChatSimple) },
    { sEasyChatWelcome, NELEMS(sEasyChatWelcome) },
    { sEasyChatWow, NELEMS(sEasyChatWow) },
    { sEasyChatYou, NELEMS(sEasyChatYou) },
};

EasyChatManager *EasyChatManager_New(HeapID heapId) {
    EasyChatManager *ret = AllocFromHeap(heapId, sizeof(EasyChatManager));

    for (s32 i = 0; i < EC_GROUP_MAX; i++) {
        ret->heapId = heapId; // inadvertently inside the loop
        ret->msgData[i] = NewMsgDataFromNarc(MSGDATA_LOAD_LAZY, NARC_MSGDATA_MSG, sNarcMsgBanks[i], heapId);
    }
    return ret;
}

void EasyChatManager_Delete(EasyChatManager *easyChatManager) {
    for (s32 i = 0; i < EC_GROUP_MAX; i++) {
        DestroyMsgData(easyChatManager->msgData[i]);
    }
    FreeToHeap(easyChatManager);
}

void EasyChatManager_ReadWordIntoString(struct EasyChatManager * unk, u16 wordIdx, struct String * str)
{
    s32 msgBank;
    s32 msgNo;
    GetCategoryAndMsgNoByECWordIdx(wordIdx, &msgBank, &msgNo);
    ReadMsgDataIntoString(unk->msgData[msgBank], (u32)msgNo, str);
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
        if (sLanguageToGreetingMap[i][0] == GAME_LANGUAGE)
        {
            sub_02013C18(unk, sLanguageToGreetingMap[i][1]);
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

    for (r3 = 0; r3 < NELEMS(sIdenticalPhrases); r3++)
    {
        for (r4 = 0; r4 < sIdenticalPhrases[r3].count; r4++)
        {
            if (a0 == sIdenticalPhrases[r3].data[r4])
                return sIdenticalPhrases[r3].count - 1;
        }
    }
    return 0;
}

u16 sub_02013C6C(u16 a0, s32 a1)
{
    s32 r7;
    s32 r2;
    s32 r0;

    for (r7 = 0; r7 < NELEMS(sIdenticalPhrases); r7++)
    {
        for (r2 = 0; r2 < sIdenticalPhrases[r7].count; r2++)
        {
            if (a0 == sIdenticalPhrases[r7].data[r2])
            {
                // ERROR: Infinite loop when reached
                for (r0 = 0; /*r0 <*/ sIdenticalPhrases[r7].count; r0++)
                {
                    if (a1 == 0)
                        return sIdenticalPhrases[r7].data[r0];
                    a1--;
                }
                GF_ASSERT(0);
                return 0xFFFF;
            }
        }
    }
    return a0;
}

#include "global.h"
#include "mail.h"
#include "heap.h"
#include "string_util.h"
#include "MI_memory.h"
#include "save.h"
#include "party.h"
#include "player_data.h"

extern u32 sub_0206B6C8(struct Pokemon * pokemon);
extern u16 sub_0206B7BC(u16 species, u32 form, BOOL is_egg);

void Mail_Init(struct Mail * mail)
{
    s32 i;
    mail->author_otId = 0;
    mail->author_gender = 0;
    mail->author_language = (u8)gGameLanguage;
    mail->author_version = (u8)gGameVersion;
    mail->mail_type = 0xFF;
    StringFillEOS(mail->author_name, 8);
    for (i = 0; i < 3; i++)
    {
        mail->unk_18[i].raw = 0xFFFF;
    }
    for (i = 0; i < 3; i++)
    {
        MailMsg_Init(&mail->unk_20[i]);
    }
}

BOOL Mail_TypeIsValid(struct Mail * mail)
{
    return mail->mail_type <= 11;
}

struct Mail * Mail_New(HeapID heapId)
{
    struct Mail * ret = (struct Mail *)AllocFromHeapAtEnd(heapId, sizeof(struct Mail));
    Mail_Init(ret);
    return ret;
}

void Mail_Copy(const struct Mail * src, struct Mail * dest)
{
    MI_CpuCopy8(src, dest, sizeof(struct Mail));
}

void Mail_SetNewMessageDetails(struct Mail * mail, u8 type, u8 monIdx, struct SaveData * save)
{
    u32 sp10;
    u32 form;
    BOOL is_egg;
    u16 species;
    struct Party * party;
    PlayerProfile * profile;
    struct Pokemon * pokemon;
    u16 r7;
    u8 i;

    Mail_Init(mail);
    mail->mail_type = type;
    party = SaveArray_Party_Get(save);
    profile = Save_PlayerData_GetProfileAddr(save);

    CopyU16StringArray(mail->author_name, PlayerProfile_GetNamePtr(profile));
    mail->author_gender = (u8)PlayerProfile_GetTrainerGender(profile);
    mail->author_otId = PlayerProfile_GetTrainerID(profile);
    for (i = 0; monIdx < GetPartyCount(party); monIdx++)
    {
        union MailPatternData * ptr;
        pokemon = GetPartyMonByIndex(party, monIdx);
        species = (u16)GetMonData(pokemon, MON_DATA_SPECIES, NULL);
        is_egg = (BOOL)GetMonData(pokemon, MON_DATA_IS_EGG, NULL);
        form = GetMonData(pokemon, MON_DATA_FORM, NULL);
        sp10 = sub_0206B6C8(pokemon);
        r7 = sub_0206B7BC(species, form, is_egg);
        ptr = &mail->unk_18[i];
        ptr->bits.unk_0 = sp10;
        i++;
        ptr->bits.unk_C = r7;
        if (i >= 3)
            break;
    }
}

u32 Mail_GetOTID(struct Mail * mail)
{
    return mail->author_otId;
}

u16 * Mail_GetAuthorNamePtr(struct Mail * mail)
{
    return mail->author_name;
}

u8 Mail_GetAuthorGender(struct Mail * mail)
{
    return mail->author_gender;
}

u8 Mail_GetType(struct Mail * mail)
{
    return mail->mail_type;
}

void Mail_SetType(struct Mail * mail, u8 type)
{
    if (type < 12)
        mail->mail_type = type;
}

u8 Mail_GetLanguage(struct Mail * mail)
{
    return mail->author_language;
}

u8 Mail_GetVersion(struct Mail * mail)
{
    return mail->author_version;
}

u16 Mail_GetAttrFromUnk18Array(struct Mail * mail, u32 idx, u32 attr)
{
    if (idx < 3)
    {
        switch (attr)
        {
        case 0:
            return mail->unk_18[idx].bits.unk_0;
        case 1:
            return mail->unk_18[idx].bits.unk_C;
        case 2:
        default:
            return mail->unk_18[idx].raw;
        }
    }
    return 0;
}

struct MailMessage * Mail_GetUnk20Array(struct Mail * mail, u32 idx)
{
    if (idx < 3)
        return &mail->unk_20[idx];
    else
        return &mail->unk_20[0];
}

void Mail_CopyToUnk20Array(struct Mail * mail, const struct MailMessage * src, u32 idx)
{
    if (idx < 3)
        MailMsg_Copy(&mail->unk_20[idx], src);
}

struct Mail * Save_Mailbox_Get(struct SaveData * save)
{
    return (struct Mail *)SaveArray_Get(save, 15);
}

u32 Save_Mailbox_sizeof(void)
{
    return 20 * sizeof(struct Mail);
}

void Save_Mailbox_Init(struct Mail * mail)
{
    s32 i;
    for (i = 0; i < 20; i++)
    {
        Mail_Init(&mail[i]);
    }
}

s32 Mailbox_GetFirstEmptySlotIdx(struct Mail * mail, BOOL r1)
{
    switch (r1)
    {
    case 0:
        return MailArray_GetFirstEmptySlotIdx(mail, 20);
    default:
        return -1;
    }
}

void Mailbox_DeleteSlotI(struct Mail * mail, BOOL r1, s32 idx)
{
    mail = Mailbox_GetPtrToSlotI(mail, r1, idx);
    if (mail != NULL)
        Mail_Init(mail);
}

void Mailbox_CopyMailToSlotI(struct Mail * mail, BOOL r1, s32 idx, const struct Mail * src)
{
    mail = Mailbox_GetPtrToSlotI(mail, r1, idx);
    if (mail != NULL)
        Mail_Copy(src, mail);
}

s32 Mailbox_CountMessages(struct Mail * mail, BOOL r1)
{
    switch (r1)
    {
    case 0:
        return MailArray_CountMessages(mail, 20);
    default:
        return 0;
    }
}

struct Mail * Mailbox_AllocAndFetchMailI(struct Mail * mail, BOOL r1, s32 idx, HeapID heapId)
{
    struct Mail * ret;
    mail = Mailbox_GetPtrToSlotI(mail, r1, idx);
    ret = Mail_New(heapId);
    if (mail != NULL)
        Mail_Copy(mail, ret);
    return ret;
}

void Mailbox_FetchMailIToBuffer(struct Mail * mail, BOOL r1, s32 idx, struct Mail * dest)
{
    mail = Mailbox_GetPtrToSlotI(mail, r1, idx);
    if (mail == NULL)
        Mail_Init(dest);
    else
        Mail_Copy(mail, dest);
}

s32 MailArray_GetFirstEmptySlotIdx(struct Mail * mail, s32 count)
{
    s32 i;
    for (i = 0; i < count; i++)
    {
        if (!Mail_TypeIsValid(&mail[i]))
            return i;
    }
    return -1;
}

s32 MailArray_CountMessages(struct Mail * mail, s32 count)
{
    s32 ret = 0;
    s32 i;
    for (i = 0; i < count; i++)
    {
        if (Mail_TypeIsValid(&mail[i]))
            ret++;
    }
    return ret;
}

struct Mail * Mailbox_GetPtrToSlotI(struct Mail * mail, BOOL r1, s32 idx)
{
    struct Mail * ret = NULL;
    switch (r1)
    {
    case 0:
        if (idx < 20)
            ret = &mail[idx];
        break;
    }
    return ret;
}

#include "global.h"
#include "mail.h"
#include "heap.h"
#include "string_util.h"
#include "MI_memory.h"
#include "save_block_2.h"
#include "party.h"
#include "player_data.h"

#pragma thumb on

extern u32 FUN_0206B6C8(struct Pokemon * pokemon);
extern u16 FUN_0206B7BC(u16 species, u32 forme, BOOL is_egg);

void Mail_init(struct Mail * mail)
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
        MailMsg_init(&mail->unk_20[i]);
    }
}

BOOL Mail_TypeIsValid(struct Mail * mail)
{
    return mail->mail_type <= 11;
}

struct Mail * Mail_new(u32 heap_id)
{
    struct Mail * ret = (struct Mail *)AllocFromHeapAtEnd(heap_id, sizeof(struct Mail));
    Mail_init(ret);
    return ret;
}

void Mail_copy(const struct Mail * src, struct Mail * dest)
{
    MI_CpuCopy8(src, dest, sizeof(struct Mail));
}

void Mail_SetNewMessageDetails(struct Mail * mail, u8 type, u8 monIdx, struct SaveBlock2 * sav2)
{
    u32 sp10;
    u32 forme;
    BOOL is_egg;
    u16 species;
    struct PlayerParty * party;
    struct PlayerData * profile;
    struct Pokemon * pokemon;
    u16 r7;
    u8 i;

    Mail_init(mail);
    mail->mail_type = type;
    party = SavArray_PlayerParty_get(sav2);
    profile = Sav2_PlayerData_GetProfileAddr(sav2);

    CopyU16StringArray(mail->author_name, PlayerProfile_GetNamePtr(profile));
    mail->author_gender = (u8)PlayerProfile_GetTrainerGender(profile);
    mail->author_otId = PlayerProfile_GetTrainerID(profile);
    for (i = 0; monIdx < GetPartyCount(party); monIdx++)
    {
        union MailPatternData * ptr;
        pokemon = GetPartyMonByIndex(party, monIdx);
        species = (u16)GetMonData(pokemon, MON_DATA_SPECIES, NULL);
        is_egg = (BOOL)GetMonData(pokemon, MON_DATA_IS_EGG, NULL);
        forme = GetMonData(pokemon, MON_DATA_FORME, NULL);
        sp10 = FUN_0206B6C8(pokemon);
        r7 = FUN_0206B7BC(species, forme, is_egg);
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
        MailMsg_copy(&mail->unk_20[idx], src);
}

struct Mail * Sav2_Mailbox_get(struct SaveBlock2 * sav2)
{
    return (struct Mail *)SavArray_get(sav2, 15);
}

u32 Sav2_Mailbox_sizeof(void)
{
    return 20 * sizeof(struct Mail);
}

void Sav2_Mailbox_init(struct Mail * mail)
{
    s32 i;
    for (i = 0; i < 20; i++)
    {
        Mail_init(&mail[i]);
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
        Mail_init(mail);
}

void Mailbox_CopyMailToSlotI(struct Mail * mail, BOOL r1, s32 idx, const struct Mail * src)
{
    mail = Mailbox_GetPtrToSlotI(mail, r1, idx);
    if (mail != NULL)
        Mail_copy(src, mail);
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

struct Mail * Mailbox_AllocAndFetchMailI(struct Mail * mail, BOOL r1, s32 idx, u32 heap_id)
{
    struct Mail * ret;
    mail = Mailbox_GetPtrToSlotI(mail, r1, idx);
    ret = Mail_new(heap_id);
    if (mail != NULL)
        Mail_copy(mail, ret);
    return ret;
}

void Mailbox_FetchMailIToBuffer(struct Mail * mail, BOOL r1, s32 idx, struct Mail * dest)
{
    mail = Mailbox_GetPtrToSlotI(mail, r1, idx);
    if (mail == NULL)
        Mail_init(dest);
    else
        Mail_copy(mail, dest);
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

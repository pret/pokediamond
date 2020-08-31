#ifndef POKEDIAMOND_SEALS_H
#define POKEDIAMOND_SEALS_H

#include "save_block_2.h"
#include "mail_message.h"

union MailPatternData
{
    u16 raw;
    struct {
        u16 unk_0:12;
        u16 unk_C:4;
    } bits;
};

struct Mail
{
    u32 author_otId; // author otid
    u8 author_gender; // author gender
    u8 author_language; // language
    u8 author_version; // version
    u8 mail_type; // mail type
    u16 author_name[OT_NAME_LENGTH + 1]; // author name
    union MailPatternData unk_18[3];
    u8 padding_1E[2];
    struct MailMessage unk_20[3];
};

struct Mail * Mail_new(u32 heap_id);

void Mail_init(struct Mail * mail);
BOOL Mail_TypeIsValid(struct Mail * mail);
struct Mail * Mail_new(u32 heap_id);
void Mail_copy(const struct Mail * src, struct Mail * dest);
void Mail_SetNewMessageDetails(struct Mail * mail, u8 type, u8 monIdx, struct SaveBlock2 * sav2);
u32 Mail_GetOTID(struct Mail * mail);
u16 * Mail_GetAuthorNamePtr(struct Mail * mail);
u8 Mail_GetAuthorGender(struct Mail * mail);
u8 Mail_GetType(struct Mail * mail);
void Mail_SetType(struct Mail * mail, u8 type);
u8 Mail_GetLanguage(struct Mail * mail);
u8 Mail_GetVersion(struct Mail * mail);
u16 Mail_GetAttrFromUnk18Array(struct Mail * mail, u32 idx, u32 attr);
struct MailMessage * Mail_GetUnk20Array(struct Mail * mail, u32 idx);
void Mail_CopyToUnk20Array(struct Mail * mail, const struct MailMessage * src, u32 idx);
struct Mail * Sav2_Mailbox_get(struct SaveBlock2 * sav2);
u32 Sav2_Mailbox_sizeof(void);
void Sav2_Mailbox_init(struct Mail * mail);
s32 Mailbox_GetFirstEmptySlotIdx(struct Mail * mail, BOOL r1);
void Mailbox_DeleteSlotI(struct Mail * mail, BOOL r1, s32 idx);
void Mailbox_CopyMailToSlotI(struct Mail * mail, BOOL r1, s32 idx, const struct Mail * src);
s32 Mailbox_CountMessages(struct Mail * mail, BOOL r1);
struct Mail * Mailbox_AllocAndFetchMailI(struct Mail * mail, BOOL r1, s32 idx, u32 heap_id);
void Mailbox_FetchMailIToBuffer(struct Mail * mail, BOOL r1, s32 idx, struct Mail * dest);
s32 MailArray_GetFirstEmptySlotIdx(struct Mail * mail, s32 count);
s32 MailArray_CountMessages(struct Mail * mail, s32 count);
struct Mail * Mailbox_GetPtrToSlotI(struct Mail * mail, BOOL r1, s32 idx);

#endif //POKEDIAMOND_SEALS_H

#ifndef POKEDIAMOND_MAIL_MESSAGE_H
#define POKEDIAMOND_MAIL_MESSAGE_H

struct MailMessage
{
    u16 msg_bank;
    u16 msg_no;
    u16 fields[2];
};

void MailMsg_init(struct MailMessage * mailMsg);
void MailMsg_init_withBank(struct MailMessage * mailMsg, u16 bank);
void MailMsg_init_default(struct MailMessage * mailMsg);
void MailMsg_init_fromTemplate(struct MailMessage * mailMsg, u32 a1);
struct String * MailMsg_GetExpandedString(struct MailMessage * mailMsg, u32 heap_id);
struct String * MailMsg_GetRawString(struct MailMessage * mailMsg, u32 heap_id);
BOOL MailMsg_IsInit(struct MailMessage * mailMsg);
BOOL MailMsg_AllFieldsAreInit(struct MailMessage * mailMsg);
u32 MailMsg_NumFields(u16 bank, u16 num);
u16 MailMsg_GetFieldI(struct MailMessage * mailMsg, u32 a1);
u16 MailMsg_GetMsgBank(struct MailMessage * mailMsg);
u16 MailMsg_GetMsgNo(struct MailMessage * mailMsg);
BOOL MailMsg_compare(const struct MailMessage *mailMsg, const struct MailMessage *a1);
void MailMsg_copy(struct MailMessage * mailMsg, const struct MailMessage * a1);
u32 MailMsg_NumMsgsInBank(u16 bank);
void MailMsg_SetMsgBankAndNum(struct MailMessage * mailMsg, u16 bank, u16 num);
void MailMsg_SetFieldI(struct MailMessage * mailMsg, u32 idx, u16 word);
void MailMsg_SetTrailingFieldsEmpty(struct MailMessage * mailMsg);

#endif //POKEDIAMOND_MAIL_MESSAGE_H

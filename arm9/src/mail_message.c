#include "global.h"
#include "msgdata.h"
#include "script_buffers.h"
#include "unk_0201B8B8.h"
#include "mail_message.h"

#pragma thumb on

struct UnkStruct_020ED556
{
    u8 unk_0;
    u8 unk_1;
    s16 unk_2;
    u16 unk_4;
    s16 unk_6;
    u16 unk_8;
};

extern u16 FUN_02013A9C(s16 bank, u16 num);

const u16 UNK_020ED54C[] = {
    397,
    399,
    395,
    396,
    398
};

const struct UnkStruct_020ED556 UNK_020ED556[] = {
    { 0, 0, 0x184,  7, -1, 0 },
    { 1, 0, 0x184, 33, -1, 0 },
    { 2, 0, 0x188, 10, -1, 0 },
    { 1, 4, 0x184,  1, -1, 0 }
};

void MailMsg_init(struct MailMessage * mailMsg)
{
    s32 i;
    mailMsg->msg_bank = 0xFFFF;
    for (i = 0; i < 2; i++)
    {
        mailMsg->fields[i] = 0xFFFF;
    }
}

void MailMsg_init_withBank(struct MailMessage * mailMsg, u16 bank)
{
    s32 i;
    mailMsg->msg_bank = bank;
    mailMsg->msg_no = 0;
    for (i = 0; i < 2; i++)
    {
        mailMsg->fields[i] = 0xFFFF;
    }
}

void MailMsg_init_default(struct MailMessage * mailMsg)
{
    MailMsg_init_withBank(mailMsg, 4);
    mailMsg->msg_no = 5;
}

void MailMsg_init_fromTemplate(struct MailMessage * mailMsg, u32 a1)
{
    GF_ASSERT(a1 < 4);
    if (a1 < 4)
    {
        MailMsg_init_withBank(mailMsg, UNK_020ED556[a1].unk_0);
        mailMsg->msg_no = UNK_020ED556[a1].unk_1;
        if (UNK_020ED556[a1].unk_2 != -1)
            mailMsg->fields[0] = FUN_02013A9C(UNK_020ED556[a1].unk_2, UNK_020ED556[a1].unk_4);
        if (UNK_020ED556[a1].unk_6 != -1)
            mailMsg->fields[1] = FUN_02013A9C(UNK_020ED556[a1].unk_6, UNK_020ED556[a1].unk_8);
    }
}

struct String * MailMsg_GetExpandedString(struct MailMessage * mailMsg, u32 heap_id)
{
    s32 i;
    struct ScrStrBufs * mgr = ScrStrBufs_new(heap_id);
    struct MsgData * msgData;
    struct String * ret;
    for (i = 0; i < 2; i++)
    {
        if (mailMsg->fields[i] == 0xFFFF)
            break;
        FUN_0200B518(mgr, (u32)i, mailMsg->fields[i]);
    }
    msgData = NewMsgDataFromNarc(1, NARC_MSGDATA_MSG, UNK_020ED54C[mailMsg->msg_bank], heap_id);
    ret = ReadMsgData_ExpandPlaceholders(mgr, msgData, mailMsg->msg_no, heap_id);
    DestroyMsgData(msgData);
    ScrStrBufs_delete(mgr);
    return ret;
}

struct String * MailMsg_GetRawString(struct MailMessage * mailMsg, u32 heap_id)
{
    return ReadMsgData_NewNarc_NewString(NARC_MSGDATA_MSG, UNK_020ED54C[mailMsg->msg_bank], mailMsg->msg_no, heap_id);
}

BOOL MailMsg_IsInit(struct MailMessage * mailMsg)
{
    return mailMsg->msg_bank != 0xFFFF;
}

BOOL MailMsg_AllFieldsAreInit(struct MailMessage * mailMsg)
{
    s32 i;
    u32 n = MailMsg_NumFields(mailMsg->msg_bank, mailMsg->msg_no);
    for (i = 0; i < n; i++)
    {
        if (mailMsg->fields[i] == 0xFFFF)
            return FALSE;
    }
    return TRUE;
}

u32 MailMsg_NumFields(u16 bank, u16 num)
{
    struct String * str;
    const u16 * cstr;
    u32 count;
    GF_ASSERT(bank < 5);
    GF_ASSERT(num < MailMsg_NumMsgsInBank(bank));
    str = ReadMsgData_NewNarc_NewString(NARC_MSGDATA_MSG, UNK_020ED54C[bank], num, 0);
    cstr = String_c_str(str);
    count = 0;
    while (*cstr != EOS)
    {
        if (*cstr == 0xFFFE)
        {
            if (MsgArray_ControlCodeIsStrVar(cstr))
                count++;
            cstr = MsgArray_SkipControlCode(cstr);
        }
        else
            cstr++;
    }
    String_dtor(str);
    return count;
}

u16 MailMsg_GetFieldI(struct MailMessage * mailMsg, u32 a1)
{
    return mailMsg->fields[a1];
}

u16 MailMsg_GetMsgBank(struct MailMessage * mailMsg)
{
    return mailMsg->msg_bank;
}

u16 MailMsg_GetMsgNo(struct MailMessage * mailMsg)
{
    return mailMsg->msg_no;
}

BOOL MailMsg_compare(struct MailMessage * mailMsg, struct MailMessage * a1)
{
    s32 i;
    if (mailMsg->msg_bank != a1->msg_bank || mailMsg->msg_no != a1->msg_no)
        return FALSE;
    for (i = 0; i < 2; i++)
    {
        if (mailMsg->fields[i] != a1->fields[i])
            return FALSE;
    }
    return TRUE;
}

void MailMsg_copy(struct MailMessage * mailMsg, const struct MailMessage * a1)
{
    *mailMsg = *a1;
}

u32 MailMsg_NumMsgsInBank(u16 bank)
{
    return (u32)((bank < 5) ? 20 : 0);
}

void MailMsg_SetMsgBankAndNum(struct MailMessage * mailMsg, u16 bank, u16 num)
{
    GF_ASSERT(bank < 5);
    mailMsg->msg_bank = bank;
    mailMsg->msg_no = num;
}

void MailMsg_SetFieldI(struct MailMessage * mailMsg, u32 idx, u16 word)
{
    GF_ASSERT(idx < 2);
    mailMsg->fields[idx] = word;
}

void MailMsg_SetTrailingFieldsEmpty(struct MailMessage * mailMsg)
{
    u32 n;
    for (n = MailMsg_NumFields(mailMsg->msg_bank, mailMsg->msg_no); n < 2; n++)
    {
        mailMsg->fields[n] = 0xFFFF;
    }
}

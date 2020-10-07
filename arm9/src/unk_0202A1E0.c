#include "global.h"
#include "MI_memory.h"
#include "mail_message.h"

#pragma thumb on

struct Unk0202A1F0
{
    u8 b0;
    u8 b1;
    u8 b2;
    u8 b3;
};

struct Unk0202A204
{
    struct MailMessage msg0;
    struct MailMessage msg1;
    struct MailMessage msg2;
    struct MailMessage msg3;
};

struct Unk0202A240
{
    u8 b0_0 : 1; // used
    u8 b0_1 : 1;
    u8 b0_2 : 3; // used
    u8 b0_5 : 3; // used
    u8 b1;
    u8 b2; // used
    u8 b3; // used
    u16 b4; // used
    u16 b6; // used
    int b8; // used
    int b12; // used
    int filler[6];
    int b40; // used
    int b44; // used
};

// Prototypes from other files
void FUN_02013764(void *arg0, int arg1);

// Prototypes for this file
int FUN_0202A1E0();
void FUN_0202A1E4(void *dest);
void FUN_0202A1F0(struct Unk0202A1F0 *unk);
void FUN_0202A204(struct Unk0202A204 *unk);
void FUN_0202A230(void *dest);
int FUN_0202A240(struct Unk0202A240 *unk, u32 arg1, void *dest);

int FUN_0202A1E0()
{
    return 0xe4;
}

void FUN_0202A1E4(void *dest)
{
    MI_CpuFill8(dest, 0, 0x3c);
}

void FUN_0202A1F0(struct Unk0202A1F0 *unk)
{
    MI_CpuFill8(unk, 0, 0x5a << 2);
    unk->b3 = 1;
}

void FUN_0202A204(struct Unk0202A204 *unk)
{
    MailMsg_init_fromTemplate(&unk->msg0, 0);
    MailMsg_init_fromTemplate(&unk->msg1, 1);
    MailMsg_init_fromTemplate(&unk->msg2, 2);
    MailMsg_init_fromTemplate(&unk->msg3, 3);
}

void FUN_0202A230(void *dest)
{
    MI_CpuFill8(dest, 0, 0xB3C);
}

int FUN_0202A240(struct Unk0202A240 *unk, u32 arg1, void *dest)
{
    switch (arg1)
    {
    case 0:
        return unk->b0_2;
    case 1:
        return unk->b2;
    case 2:
        return unk->b3;
    case 3:
        return unk->b4;
    case 4:
        return unk->b6;
    case 5:
        MI_CpuCopy8(&unk->b8, dest, 4);
        return 0;
    case 6:
        MI_CpuCopy8(&unk->b44, dest, 16);
        return 0;
    case 7:
        return unk->b0_0;
    case 8:
        MI_CpuCopy8(&unk->b12, dest, 28);
        return 0;
    case 9:
        return unk->b0_5;
    case 10:
        return unk->b40;
    default:
        return 0;
    };
}

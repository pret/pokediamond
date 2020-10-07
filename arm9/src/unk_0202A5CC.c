#include "global.h"
#include "mail_message.h"
#include "pokemon.h"
#include "proto.h"
#include "save_block_2.h"

#pragma thumb on

// Prototypes from other files
extern void FUN_02013960(void *arg0, u32 arg1);

struct Unk0202A5CC
{
    u32 b0;
    u32 b4;
};

// Prototypes for this file
void FUN_0202A5CC(struct Unk0202A5CC *unk, u32 arg1);
u32 FUN_0202A5D0(struct Unk0202A5CC *unk);
void FUN_0202A5D4(struct SaveBlock2 *sav2, u32 arg1, struct MailMessage *arg2);
struct MailMessage *FUN_0202A5F4(struct SaveBlock2 *sav2, u32 arg1);

void FUN_0202A5CC(struct Unk0202A5CC *unk, u32 arg1)
{
    unk->b4 = arg1;
}

u32 FUN_0202A5D0(struct Unk0202A5CC *unk)
{
    return unk->b4;
}


void FUN_0202A5D4(struct SaveBlock2 *sav2, u32 arg1, struct MailMessage *arg2)
{
    struct UnkSaveStruct_0202A5D4 *data = SavArray_get(sav2, 23);
    MailMsg_copy(&data->messages[arg1], arg2);
}

struct MailMessage *FUN_0202A5F4(struct SaveBlock2 *sav2, u32 arg1)
{
    struct UnkSaveStruct_0202A5D4 *data = SavArray_get(sav2, 23);
    return &data->messages[arg1];
}

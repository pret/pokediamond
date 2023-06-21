#ifndef POKEDIAMOND_UNK_020337E8_H
#define POKEDIAMOND_UNK_020337E8_H

#include "global.h"
#include "save.h"

// Dummy struct until DWC_account
struct DWC_Struct
{
    s32 unk0;
};

struct DWC_token
{
    // size: 0xC
    u8 fill0[0xC];
};

s32 sub_020337E8(u32 heap_id);
void sub_0203380C(struct DWC_Struct *);
s32 sub_02033830(struct DWC_Struct *);
BOOL sub_0203384C(struct SaveData *);


#endif //  POKEDIAMOND_UNK_020337E8_H
